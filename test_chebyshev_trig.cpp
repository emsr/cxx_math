/*
$HOME/bin_specfun/bin/g++ -std=gnu++17 -g -Wall -Wextra -Wno-psabi -I. -o test_chebyshev_trig test_chebyshev_trig.cpp -lquadmath
./test_chebyshev_trig > test_chebyshev_trig.txt

$HOME/bin/bin/g++ -std=gnu++17 -g -Wall -Wextra -Wno-psabi -I. -o test_chebyshev_trig test_chebyshev_trig.cpp -lquadmath
./test_chebyshev_trig > test_chebyshev_trig.txt
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#include <bits/float128_io.h>

  /**
   * Return the Chebyshev polynomial of the first kind
   * of order @f$ n @f$, @f$ T_n(x) @f$ by trigonometric identity:
   * @f[
   *   T_n(x) = \cos(n\theta)
   * @f]
   * where @f$ \theta = \acos(x) @f$.
   */
  template<typename _Tp>
    _Tp
    __chebyshev_t_trig(unsigned int __n, _Tp __x)
    {
      if (std::abs(__x) <= _Tp{1})
	{
	  auto __theta = std::acos(__x);
	  return std::cos(__n * __theta);
	}
      else if (__x > _Tp{1})
	{
	  auto __theta = std::acosh(__x);
	  return std::cosh(__n * __theta);
	}
      else
	{
	  auto __theta = std::acosh(-__x);
	  return (__n & 1 ? _Tp{-1} : _Tp{+1}) * std::cosh(__n * __theta);
	}
    }

  /**
   * Return a vector of zeros of the Chebyshev function of the first kind
   * of order @f$ n @f$, @f$ T_n(x) @f$.
   * The zeros are given by:
   * @f[
   *   x_k = \cos\left(\frac{(k+\frac{1}{2})\pi}{n+1}\right),
   *     k \elem {1, ..., n}
   * @f]
   */
  template<typename _Tp>
    std::vector<__gnu_cxx::__quadrature_point_t<_Tp>>
    __chebyshev_t_zeros(unsigned int __n)
    {
      const auto _S_pi = __gnu_cxx::__const_pi<_Tp>();
      std::vector<__gnu_cxx::__quadrature_point_t<_Tp>> __pt(__n);
      for (unsigned int __k = 0; __k < __n; ++__k)
	{
	  __pt[__k].__zero = __gnu_cxx::cos_pi(_Tp(__k + 0.5L) / _Tp(__n));
	  __pt[__k].__weight = _S_pi / __n;
	}
      return __pt;
    }

  /**
   * Return the Chebyshev polynomial of the second kind
   * of order @f$ n @f$, @f$ U_n(x) @f$ by trigonometric identity:
   * @f[
   *   U_n(x) = \frac{\sin((n + 1)\theta)}{\sin(\theta)}
   * @f]
   * where @f$ \theta = \acos(x) @f$.
   */
  template<typename _Tp>
    _Tp
    __chebyshev_u_trig(unsigned int __n, _Tp __x)
    {
      const auto _S_eps = __gnu_cxx::__epsilon(__x);
      if (std::abs(__x + _Tp{1}) < _S_eps)
	return (__n % 2 == 0 ? +1 : -1) * _Tp(__n + 1);
      else if (std::abs(__x - _Tp{1}) < _S_eps)
	return _Tp(__n + 1);
      else if (std::abs(__x) < _Tp{1})
	{
	  auto __theta = std::acos(__x);
	  return std::sin(_Tp(__n + 1) * __theta)
	       / std::sin(__theta);
	}
      else if (__x > _Tp{1})
	{
	  auto __theta = std::acosh(__x);
	  return std::sinh(_Tp(__n + 1) * __theta)
	       / std::sinh(__theta);
	}
      else
	{
	  auto __theta = std::acosh(-__x);
	  return (__n & 1 ? _Tp{-1} : _Tp{+1})
	       * std::sinh(_Tp(__n + 1) * __theta)
	       / std::sinh(__theta);
	}
    }

  /**
   * Return a vector of zeros of the Chebyshev function of the second kind
   * of order @f$ n @f$, @f$ U_n(x) @f$.
   * The zeros are given by:
   * @f[
   *   x_k = \cos\left(\frac{k\pi}{n+1}\right), k \elem {1, ..., n}
   * @f]
   */
  template<typename _Tp>
    std::vector<__gnu_cxx::__quadrature_point_t<_Tp>>
    __chebyshev_u_zeros(unsigned int __n)
    {
      const auto _S_pi = __gnu_cxx::__const_pi<_Tp>();
      std::vector<__gnu_cxx::__quadrature_point_t<_Tp>> __pt(__n);
      for (unsigned int __k = 1; __k <= __n; ++__k)
	{
	  auto __arg = _Tp(__k) / _Tp(__n + 1);
	  auto __half = __gnu_cxx::__fp_is_equal<_Tp>(__arg, _Tp{0.5L});
	  auto __z = (__half ? _Tp{0} : __gnu_cxx::cos_pi(__arg));
	  auto __w = _S_pi * (_Tp{1} - __z * __z) / _Tp(__n + 1);
	  __pt[__k - 1].__zero = __z;
	  __pt[__k - 1].__weight = __w;
	}
      return __pt;
    }

  /**
   * Return the Chebyshev polynomial of the third kind
   * of order @f$ n @f$, @f$ V_n(x) @f$ by trigonometric identity:
   * @f[
   *   V_n(x) = \frac{\cos((n + \frac{1}{2})\theta)}
   *                 {cos(\frac{1}{2}\theta)}
   * @f]
   * where @f$ \theta = \acos(x) @f$.
   */
  template<typename _Tp>
    _Tp
    __chebyshev_v_trig(unsigned int __n, _Tp __x)
    {
      const auto _S_eps = __gnu_cxx::__epsilon(__x);
      if (std::abs(__x + _Tp{1}) < _S_eps)
	return (__n % 2 == 0 ? +1 : -1) * _Tp(2 * __n + 1);
      else if (std::abs(__x) <= _Tp{1})
	{
	  auto __theta = std::acos(__x);
	  return std::cos(_Tp(__n + 0.5L) * __theta)
	       / std::cos(_Tp{0.5L} * __theta);
	}
      else if (__x > _Tp{1})
	{
	  auto __theta = std::acosh(__x);
	  return std::cosh(_Tp(__n + 0.5L) * __theta)
	       / std::cosh(_Tp{0.5L} * __theta);
	}
      else
	{
	  auto __theta = std::acosh(-__x);
	  return (__n % 2 == 0 ? +1 : -1)
	       * std::sinh(_Tp(__n + 0.5L) * __theta)
	       / std::sinh(_Tp{0.5L} * __theta);
	}
    }

  /**
   * Return a vector of zeros of the Chebyshev function of the third kind
   * of order @f$ n @f$, @f$ V_n(x) @f$.
   * The zeros are given by:
   * @f[
   *   x_k = \cos\left(\frac{\left(k+\frac{1}{2}\right)\pi}{n+\frac{1}{2}}\right),
   *       k \elem {1, ..., n}
   * @f]
   */
  template<typename _Tp>
    std::vector<__gnu_cxx::__quadrature_point_t<_Tp>>
    __chebyshev_v_zeros(unsigned int __n)
    {
      const auto _S_pi = __gnu_cxx::__const_pi<_Tp>();
      std::vector<__gnu_cxx::__quadrature_point_t<_Tp>> __pt(__n);
      for (unsigned int __k = 0; __k < __n; ++__k)
	{
	  auto __z = __gnu_cxx::cos_pi(_Tp(__k + 0.5L) / _Tp(__n + 0.5L));
	  auto __w = _S_pi * (_Tp{1} + __z) / (_Tp(__n) + _Tp{1} / _Tp{2});
	  __pt[__k].__zero = __z;
	  __pt[__k].__weight = __w;
	}
      return __pt;
    }

  /**
   * Return the Chebyshev polynomial of the fourth kind
   * of order @f$ n @f$, @f$ W_n(x) @f$ by trigonometric identity:
   * @f[
   *   W_n(x) = \frac{\sin((n + \frac{1}{2})\theta)}
   *                 {\sin(\frac{1}{2}\theta)}
   * @f]
   * where @f$ \theta = \acos(x) @f$.
   */
  template<typename _Tp>
    _Tp
    __chebyshev_w_trig(unsigned int __n, _Tp __x)
    {
      const auto _S_eps = __gnu_cxx::__epsilon(__x);
      if (std::abs(__x - _Tp{1}) < _S_eps)
	return _Tp(2 * __n + 1);
      else if (std::abs(__x) <= _Tp{1})
	{
	  auto __theta = std::acos(__x);
	  return std::sin(_Tp(__n + 0.5L) * __theta)
	       / std::sin(_Tp{0.5L} * __theta);
	}
      else if (__x > _Tp{1})
	{
	  auto __theta = std::acosh(__x);
	  return std::sinh(_Tp(__n + 0.5L) * __theta)
	       / std::sinh(_Tp{0.5L} * __theta);
	}
      else
	{
	  auto __theta = std::acosh(-__x);
	  return (__n % 2 == 0 ? +1 : -1)
	       * std::cosh(_Tp(__n + 0.5L) * __theta)
	       / std::cosh(_Tp{0.5L} * __theta);
	}
    }

  /**
   * Return a vector of zeros of the Chebyshev function of the fourth kind
   * of order @f$ n @f$, @f$ W_n(x) @f$.
   * The zeros are given by:
   * @f[
   *   x_k = \cos\left(\frac{k\pi}{n+\frac{1}{2}}\right),
   *       k \elem {1, ..., n}
   * @f]
   */
  template<typename _Tp>
    std::vector<__gnu_cxx::__quadrature_point_t<_Tp>>
    __chebyshev_w_zeros(unsigned int __n)
    {
      const auto _S_pi = __gnu_cxx::__const_pi<_Tp>();
      std::vector<__gnu_cxx::__quadrature_point_t<_Tp>> __pt(__n);
      for (unsigned int __k = 1; __k <= __n; ++__k)
	{
	  auto __z = __gnu_cxx::cos_pi(_Tp(__k) / _Tp(__n + 0.5L));
	  auto __w = _S_pi * (_Tp{1} - __z) / (_Tp(__n) + _Tp{1} / _Tp{2});
	  __pt[__k - 1].__zero = __z;
	  __pt[__k - 1].__weight = __w;
	}
      return __pt;
    }


template<typename Tp>
  void
  test_chebyshev(Tp proto = Tp{})
  {
    std::cout.precision(__gnu_cxx::__digits10(proto));
    std::cout << std::showpoint << std::scientific;
    auto width = 8 + std::cout.precision();

    std::vector<unsigned int> index{0, 1, 2, 3, 4, 5, 10, 20, 23, 50, 100};

    for (auto n : index)
      {
	std::cout << "\n n = " << std::setw(width) << n << '\n';
	std::cout << ' ' << std::setw(width) << "x"
		  << ' ' << std::setw(width) << "Tt"
		  << ' ' << std::setw(width) << "Tg"
		  << ' ' << std::setw(width) << "Ut"
		  << ' ' << std::setw(width) << "Ug"
		  << ' ' << std::setw(width) << "Vt"
		  << ' ' << std::setw(width) << "Vg"
		  << ' ' << std::setw(width) << "Wt"
		  << ' ' << std::setw(width) << "Wg"
		  << ' ' << std::setw(width) << "Tt - Tg"
		  << ' ' << std::setw(width) << "Ut - Ug"
		  << ' ' << std::setw(width) << "Vt - Vg"
		  << ' ' << std::setw(width) << "Wt - Wg"
		  << '\n';
	const auto del = Tp{1} / Tp{100};
	for (int i = -150; i <= 150; ++i)
	  {
	    auto x = del * i;
	    auto Tt = __chebyshev_t_trig(n, x);
	    auto Ut = __chebyshev_u_trig(n, x);
	    auto Vt = __chebyshev_v_trig(n, x);
	    auto Wt = __chebyshev_w_trig(n, x);
	    auto Tg = __gnu_cxx::chebyshev_t(n, x);
	    auto Ug = __gnu_cxx::chebyshev_u(n, x);
	    auto Vg = __gnu_cxx::chebyshev_v(n, x);
	    auto Wg = __gnu_cxx::chebyshev_w(n, x);
	    std::cout << ' ' << std::setw(width) << x
		      << ' ' << std::setw(width) << Tt
		      << ' ' << std::setw(width) << Tg
		      << ' ' << std::setw(width) << Ut
		      << ' ' << std::setw(width) << Ug
		      << ' ' << std::setw(width) << Vt
		      << ' ' << std::setw(width) << Vg
		      << ' ' << std::setw(width) << Wt
		      << ' ' << std::setw(width) << Wg
		      << ' ' << std::setw(width) << Tt - Tg
		      << ' ' << std::setw(width) << Ut - Ug
		      << ' ' << std::setw(width) << Vt - Vg
		      << ' ' << std::setw(width) << Wt - Wg
		      << '\n';
	  }
      }

    std::cout << "\n\nZeros of Chebyshev T_n(x)\n";
    for (auto n : index)
      {
	std::cout << "\n n = " << std::setw(width) << n << '\n';
	auto tz = __chebyshev_t_zeros<Tp>(n);
	for (auto z : tz)
	  {
	    auto Tt = __chebyshev_t_trig(n, z.__zero);
	    auto Tg = __gnu_cxx::chebyshev_t(n, z.__zero);
	    std::cout << ' ' << std::setw(width) << z.__zero
		      << ' ' << std::setw(width) << z.__weight
		      << ' ' << std::setw(width) << Tt
		      << ' ' << std::setw(width) << Tg
		      << '\n';
	  }
      }

    std::cout << "\n\nZeros of Chebyshev U_n(x)\n";
    for (auto n : index)
      {
	std::cout << "\n n = " << std::setw(width) << n << '\n';
	auto uz = __chebyshev_u_zeros<Tp>(n);
	for (auto z : uz)
	  {
	    auto Ut = __chebyshev_u_trig(n, z.__zero);
	    auto Ug = __gnu_cxx::chebyshev_u(n, z.__zero);
	    std::cout << ' ' << std::setw(width) << z.__zero
		      << ' ' << std::setw(width) << z.__weight
		      << ' ' << std::setw(width) << Ut
		      << ' ' << std::setw(width) << Ug
		      << '\n';
	  }
      }

    std::cout << "\n\nZeros of Chebyshev V_n(x)\n";
    for (auto n : index)
      {
	std::cout << "\n n = " << std::setw(width) << n << '\n';
	auto vz = __chebyshev_v_zeros<Tp>(n);
	for (auto z : vz)
	  {
	    auto Vt = __chebyshev_v_trig(n, z.__zero);
	    auto Vg = __gnu_cxx::chebyshev_v(n, z.__zero);
	    std::cout << ' ' << std::setw(width) << z.__zero
		      << ' ' << std::setw(width) << z.__weight
		      << ' ' << std::setw(width) << Vt
		      << ' ' << std::setw(width) << Vg
		      << '\n';
	  }
      }

    std::cout << "\n\nZeros of Chebyshev W_n(x)\n";
    for (auto n : index)
      {
	std::cout << "\n n = " << std::setw(width) << n << '\n';
	auto wz = __chebyshev_w_zeros<Tp>(n);
	for (auto z : wz)
	  {
	    auto Wt = __chebyshev_w_trig(n, z.__zero);
	    auto Wg = __gnu_cxx::chebyshev_w(n, z.__zero);
	    std::cout << ' ' << std::setw(width) << z.__zero
		      << ' ' << std::setw(width) << z.__weight
		      << ' ' << std::setw(width) << Wt
		      << ' ' << std::setw(width) << Wg
		      << '\n';
	  }
      }
  }

int
main()
{
  using Tp = __float128;

  test_chebyshev(1.0);

  std::cout.precision(__gnu_cxx::__digits10<Tp>());
  std::cout << std::showpoint << std::scientific;
  auto width = 8 + std::cout.precision();
  std::cout << "\n\nZeros of Chebyshev U_23(x) for qcheb_integrate\n";
  for (auto n : {23})
    {
      auto uz = __chebyshev_u_zeros<Tp>(n);
      for (auto z : uz)
	{
	  std::cout << ' ' << std::setw(width) << z.__zero
		    << ' ' << std::setw(width) << z.__weight
		    << '\n';
	}
    }
}
