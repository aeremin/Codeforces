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
