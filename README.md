# bigint

C++17 implementation of arbitrary precision integer arithmetic.


This implementation is a re-implementation from:

`https://sites.google.com/site/indy256/algo_cpp/bigint`

However, this site is no more reachable.

You can get back past snapshots from the Internet Archive:

`https://web.archive.org/web/20210301000000*/https://sites.google.com/site/indy256/algo_cpp/bigint`

March 19 2021:

`https://web.archive.org/web/20210319023614/https://sites.google.com/site/indy256/algo_cpp/bigint`

October 24 2011:

`https://web.archive.org/web/20111024050800/https://sites.google.com/site/indy256/algo_cpp/bigint`

February 8 2011:

`https://web.archive.org/web/20110208155854/https://sites.google.com/site/indy256/algo_cpp/bigint`

Snapshot from March 19 2921 can be found in the folder `src/original`


## Requirements

`cmake 3.26.3` is used to compile the sources.

The cmake files compile with `-std=c++17`.

The unit tests are implemented in `googletest`: be sure you have installed `googletest` to compile.

To compile the example fibonacci, you need to install Boost's `libboost-filesystem-dev`, `libboost-program-options-dev`.


## Install and Run Unit Tests

```bash
$ git clone https://github.com:massimo-marino/bigint.git
$ cd bigint
$ mkdir build
$ cd build
$ cmake ..
$ make
$ cd src/unitTests
$ ./bigint-unit-tests
```

## Example: Fibonacci
To run the example:

```bash
$ cd build/src/fibonacci
$ ./fibonacci --help
$ ./fibonacci -n 1000000
[main] fib(1000000) of length 208988 digits written to file fib-1000000.txt
$
```

If you want to verify the results, there's a Julia script `fib.jl` in `src/fibonacci/julia/`

From there (and after having installed Julia), run:

```bash
$ julia -i fib.jl

julia> fib(100)
354224848179261915075

julia> fib(1000000)
354224848179261915075...omitted...411568996526838242546875

julia>
```


## How to Use it

See the source code and the unit tests for examples of use.
