//
// fibonacci.h
//
// Created by massimo on 3/16/18.
//

#pragma once

#include "cfile_helper.h"
#include "../bigint.h"
////////////////////////////////////////////////////////////////////////////////

static std::pair<bigint::bigint, bigint::bigint> fast_fib_even(uint_fast64_t n);
static std::pair<bigint::bigint, bigint::bigint> fast_fib(uint_fast64_t n);

template <typename T>
constexpr
bool
isOdd(const T& n) noexcept
{
  static_assert(std::is_integral<T>::value, "Integral required.");
  return (static_cast<T>(1) == (n & static_cast<T>(1)));
}

template <typename T>
constexpr
bool
isEven(const T& n) noexcept
{
  static_assert(std::is_integral<T>::value, "Integral required.");
  return (static_cast<T>(0) == (n & static_cast<T>(1)));
}
