/**
 *
 */

#include <iostream>
#include <iomanip>

#include <cmath>
#include <bits/complex_util.h>
//#include <hankel.h>
#include <bits/float128_io.h>


  template<typename _Tp>
    inline std::complex<_Tp>
    operator/(const std::complex<_Tp>& __x, const __complex__ & __y)
    {
      std::complex<_Tp> __r = __x;
      __r /= std::complex<_Tp>(__y);
      return __r;
    }

int
main()
{
  using namespace std::literals::complex_literals;
  std::complex<double> z, nu;
  std::__detail::_Airy<std::complex<double>> airy_thing;

  std::cout.precision(std::numeric_limits<double>::max_digits10);
  auto width = 6 + std::cout.precision();

  nu = 5.0;
  z = 1.0 - 3.0i;

  try
  {
    // Cool but we nead an eater.
    auto [zx, nux, h1, h2, h1p, h2p] = std::__detail::__hankel_uniform(nu, z);

    std::cout << '\n';
    std::cout << " nu     = " << std::setw(width) << nu << '\n';
    std::cout << " z      = " << std::setw(width) << z << '\n';
    std::cout << " H1(z)  = " << std::setw(width) << h1 << '\n';
    std::cout << " H1'(z) = " << std::setw(width) << h1p << '\n';
    std::cout << " H2(z)  = " << std::setw(width) << h2 << '\n';
    std::cout << " H2'(z) = " << std::setw(width) << h2p << '\n';
    std::cout << " J(z)   = " << std::setw(width) << (h1 + h2) / 2.0 << '\n';
    std::cout << " J'(z)  = " << std::setw(width) << (h1p + h2p) / 2.0 << '\n';
    std::cout << " Y(z)   = " << std::setw(width) << (h1 - h2) / 2.0i << '\n';
    std::cout << " Y'(z)  = " << std::setw(width) << (h1p - h2p) / 2.0i << '\n';
  }
  catch (std::exception & err)
  {
    std::cerr << "Error in test_hankel (hankel_uniform): " << err.what() << '\n';
  }

  try
  {
    auto Airy = airy_thing(z);
    std::cout << '\n';
    std::cout << " z      = " << std::setw(width) << Airy.__z << '\n';
    std::cout << " Ai(z)  = " << std::setw(width) << Airy.__Ai_value << '\n';
    std::cout << " Ai'(z) = " << std::setw(width) << Airy.__Ai_deriv << '\n';
    std::cout << " Bi(z)  = " << std::setw(width) << Airy.__Bi_value << '\n';
    std::cout << " Bi'(z) = " << std::setw(width) << Airy.__Bi_deriv << '\n';
  }
  catch (std::exception & err)
  {
    std::cerr << "Error in test_hankel (airy): " << err.what() << '\n';
  }
}
