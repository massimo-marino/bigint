//
// fibonacci.h
//
// Created by massimo on 3/16/18.
//

#pragma once

#include "cfile_helper.h"
#include "../bigint.h"
////////////////////////////////////////////////////////////////////////////////
using ui64 = uint_fast64_t;
using i32 = int32_t;
using i64 = int64_t;

static std::pair<bigint::bigint, bigint::bigint> fast_fib_even(ui64 n);
static std::pair<bigint::bigint, bigint::bigint> fast_fib(ui64 n);

template <typename T>
constexpr
bool
isOdd(const T& n) noexcept
{
  return (static_cast<T>(1) == (n & static_cast<T>(1)));
}

template <typename T>
constexpr
bool
isEven(const T& n) noexcept
{
  return (static_cast<T>(0) == (n & static_cast<T>(1)));
}
