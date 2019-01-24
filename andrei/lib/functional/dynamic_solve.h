// Generic solver for dynamic programming problems.
//
// * DynamicSolver<Result(Arg1, Arg2, ...)>
//
//   Sample usage:
//
//       using Solver = DynamicSolver<int(int)>;
//       Solver fibonacci_solver([](Solver& solver, int x) {
//           return (x <= 2) ? 1 : solver(x - 1) + solver(x - 2);
//       });
//       int x = fibonacci_solver(6);      // x == 8
//
//   The solver caches results internally. The cache is persistent across calls:
//
//       Solver fibonacci_solver(...);
//       int a = fibonacci_solver(n);      // O(n)
//       int b = fibonacci_solver(n + 1);  // O(1)

#pragma once

#include <functional>
#include <tuple>
#include <type_traits>
#include <unordered_map>


template<typename>
class DynamicSolver;

template<typename ResultT, typename... Args>
class DynamicSolver<ResultT(Args...)> {
public:
    using ValueFuncT = std::function<ResultT(DynamicSolver&, Args...)>;

    DynamicSolver(ValueFuncT value_func)
    : value_func_(std::move(value_func)) {}

    ResultT operator()(const Args&... args) {
        auto key = std::make_tuple(args...);
        const auto it = cache_.find(key);
        if (it != cache_.end())
            return it->second;
        ResultT result = value_func_(*this, args...);
        cache_.insert(it, {std::move(key), result});
        return result;
    }

private:
    std::unordered_map<std::tuple<Args...>, ResultT> cache_;
    ValueFuncT value_func_;
};
