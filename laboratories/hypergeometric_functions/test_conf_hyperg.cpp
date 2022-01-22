/**
 *
 */

#include <cmath>
#include <limits>
#include <iostream>
#include <iomanip>

template<typename _Tp>
  void
  test_conf_hyperg(_Tp proto = _Tp{})
  {
    std::cout.precision(emsr::digits10(proto));
    auto width = std::cout.precision() + 8;
    std::cout << std::showpoint << std::scientific;

    auto a = _Tp{6} / _Tp{5};
    auto c = _Tp{1} / _Tp{5};
    const auto del = _Tp{1} / _Tp{10};
    for (int i = -200; i < +200; ++i)
    {
      auto z = del * i;
      std::cout << ' ' << std::setw(6) << z
		<< ' ' << std::setw(width) << __gnu_cxx::conf_hyperg(a, c, z)
		<< '\n';
    }
  }

int
main()
{
}
