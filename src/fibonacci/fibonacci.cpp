//
// fibonacci.cpp
//
// Created by massimo on 3/16/18.
//

#include "fibonacci.h"

#include <climits>
#include <iostream>
#include <boost/program_options.hpp>
////////////////////////////////////////////////////////////////////////////////
namespace po      = boost::program_options;
namespace postyle = boost::program_options::command_line_style;
////////////////////////////////////////////////////////////////////////////////

static
std::pair<bigint::bigint, bigint::bigint>
fast_fib_even(const uint_fast64_t n)
{
  if ( 0 == n )
  {
    return std::make_pair(1, 0);
  }
  else if ( 2 == n )
  {
    return std::make_pair(1, 1);
  }
  else if ( 4 == n )
  {
    return std::make_pair(2, 3);
  }
  auto p { fast_fib((n >> 1) - 1) };
  auto c { p.first + p.second };
  auto d { p.second + c };

  return std::make_pair(p.second * d + p.first * c, c * (d + p.second));
}

static
std::pair<bigint::bigint, bigint::bigint>
fast_fib(const uint_fast64_t n)
{
 if (isOdd(n))
 {
   auto p { fast_fib_even(n - 1) };
   return std::make_pair(p.second, p.first + p.second);
 }
 else
 {
   return fast_fib_even(n);
 }
}


static uint_fast64_t a;
static uint_fast64_t b;
static uint_fast64_t c;
static uint_fast64_t d;

static constexpr
void
fast_fib(const uint_fast64_t n, uint_fast64_t ans[])
{
  if (0 == n)
  {
    ans[0] = 0;  // F(0)
    ans[1] = 1;  // F(1)
    return;
  }

  fast_fib((n >> 1), ans);

  a = ans[0];  // F(n)
  b = ans[1];  // F(n+1)
  c = 2 * b - a;

  c = (a * c);          // F(2n)
  d = (a * a + b * b);  // F(2n + 1)
  if (0 == n % 2)
  {
    ans[0] = c;
    ans[1] = d;
  }
  else
  {
    ans[0] = d;
    ans[1] = c + d;
  }
}

static constexpr
uint_fast64_t
fastFib(const uint_fast64_t n)
{
  if (n < 94)
  {
    uint_fast64_t ans[2] = {0};

    fast_fib(n, ans);

    return ans[0];
  }
  return 0;
}

static
bigint::bigint
fastFib(const uint_fast64_t n, const bool flag)
{
  if (n >= 94)
  {
    return fast_fib(n).second;
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
int
main(const int argc, const char** argv)
{
  po::options_description desc("Options");

  desc.add_options()
          ("n,n",    po::value<uint_fast64_t>()->implicit_value(1)->default_value(1), "the fib number we want to compute")
          ("test,t", po::value<bool>()->implicit_value(true)->default_value(false), "test fib algorithms; no result is printed or saved on file")
          ("write-to-file,w", po::value<bool>()->implicit_value(true)->default_value(false), "write the result to file")
          ("help,h",   "Print this help message")
          ;

  po::variables_map vm;

  try
  {
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);

    po::notify(vm);

    if ( vm.count("help") )
    {
      std::clog << "[" << __func__ << "] "
                << "USAGE: "
                << argv[0]
                << " options\n"
                << desc
                << '\n';
      return 0;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "[" << __func__ << "] "
              << "Error parsing command line: '"
              << e.what()
              << "'"
              << '\n';

    std::cerr << desc << '\n';

    return -1;
  }

  const uint_fast64_t N { vm["n"].as<uint_fast64_t>() };
  const bool testAlgo { vm["test"].as<bool>() };
  const bool writeToFile { vm["write-to-file"].as<bool>() };
////////////////////////////////////////////////////////////////////////////////
  if ( N < 94 )
  {
    // compute fib(N)
    const uint_fast64_t fN { fastFib(N) };
    const std::string sfN { std::to_string(fN) };

    if (writeToFile) {
      const std::string fileName{ "fib-" + std::to_string(N) + ".txt" };
      utilities::cfile_helper::cfile_helper fs { utilities::cfile_helper::cfile_helper(fileName,
                                                                                       utilities::cfile_helper::cfile_helper::fstream_direction::fs_OUTPUT) };
      fs.get_fstream() << sfN;
      std::cout << "[" << __func__ << "] "
                << "fib("
                << N
                << ") = "
                << sfN
                << "\nof length "
                << sfN.size()
                << " digits written to file "
                << fileName
                << std::endl;
    } else {
      std::cout << "[" << __func__ << "] "
                << "fib("
                << N
                << ") = "
                << sfN
                << "\nof length "
                << sfN.size()
                << std::endl;
    }
  }
  else  // when N >= 94
  {
//    [[maybe_unused]]
//    auto
//    fib = [&N]() {
//      bigint::bigint fib_n;
//      bigint::bigint fib_n_1;
//      bigint::bigint fib_n_2;
//      uint_fast64_t n{};
//
//      fib_n_1 = 1;
//      fib_n_2 = 0;
//
//      for (n = 2; n <= N; ++n) {
//        fib_n = fib_n_1 + fib_n_2;
//        fib_n_2 = fib_n_1;
//        fib_n_1 = fib_n;
//      }
//      return fib_n_1;
//    };

//    [[maybe_unused]]
//    auto
//    pfib = [&N]() {
//      bigint::bigint *pfib_n = new bigint::bigint;
//      bigint::bigint *pfib_n_1 = new bigint::bigint;
//      bigint::bigint *pfib_n_2 = new bigint::bigint;
//      uint_fast64_t n{};
//
//      *pfib_n_1 = 1;
//      *pfib_n_2 = 0;
//
//      for (n = 2; n <= N; ++n) {
//        *pfib_n = *pfib_n_1 + *pfib_n_2;
//        std::swap(pfib_n_2, pfib_n);
//        std::swap(pfib_n_2, pfib_n_1);
//      }
//      return *pfib_n_1;
//    };

    [[maybe_unused]]
    auto
    upfib = [&N]() {
      std::unique_ptr<bigint::bigint> upfib_n   { bigint::createUniquePtr() };  // ptr to fib(n)
      std::unique_ptr<bigint::bigint> upfib_n_1 { bigint::createUniquePtr() };  // ptr to fib(n - 1)
      std::unique_ptr<bigint::bigint> upfib_n_2 { bigint::createUniquePtr() };  // ptr to fib(n - 2)
      uint_fast64_t n {};

      *upfib_n_1 = 1;
      *upfib_n_2 = 0;

      for (n = 2; n <= N; ++n) {
        *upfib_n = *upfib_n_1 + *upfib_n_2; // fib(n) = fib(n - 1) + fib(n - 2)
        std::swap(upfib_n_2, upfib_n);
        std::swap(upfib_n_2, upfib_n_1);
      }
      return *upfib_n_1;
    };

//    bigint::bigint fN;

    if ( bigint::bigint fN; false == testAlgo )
    {
      fN = upfib();

      if (writeToFile) {
        const std::string fileName{ "fib-" + std::to_string(N) + ".txt" };
        utilities::cfile_helper::cfile_helper fs { utilities::cfile_helper::cfile_helper(fileName,
                                                                                         utilities::cfile_helper::cfile_helper::fstream_direction::fs_OUTPUT) };
        fs.get_fstream() << fN;

        std::cout << "[" << __func__ << "] "
                  << "fib("
                  << N
                  << ") of length "
                  << bigint::numberOfDigits(fN)
                  << " digits written to file "
                  << fileName
                  << std::endl;
      } else {
        std::cout << "[" << __func__ << "] "
                  << "fib("
                  << N
                  << ") = "
                  << fN
                  << "\nof length "
                  << bigint::numberOfDigits(fN)
                  << std::endl;
      }
    }
    else
    {
      [[maybe_unused]]
      auto
      upfibTest = [](const uint_fast64_t &N)
      {
        std::unique_ptr<bigint::bigint> upfib_n   { bigint::createUniquePtr() };
        std::unique_ptr<bigint::bigint> upfib_n_1 { bigint::createUniquePtr() };
        std::unique_ptr<bigint::bigint> upfib_n_2 { bigint::createUniquePtr() };
        uint_fast64_t n {};

        *upfib_n_1 = 1;
        *upfib_n_2 = 0;

        for (n = 2; n <= N; ++n)
        {
          *upfib_n = *upfib_n_1 + *upfib_n_2;
          std::swap(upfib_n_2, upfib_n);
          std::swap(upfib_n_2, upfib_n_1);
        }
        return *upfib_n_1;
      };

      bigint::bigint fNnew;
      for (uint_fast64_t n {94}; n <= N; ++n)
      {
        fN = upfibTest(n);
        fNnew = fastFib(n, true);

        if (fN != fNnew)
        {
          std::cout << n << ": " << "DIFFERENT" << std::endl;

          std::stringstream olds {};
          std::stringstream news {};
          olds << fN;
          news << fNnew;
          if (olds.str().size() != news.str().size())
          {
            std::cout << n << ": " << "LENGTHS DIFFER" << std::endl;
          }
          exit(2);
/*
          for (size_t i {0}; i < olds.str().size(); ++i)
          {
            if (olds.str()[i] != news.str()[i]) {
              std::cout << "differ at index "
                        << i
                        << " -> '"
                        << static_cast<char>(olds.str()[i])
                        << "' - '"
                        << static_cast<char>(news.str()[i])
                        << "'"
                        << std::endl;
            }
          }
*/
        }
/*
        else
        {
          std::cout << n << ": " << "EQUAL" << std::endl;
        }
*/
      }
      std::cout << "[" << __func__ << "] "
                << "fib("
                << N
                << ") was computed correctly"
                << std::endl;
    }
  }
  return 0;
}
