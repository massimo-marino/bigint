//
// perf-timer.h
//
#pragma once
//
//#include <iostream>
#include <chrono>
#include <algorithm>
//
////////////////////////////////////////////////////////////////////////////////
using namespace std::chrono_literals;

template <typename Time  = std::chrono::nanoseconds,
          typename Clock = std::chrono::steady_clock> //std::chrono::high_resolution_clock>
struct perftimer_t {

  // returns time measured in Time, defaulting to nanoseconds
  template <typename F, typename... Args>
  static inline auto duration(F&& f, Args&&... args) -> Time {
    const typename Clock::time_point start { Clock::now() };

    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);  // from C++17
    //f(std::forward<Args>(args)...);  // until C++17

    const typename Clock::time_point end { Clock::now() };

    return std::chrono::duration_cast<Time>(end - start);
  }

  // returns time measured in seconds
  template <typename F, typename... Args>
  static inline auto duration_secs(F&& f, Args&&... args) -> std::chrono::duration<double> {
    const typename Clock::time_point start { Clock::now() };

    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);  // from C++17
    //f(std::forward<Args>(args)...);  // until C++17

    const typename Clock::time_point end { Clock::now() };

    return std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
  }
};  // struct perftimer_t

// returns time measured in seconds
template <typename F, typename... Args>
static inline auto duration_secs(F&& f, Args&&... args) -> double {
  const std::chrono::steady_clock::time_point start { std::chrono::steady_clock::now() };

  std::invoke(std::forward<F>(f), std::forward<Args>(args)...);  // from C++17
  //f(std::forward<Args>(args)...);  // until C++17

  const std::chrono::steady_clock::time_point end { std::chrono::steady_clock::now() };

  return std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}

// returns time measured in nanoseconds
template <typename F, typename... Args>
static inline auto duration_nsec(F&& f, Args&&... args) -> long {
  const std::chrono::steady_clock::time_point start { std::chrono::steady_clock::now() };

  std::invoke(std::forward<F>(f), std::forward<Args>(args)...);  // from C++17
  //f(std::forward<Args>(args)...);  // until C++17

  const std::chrono::steady_clock::time_point end { std::chrono::steady_clock::now() };

  return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

// returns time measured in microseconds
template <typename F, typename... Args>
static inline auto duration_microsec(F&& f, Args&&... args) -> long {
  const std::chrono::steady_clock::time_point start { std::chrono::steady_clock::now() };

  std::invoke(std::forward<F>(f), std::forward<Args>(args)...);  // from C++17
  //f(std::forward<Args>(args)...);  // until C++17

  const std::chrono::steady_clock::time_point end { std::chrono::steady_clock::now() };

  return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// returns time measured in milliseconds
template <typename F, typename... Args>
static inline auto duration_msec(F&& f, Args&&... args) -> long {
  const std::chrono::steady_clock::time_point start { std::chrono::steady_clock::now() };

  std::invoke(std::forward<F>(f), std::forward<Args>(args)...);  // from C++17
  //f(std::forward<Args>(args)...);  // until C++17

  const std::chrono::steady_clock::time_point end { std::chrono::steady_clock::now() };

  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}
