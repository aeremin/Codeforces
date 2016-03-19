#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "util/relax.h"
using namespace std;


using namespace std;

struct Edge {
    int64_t from, to, cap, flow, index;
    Edge(int64_t from, int64_t to, int64_t cap, int64_t flow, int64_t index) :
        from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
    int64_t N;
    vector<vector<Edge> > G;
    vector<int64_t> excess;
    vector<int64_t> dist, active, count;
    queue<int64_t> Q;

    PushRelabel(int64_t N) : N(N), G(N), excess(N), dist(N), active(N), count(2 * N) {}

    void AddEdge(int64_t from, int64_t to, int64_t cap) {
        G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
        if (from == to) G[from].back().index++;
        G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
    }

    void Enqueue(int64_t v) {
        if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
    }

    void Push(Edge &e) {
        int64_t amt = int64_t(min(excess[e.from], int64_t(e.cap - e.flow)));
        if (dist[e.from] <= dist[e.to] || amt == 0) return;
        e.flow += amt;
        G[e.to][e.index].flow -= amt;
        excess[e.to] += amt;
        excess[e.from] -= amt;
        Enqueue(e.to);
    }

    void Gap(int64_t k) {
        for (int64_t v = 0; v < N; v++) {
            if (dist[v] < k) continue;
            count[dist[v]]--;
            dist[v] = max(dist[v], N + 1);
            count[dist[v]]++;
            Enqueue(v);
        }
    }

    void Relabel(int64_t v) {
        count[dist[v]]--;
        dist[v] = 2 * N;
        for (int64_t i = 0; i < G[v].size(); i++)
            if (G[v][i].cap - G[v][i].flow > 0)
                dist[v] = min(dist[v], dist[G[v][i].to] + 1);
        count[dist[v]]++;
        Enqueue(v);
    }

    void Discharge(int64_t v) {
        for (int64_t i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
        if (excess[v] > 0) {
            if (count[dist[v]] == 1)
                Gap(dist[v]);
            else
                Relabel(v);
        }
    }

    int64_t GetMaxFlow(int64_t s, int64_t t) {
        count[0] = N - 1;
        count[N] = 1;
        dist[s] = N;
        active[s] = active[t] = true;
        for (int64_t i = 0; i < G[s].size(); i++) {
            excess[s] += G[s][i].cap;
            Push(G[s][i]);
        }

        while (!Q.empty()) {
            int64_t v = Q.front();
            Q.pop();
            active[v] = false;
            Discharge(v);
        }

        int64_t totflow = 0;
        for (int64_t i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
        return totflow;
    }
};


class Solver653D
{
public:
    void run();
};

void Solver653D::run()
{
    int64_t nVertices, nEdges, nBears;
    cin >> nVertices >> nEdges >> nBears;
    struct Edge { int64_t from, to, w; };
    vector<Edge> edges(nEdges);
    for (auto& e : edges)
        cin >> e.from >> e.to >> e.w;

    double l = 0.0;
    double r = 1e18;
    while (r - l > 1e-8) {
        auto m = (r + l) / 2.0;
        auto perBear = m / nBears;
        
        PushRelabel pr(nVertices);
        
        vector<vector<int64_t>> c(nVertices, vector<int64_t>(nVertices, 0));
        for (auto& e : edges)
            pr.AddEdge(e.from - 1, e.to - 1, e.w / perBear);

        auto fl = pr.GetMaxFlow(0, nVertices - 1);
        if (fl >= nBears)
            l = m;
        else
            r = m;
    }

    cout << setprecision(7) << fixed << r;
}

class Solver653DTest : public ProblemTest {};

TEST_F(Solver653DTest, Example1)
{
    string input = R"(4 4 3
1 2 2
2 4 1
1 3 1
3 4 2
)";
    string output = R"(1.5000000
)";
    output.pop_back();
    setInput(input);
    Solver653D().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver653DTest, Example2)
{
    string input = R"(5 11 23
1 2 3
2 3 4
3 4 5
4 5 6
1 3 4
2 4 5
3 5 6
1 4 2
2 5 3
1 5 2
3 2 30
)";
    string output = R"(10.2222222
)";
    output.pop_back();
    setInput(input);
    Solver653D().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver653DTest, Example3) {
    string input = R"(3 2 1
1 3 1
2 3 1
)";
    string output = R"(1.0000000
)";
    output.pop_back();
    setInput(input);
    Solver653D().run();
    EXPECT_EQ(output, getOutput());
}

