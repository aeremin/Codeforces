// Generalized graph traversal. Not intended to be used directly.
//
// Signature:
//   traverse_graph(graph, starting_vertices, [on_see, on_enter], on_exit)
//
// Supports all graphs, directed or non-directed.
//
// ExecutionControllerT must provide these function with obvious semantics:
//   - push;
//   - pop;
//   - top;
//   - empty.
// Substituting stack corresponds to DFS; queue - to BFS.
//
// starting_vertices is any iterable collection of ints, e.g.
// std::vector, initializer_list or a range (see iter/range.h).
// To start with one vertex use `{vertex}`.
//
// All callbacks must have the following signature:
// ` IterationControl callback(const GraphTraversalState&, int /*vertex*/);
//
// Callback types:
//   - on_see: a vertex is being considered as a candidate to go to;
//   - on_enter: a vertex is pushed to stack/queue (most interesting for BFS);
//   - on_exit: a vertex is poped from stack/queue (most interesting for DFS).
//
// Returns IterationResult, which is
//   - Aborted if any callback returned Abort, and
//   - Done otherwise.
//
// Call sequence for each vertex, if there are no aborts:
//   (on_see? on_enter on_see* on_exit on_see*)?
// After AbortGently:
//   - no more on_see or on_enter are issued;
//   - on_exit are issued for all vertices that had on_enter called before,
//     and only for them (so, the above-mentioned call sequence holds true).
// After AbortBluntly: no more callbacks are issued.

// TODO: Treat callback returning void as if they return IterationControl::Proceed.

#pragma once

#include <queue>
#include <stack>

#include "graph/graph.h"


struct GraphTraversalState {
    int starting_vertex = kInvalidGraphVertex;
    int previous_vertex = kInvalidGraphVertex;
    std::vector<char> visited;
    bool aborting = false;
};

enum class IterationResult {
    Done,
    Aborted,
};

enum class IterationControl {
    Proceed,
    AbortGently,
    AbortBluntly,
};

// NOTE. This could've been a normal function, but that makes traversal slower
//       under gcc with "-O2". Even with "__attribute__((always_inline))".
//       I assume, inlining happens too late or doesn't happen at all.
#define graph_traversal_noop_continue [](const GraphTraversalState&, int) { return IterationControl::Proceed; }

template <typename GraphT>
struct GraphTraversalExecutionItem {
    explicit GraphTraversalExecutionItem(int v, const GraphT& graph)
        : vertex(v), neighbour_it(graph.out_nbrs(v).begin()) {}

    int vertex;
    typename GraphT::NeighborMap::const_iterator neighbour_it;
};


// TODO: Test.
// TODO: Benchmark.
template <typename ExecutionControllerT, typename GraphT, typename VertexListT, typename OnSeeT, typename OnEnterT,
          typename OnExitT>
IterationResult traverse_graph(const GraphT& graph, const VertexListT& starting_vertices, const OnSeeT& on_see,
                               const OnEnterT& on_enter, const OnExitT& on_exit) {
    GraphTraversalState state;
    const GraphTraversalState& const_state = state;
    state.visited.resize(graph.num_vertices(), false);
    for (int start : starting_vertices) {
        ExecutionControllerT execution_controller;
        state.starting_vertex = start;
        state.previous_vertex = kInvalidGraphVertex;
        if (state.visited[start])
            continue;

        switch (on_enter(const_state, start)) {
            case IterationControl::Proceed:
                state.visited[start] = true;
                execution_controller.push(GraphTraversalExecutionItem<GraphT>{start, graph});
                break;
            case IterationControl::AbortGently:
                state.aborting = true;
                break;
            case IterationControl::AbortBluntly:
                return IterationResult::Aborted;
        }
        while (!execution_controller.empty()) {
            auto& top = execution_controller.top();
            state.previous_vertex = top.vertex;
            bool we_need_to_go_deeper = false;
            if (!state.aborting) {
                while (top.neighbour_it != graph.out_nbrs(top.vertex).end()) {
                    int neighbour = top.neighbour_it->first;
                    switch (on_see(const_state, neighbour)) {
                        case IterationControl::Proceed:
                            break;
                        case IterationControl::AbortGently:
                            we_need_to_go_deeper = false;
                            state.aborting = true;
                            break;
                        case IterationControl::AbortBluntly:
                            return IterationResult::Aborted;
                    }
                    if (state.aborting)
                        break;
                    ++top.neighbour_it;
                    if (!state.visited[neighbour]) {
                        switch (on_enter(const_state, neighbour)) {
                            case IterationControl::Proceed:
                                state.visited[neighbour] = true;
                                execution_controller.push(GraphTraversalExecutionItem<GraphT>{neighbour, graph});
                                we_need_to_go_deeper = true;
                                break;
                            case IterationControl::AbortGently:
                                state.aborting = true;
                                break;
                            case IterationControl::AbortBluntly:
                                return IterationResult::Aborted;
                        }
                        break;
                    }
                }
            }
            if (!we_need_to_go_deeper) {
                switch (on_exit(const_state, top.vertex)) {
                    case IterationControl::Proceed:
                        break;
                    case IterationControl::AbortGently:
                        state.aborting = true;
                        break;
                    case IterationControl::AbortBluntly:
                        return IterationResult::Aborted;
                }
                execution_controller.pop();
            }
        }
        if (state.aborting)
            break;
    }
    return state.aborting ? IterationResult::Aborted : IterationResult::Done;
}
