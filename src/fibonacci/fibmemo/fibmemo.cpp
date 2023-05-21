//
// fibmemo.cpp
//
#include <iostream>
#include <cstdint>
#include <deque>
#include <boost/program_options.hpp>
//
#include "../../bigint.h"
#include "../../perf-timer.h"
////////////////////////////////////////////////////////////////////////////////
namespace po      = boost::program_options;
namespace postyle = boost::program_options::command_line_style;
////////////////////////////////////////////////////////////////////////////////
using memo_t = bigint::bigint;

template <typename T = memo_t>
struct fibmemo_t {

public:

  // define a deque to store the memoization results
  static std::deque<T> memo;

  static T fibmemo(const uint_fast64_t n) {
    // check if the result has already been memoized
    if (memo[n] != 0) {
      return memo[n];
    }
    // base cases
    if (n == 0) {
      memo[0] = 0;
      return 0;
    }
    if (n == 1) {
      memo[1] = 1;
      return 1;
    }

    // recursive cases
    const T result { fibmemo(n - 1) + fibmemo(n - 2) };

    // memoize the result
    memo[n] = result;

    return result;
  }
};
template <typename T>
std::deque<T> fibmemo_t<T>::memo {};


int main(const int argc, const char** argv) {
  po::options_description desc("Options");

  desc.add_options()
          ("n,n",    po::value<uint_fast64_t>()->implicit_value(1)->default_value(1), "the fib number we want to compute")
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

  const uint_fast64_t n { vm["n"].as<uint_fast64_t>() };

  fibmemo_t<memo_t>::memo.resize(n + 1);

  auto elapsedTime { duration_secs(fibmemo_t<memo_t>::fibmemo, 1) };
  elapsedTime = duration_secs(fibmemo_t<memo_t>::fibmemo, n);

  std::cout << "fibmemo(" << n << "): " << fibmemo_t<memo_t>::memo[n] << " took " << elapsedTime << " sec." << std::endl;
  std::cout << "memo size: " << fibmemo_t<memo_t>::memo.size() << "\n";

  return 0;
}
