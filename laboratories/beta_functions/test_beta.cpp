/*
$HOME/bin/bin/g++ -std=gnu++2a -g -Wall -Wextra -Wno-psabi -I. -o test_beta test_beta.cpp -lquadmath -Lwrappers/debug -lwrap_boost
LD_LIBRARY_PATH=wrappers/debug:$LD_LIBRARY_PATH ./test_beta > test_beta.txt

$HOME/bin/bin/g++ -std=gnu++2a -g -Wall -Wextra -I. -o test_beta test_beta.cpp -lquadmath -Lwrappers/debug -lwrap_boost
./test_beta > test_beta.txt
*/

#include <cmath>
#include <bits/float128_io.h>
#include <limits>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <complex>

#include "wrap_boost.h"

template<typename _Tp>
  void
  test_beta(_Tp proto = _Tp{})
  {
    //using _Val = _Tp;
    //using _Real = std::__detail::__num_traits_t<_Val>;

    std::cout.precision(__gnu_cxx::__digits10(proto));
    std::cout << std::showpoint << std::scientific;
    auto width = 8 + std::cout.precision();

    std::cout << '\n'
	      << ' ' << std::setw(width) << "a"
	      << ' ' << std::setw(width) << "b"
	      << ' ' << std::setw(width) << "__beta"
	      << ' ' << std::setw(width) << "boost::beta"
	      << ' ' << std::setw(width) << "delta_boost"
	      << '\n';
    int i_min = 1;
    for (int i = i_min; i <= +500; ++i)
      {
	auto a = _Tp{0.1Q} * i;
	int j_min = 1;
	for (int j = j_min; j <= +500; ++j)
	  {
	    auto b = _Tp{0.1Q} * j;
	    auto gbet = std::__detail::__beta(a, b);
	    auto bbet = beast::beta(a, b);
	    std::cout << ' ' << std::setw(width) << a
		      << ' ' << std::setw(width) << b
		      << ' ' << std::setw(width) << gbet
		      << ' ' << std::setw(width) << bbet
		      << ' ' << std::setw(width) << (gbet - bbet) / std::abs(bbet)
		      << '\n';
	  }
      }
  }

template<typename _Tp>
  void
  plot_beta(std::string filename)
  {
    using _Val = _Tp;
    using _Real = std::__detail::__num_traits_t<_Val>;

    auto data = std::ofstream(filename);

    data.precision(std::numeric_limits<_Real>::digits10);
    data << std::showpoint << std::scientific;
    auto width = 8 + data.precision();

    int i_min = -150;
    for (int i = i_min; i <= +150; ++i)
      {
	auto a = _Tp{0.02L} * i;
	int j_min = -150;
	data << '\n';
	for (int j = j_min; j <= +150; ++j)
	  {
	    auto b = _Tp{0.02L} * j;
	    auto gbet = std::__detail::__beta(a, b);
	    data << ' ' << std::setw(width) << a
		 << ' ' << std::setw(width) << b
		 << ' ' << std::setw(width) << gbet
		 << '\n';
	  }
      }
  }

int
main()
{
  std::__detail::__beta(0.1F, 1.9F);
  std::__detail::__beta(0.1F, 35.1F);

  test_beta<float>();

  test_beta<double>();

  test_beta<long double>();

  test_beta<__float128>();

  // Beta seems to be either really tiny or really huge.
  // Maybe graph log_beta.
  plot_beta<double>("plot_data/beta_double.txt");
}
