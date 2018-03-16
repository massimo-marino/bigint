//
// fibonacci.cpp
//
// Created by massimo on 3/16/18.
//

#include <iostream>
#include <boost/program_options.hpp>

#include "fibonacci.h"
////////////////////////////////////////////////////////////////////////////////
namespace po      = boost::program_options;
namespace postyle = boost::program_options::command_line_style;
////////////////////////////////////////////////////////////////////////////////

int
main(const int argc, const char** argv)
{
  po::options_description desc("Options");

  desc.add_options()
          ("n,n", po::value<int32_t>()->implicit_value(1)->default_value(1), "the fib number we want to compute")
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

  const int32_t N = vm["n"].as<int32_t>();
////////////////////////////////////////////////////////////////////////////////

  [[maybe_unused]]
  auto
  fib = [&N]()
  {
    bigint::bigint fib_n;
    bigint::bigint fib_n_1;
    bigint::bigint fib_n_2;
    int32_t n {};

    fib_n_1 = 1;
    fib_n_2 = 0;

    for (n = 2; n <= N; ++n)
    {
      fib_n   = fib_n_1 + fib_n_2;
      fib_n_2 = fib_n_1;
      fib_n_1 = fib_n;
    }
    return fib_n_1;
  };

  [[maybe_unused]]
  auto
  pfib = [&N]()

  {
    bigint::bigint* pfib_n   = new bigint::bigint;
    bigint::bigint* pfib_n_1 = new bigint::bigint;
    bigint::bigint* pfib_n_2 = new bigint::bigint;
    int32_t n {};

    *pfib_n_1 = 1;
    *pfib_n_2 = 0;

    for (n = 2; n <= N; ++n)
    {
      *pfib_n = *pfib_n_1 + *pfib_n_2;
      std::swap(pfib_n_2, pfib_n);
      std::swap(pfib_n_2, pfib_n_1);
    }
    return *pfib_n_1;
  };

  [[maybe_unused]]
  auto
  upfib = [&N]()
  {
    std::unique_ptr<bigint::bigint> upfib_n   = bigint::createUniquePtr();
    std::unique_ptr<bigint::bigint> upfib_n_1 = bigint::createUniquePtr();
    std::unique_ptr<bigint::bigint> upfib_n_2 = bigint::createUniquePtr();
    int32_t n {};

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

  bigint::bigint fN;

  fN = fib();
  std::string fileName {"fib-" + std::to_string(N) + ".txt"};
  utilities::cfile_helper::cfile_helper fs = utilities::cfile_helper::cfile_helper(fileName,
                                               utilities::cfile_helper::cfile_helper::fstream_direction::fs_OUTPUT);
  fs.get_fstream() << fN;

  std::cout << "[" << __func__ << "] "
            << "fib("
            << N
            << ") of length "
            << bigint::numberOfDigits(fN)
            << " digits written to file "
            << fileName
            << std::endl;
  return 0;
}
