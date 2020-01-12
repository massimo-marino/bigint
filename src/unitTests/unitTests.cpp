/* 
 * File:   unitTests.cpp
 * Author: massimo
 *
 * Created on October 04, 2017, 10:43 AM
 */

#include "../bigint.h"
#include <chrono>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;
////////////////////////////////////////////////////////////////////////////////
// a simple function's performance timer
template <typename Time = std::chrono::nanoseconds,
          typename Clock = std::chrono::high_resolution_clock>
struct perftimer
{
  template <typename F, typename... Args>
  static inline Time duration(F&& f, Args&&... args)
  {
    auto start = Clock::now();
    // C++17: not yet available
    //std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    f(std::forward<Args>(args)...);
    auto end = Clock::now();

    return std::chrono::duration_cast<Time>(end - start);
  }
};

// BEGIN: ignore the warnings listed below when compiled with clang from here
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
////////////////////////////////////////////////////////////////////////////////
TEST(bigint, test_1)
{
  bigint::bigint z {};
  ASSERT_EQ(bigint::bigint("0"), z);
  bigint::bigint a("100000000000000000000000000000000000000000000000000000000000000000");
  bigint::bigint b("100000000000000000000000000000000000000000000000000000000000000000");
  ASSERT_TRUE(bigint::bigint("200000000000000000000000000000000000000000000000000000000000000000") == (a + b));
  ASSERT_TRUE(bigint::bigint("0") == (a - b));
  ASSERT_TRUE(bigint::bigint("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000") == (a * b));
  ASSERT_TRUE(bigint::bigint("1") == (a / b));

  a = -a;
  ASSERT_TRUE(bigint::bigint("-100000000000000000000000000000000000000000000000000000000000000000") == a);

  a -= -a;
  ASSERT_TRUE(bigint::bigint("-200000000000000000000000000000000000000000000000000000000000000000") == a);

  b = a - b;
  ASSERT_TRUE(bigint::bigint("-300000000000000000000000000000000000000000000000000000000000000000") == b);
}

TEST(bigint, test_2)
{
  bigint::bigint b("333333333333");
  auto c = bigint::bigint{300'000} * b;
  ASSERT_TRUE(bigint::bigint("99999999999900000") == c);
  std::cout << c << " of size " << bigint::numberOfDigits(c) << '\n';
  std::cout << c.longValue() << '\n';
}

TEST(bigint, test_3)
{
  bigint::bigint b("1234567898765432112345678987654321");
  auto c = bigint::bigint("1234567898765432112345678987654321") * b;
  ASSERT_TRUE(bigint::bigint("1524157896662094232586495832952294194482547660417620210333789971041") == c);
  std::cout << c << " of size " << bigint::numberOfDigits(c) << '\n';
}    

TEST(bigint, test_4)
{
  bigint::bigint a{"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222"};
  auto b = a / 2;
  ASSERT_TRUE(bigint::bigint("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111") == b);
  std::cout << b << " of size " << bigint::numberOfDigits(b) << '\n';
}

TEST(bigint, test_5)
{
  std::string sa {};
  std::string sb {};
  int i {};

  for (i = 0; i < 1'000'000; ++i)
  {
    sa += i % 10 + '0';
  }
  for (i = 0; i < 1'000'000; ++i)
  {
    sb += i % 10 + '0';
  }

  auto a = bigint::bigint(sa);
  auto b = bigint::bigint(sb);
  std::cout << "sa length: " << sa.size() <<'\n';
  std::cout << "sb length: " << sb.size() <<'\n';

  auto fun = [&a, &b]() {bigint::bigint c = a * b;};
  auto funTime = perftimer<std::chrono::nanoseconds>::duration(fun).count();
  std::cout << "lambda {bigint c = a * b;} took:\t\t"
            << funTime
            << " nsec"
            << '\n';

  auto start = std::chrono::high_resolution_clock::now();
  {bigint::bigint c = a * b;}
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "in block scope {bigint c = a * b;} took:\t"
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
            << " nsec"
            << '\n';
}

TEST(bigint, test_6)
{
  bigint::bigint c {};

  for (int i {1}; i <= 2'000'000; ++i)
  {
    bigint::bigint a {"9782787878638754910809747756469127987319837918612987319811298361928"};
    bigint::bigint b {"9991839289197398134501938746372911008273863561216526156219903838393"};
    c = a * b;
    ASSERT_EQ(a * b,
              bigint::bigint("97748044283666779233341997400581063693895238139796658084782362620593578372143918935600287680752213307748175835572108551004920535901704"));
    ASSERT_EQ(c,
              bigint::bigint("97748044283666779233341997400581063693895238139796658084782362620593578372143918935600287680752213307748175835572108551004920535901704"));
  }
  std::cout << c << " of size " << bigint::numberOfDigits(c) << '\n';
}

TEST(bigint, test_7)
{
  std::string sa {};
  std::string sb {};
  auto a = bigint::bigint(sa);
  auto b = bigint::bigint(sb);
  auto c = bigint::bigint {};
  int i {};
  int j {};

  for (i = 1; i <= 100; ++i)
  {
    sa += i % 10 + '0';

    for (j = 1; j <= 100; ++j)
    {
      sb += j % 10 + '0';

      a = bigint::bigint(sa);
      b = bigint::bigint(sb);
      c = bigint::bigint {};

      auto fun = [&a, &b, &c]() {c = a * b;};
      auto funTime = perftimer<std::chrono::nanoseconds>::duration(fun).count();
      std::cout << "sa length: "
                << sa.size()
                << " sb length: "
                << sb.size()
                << " result length: "
                << bigint::numberOfDigits(c)
                << " "
                << funTime
                << " nsec"
                << std::endl;
    }
  }
}

TEST(bigint, test_8)
{
  const int64_t maxN {99'999'999};

  for (int64_t i {1}; i <= maxN; ++i)
  {
    int64_t is = i * (i + 1) / 2;
    bigint::bigint isbi(is);
    bigint::bigint bis {i * (i + 1) / 2};
    ASSERT_TRUE(isbi == bis);
  }
}

TEST(bigint, fibonacci)
{
  bigint::bigint fib_n;
  bigint::bigint fib_n_1;
  bigint::bigint fib_n_2;
  int32_t n {};
  fib_n_1 = 1;
  fib_n_2 = 0;

  for (n = 2; n <= 1'001; ++n)
  {
    fib_n = fib_n_1 + fib_n_2;
    fib_n_2 = fib_n_1;
    fib_n_1 = fib_n;
  }
  ASSERT_EQ(n, 1'002);
  ASSERT_EQ(bigint::bigint("70330367711422815821835254877183549770181269836358732742604905087154537118196933579742249494562611733487750449241765991088186363265450223647106012053374121273867339111198139373125598767690091902245245323403501"),
             fib_n_1);
}

TEST(bigint, test_9)
{
  const size_t SIZE {2'000'000};
  std::string sa {};
  std::string sb {};
  sa.reserve(SIZE);
  sb.reserve(SIZE);
  for(int32_t i {1}; i <= SIZE;)
  {
    sa += std::to_string(i % 10);
    sb += std::to_string((++i) % 10);
  }
  bigint::bigint a {sa};
  bigint::bigint b {sb};
  bigint::bigint result {};
  auto fun = [&a, &b, &result]()
  {
    result = a * b;
  };

  auto funTime = perftimer<std::chrono::nanoseconds>::duration(fun).count() * (1.0 / 1'000'000.0);
  size_t sizeOfA {bigint::numberOfDigits(a)};
  size_t sizeOfB {bigint::numberOfDigits(b)};
  size_t sizeOfResult {bigint::numberOfDigits(result)};
  std::cout << "a length:      " << sizeOfA << std::endl;
  std::cout << "b length:      " << sizeOfB << std::endl;
  std::cout << "result length: " << sizeOfResult << std::endl;
  ASSERT_EQ(sizeOfA + sizeOfB - 1, sizeOfResult);
  std::cout << "result = a * b took "
            << funTime
            << " msec"
            << '\n';
}

TEST(bigint, test_10)
{
  const size_t SIZE {2'000'000};
  std::string sa {};
  std::string sb {};
  sa.reserve(SIZE);
  sb.reserve(SIZE);
  for(int32_t i {1}; i <= SIZE; ++i)
  {
    sa += std::to_string(i % 10);
  }
  sb = sa;
  bigint::bigint a {sa};
  bigint::bigint b {sb};
  bigint::bigint zero {0};
  bigint::bigint result {1};
  auto fun = [&a, &b, &result, &zero]()
  {
    result = a - b;
    ASSERT_EQ(zero, result);
  };

  auto funTime = perftimer<std::chrono::nanoseconds>::duration(fun).count() * (1.0 / 1'000'000.0);
  size_t sizeOfA {bigint::numberOfDigits(a)};
  size_t sizeOfB {bigint::numberOfDigits(b)};
  size_t sizeOfResult {bigint::numberOfDigits(result)};
  std::cout << "a length:      " << sizeOfA << std::endl;
  std::cout << "b length:      " << sizeOfB << std::endl;
  std::cout << "result length: " << sizeOfResult << std::endl;
  ASSERT_EQ(1, sizeOfResult);
  std::cout << "result = a - b took "
            << funTime
            << " msec"
            << std::endl;
}

TEST(bigint, test_11)
{
  const size_t SIZE {2'000'000};
  std::string sa {};
  std::string sb {};
  sa.reserve(SIZE);
  sb.reserve(SIZE);
  for(int32_t i {1}; i <= SIZE; ++i)
  {
    sa += std::to_string(i % 10);
  }
  sb = sa;
  bigint::bigint a {sa};
  bigint::bigint b {sb};
  bigint::bigint result {1};
  bigint::bigint two {2};
  auto fun = [&a, &b, &result, &two]()
  {
    result = a + b;
    ASSERT_EQ(two * a, result);
    ASSERT_EQ(two * b, result);
  };

  auto funTime = perftimer<std::chrono::nanoseconds>::duration(fun).count() * (1.0 / 1'000'000.0);
  size_t sizeOfA {bigint::numberOfDigits(a)};
  size_t sizeOfB {bigint::numberOfDigits(b)};
  size_t sizeOfResult {bigint::numberOfDigits(result)};
  std::cout << "a length:      " << sizeOfA << std::endl;
  std::cout << "b length:      " << sizeOfB << std::endl;
  std::cout << "result length: " << sizeOfResult << std::endl;
  ASSERT_EQ(sizeOfA, sizeOfResult);
  ASSERT_EQ(sizeOfB, sizeOfResult);
  std::cout << "result = a + b took "
            << funTime
            << " msec"
            << std::endl;
}

TEST(bigint, test_12)
{
  const size_t SIZE {2'000'000};
  std::string sa {};
  std::string sb {};
  sa.reserve(SIZE);
  sb.reserve(SIZE);
  for(int32_t i {1}; i <= SIZE;)
  {
    sa += std::to_string(i % 10);
    sb += std::to_string((++i) % 10);
  }
  bigint::bigint a {sa};
  bigint::bigint b {sb};
  bigint::bigint result {};
  auto fun = [&a, &b, &result]()
  {
    result = a / b;
  };

  auto funTime = perftimer<std::chrono::nanoseconds>::duration(fun).count() * (1.0 / 1'000'000.0);
  size_t sizeOfA {bigint::numberOfDigits(a)};
  size_t sizeOfB {bigint::numberOfDigits(b)};
  size_t sizeOfResult {bigint::numberOfDigits(result)};
  std::cout << "a length:      " << sizeOfA << std::endl;
  std::cout << "b length:      " << sizeOfB << std::endl;
  std::cout << "result length: " << sizeOfResult << std::endl;
  ASSERT_EQ(1, sizeOfResult);
  std::cout << "result = a / b took "
            << funTime
            << " msec"
            << '\n';
}
////////////////////////////////////////////////////////////////////////////////
#pragma clang diagnostic pop
// END: ignore the warnings when compiled with clang up to here
