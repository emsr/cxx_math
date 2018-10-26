// Special functions -*- C++ -*-

// Copyright (C) 2016-2018 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file bits/sf_parab_cyl.tcc
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{cmath}
 */

//
// ISO C++ 14882 TR29124: Mathematical Special Functions
//

// References:
// (1) Handbook of Mathematical Functions,
//     ed. Milton Abramowitz and Irene A. Stegun,
//     Dover Publications,
//     Section 9, pp. 355-434, Section 10 pp. 435-478
// (2) The Gnu Scientific Library, http://www.gnu.org/software/gsl
// (3) Numerical Recipes in C, by W. H. Press, S. A. Teukolsky,
//     W. T. Vetterling, B. P. Flannery, Cambridge University Press (1992),
//     2nd ed, pp. 240-245

#ifndef _GLIBCXX_BITS_SF_PARAB_CYL_TCC
#define _GLIBCXX_BITS_SF_PARAB_CYL_TCC 1

#include <ext/math_const.h>

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

// Implementation-space details.
namespace __detail
{
  /**
   * Return the prefactors used in parabolic cylinder functions.
   */
  template<typename _Tp>
    std::tuple<_Tp, _Tp, _Tp, _Tp>
    __parabolic_cylinder_factor(_Tp __a)
    {
      const auto _S_pi = __gnu_cxx::__const_pi(std::real(__a));
      const auto _S_sqrt_pi = __gnu_cxx::__const_pi_half(std::real(__a));
      auto __2e14p = std::pow(_Tp{2}, 0.25L + 0.5L * __a);
      auto __2e34p = std::pow(_Tp{2}, 0.75L + 0.5L * __a);
      auto __2e14m = std::pow(_Tp{2}, 0.25L - 0.5L * __a);
      auto __gamma34p = __gamma(0.75L + 0.5L * __a);
      auto __gamma34m = __gamma(0.75L - 0.5L * __a);
      auto __gamma14p = __gamma(0.25L + 0.5L * __a);
      auto __gamma14m = __gamma(0.25L - 0.5L * __a);
      auto __U0 = _S_sqrt_pi / (__2e14p * __gamma34p);
      auto __V0 = -_S_sqrt_pi * __2e14m / __gamma14p;
      auto __Up0 = _S_pi * __2e14p / (__gamma34m * __gamma34m * __gamma14p);
      auto __Vp0 = _S_pi * __2e34p / (__gamma14m * __gamma14m * __gamma34p);
      return std::make_tuple(__U0, __V0, __Up0, __Vp0);
    }

  /**
   * Return the parabolic cylinder functions by series solution.
   */
  template<typename _Tp>
    std::pair<_Tp, _Tp>
    __parabolic_cylinder_series(_Tp __a, _Tp __z)
    {
      const auto _S_eps = __gnu_cxx::__epsilon(std::real(__z));
      constexpr auto _S_max_iter = 1000;
      const auto __zz = __z * __z;
      const auto __ezz4 = std::exp(-__zz / _Tp{4});
      auto __term1 = _Tp{1};
      auto __sum1 = __term1;
      auto __term2 = __z;
      auto __sum2 = __term2;
      for (int __k = 1; __k < _S_max_iter; ++__k)
	{
	  __term1 *= (__a + _Tp(4 * __k - 3) / _Tp{2})
		   * __zz / _Tp(2 * __k * (2 * __k - 1));
	  __sum1 += __term1;
	  __term2 *= (__a + _Tp(4 * __k - 1) / _Tp{2})
		   * __zz / _Tp(2 * __k * (2 * __k + 1));
	  __sum2 += __term2;
	  if (std::abs(__term1) < _S_eps * std::abs(__sum1)
	   && std::abs(__term2) < _S_eps * std::abs(__sum2))
	    break;
	}
      __sum1 *= __ezz4;
      __sum2 *= __ezz4;
      auto __fact = __parabolic_cylinder_factor(__a);
      auto _U = std::get<0>(__fact) * __sum1 + std::get<2>(__fact) * __sum2;
      auto _V = std::get<1>(__fact) * __sum1 + std::get<3>(__fact) * __sum2;

      return std::make_pair(_U, _V);
    }

  /**
   * Return the parabolic cylinder functions by asymptotic series solution.
   */
  template<typename _Tp>
    std::pair<_Tp, _Tp>
    __parabolic_cylinder_asymp(_Tp __a, _Tp __z)
    {
      const auto _S_eps = __gnu_cxx::__epsilon(std::real(__z));
      constexpr auto _S_max_iter = 1000;
      constexpr auto _S_1d2 = _Tp{1} / _Tp{2};
      const auto _S_sqrt_pi = __gnu_cxx::__const_root_pi(std::real(__z));
      const auto _S_2dsqrt_pi = _Tp{2} / _S_sqrt_pi;
      const auto __zz = __z * __z;
      const auto __i2zz = _Tp{1} / (_Tp{2} * __z * __z);
      const auto __ezz4 = std::exp(-__zz / _Tp{4});
      const auto __pow = std::pow(__z, -__a - _S_1d2);
      auto __term1 = _Tp{1};
      auto __sum1 = __term1;
      auto __term2 = _Tp{1};
      auto __sum2 = __term2;
      for (auto __s = 1; __s < _S_max_iter; ++__s)
	{
	  __term1 *= -(__a + _S_1d2 + 2 * (__s - 1))
		  * (__a + _S_1d2 + 2 * (__s - 1) + 1) * __i2zz / __s;
	  __sum1 += __term1;
	  __term2 *= (__a - _S_1d2 + 2 * (__s - 1))
		  * (__a - _S_1d2 + 2 * (__s - 1) + 1) * __i2zz / __s;
	  __sum2 += __term2;
	  if (std::abs(__term1) < _S_eps * std::abs(__sum1)
	   && std::abs(__term2) < _S_eps * std::abs(__sum2))
	    break;
	}
      auto _U = __ezz4 * __pow * __sum1;
      auto _V = _S_2dsqrt_pi * __sum2 / __ezz4 / __pow / __z;

      return std::make_pair(_U, _V);
    }

  /**
   * 
   */
  template<typename _Tp>
    std::pair<_Tp, _Tp>
    __parabolic_cylinder(_Tp __a, _Tp __z)
    {
      constexpr auto _S_magic_switch = _Tp{10};
      if (std::abs(__z) < _S_magic_switch)
	return __parabolic_cylinder_series(__a, __z);
      else
	return __parabolic_cylinder_asymp(__a, __z);
    }

  /**
   * 
   */
  template<typename _Tp>
    _Tp
    __parabolic_cyl_u(_Tp __a, _Tp __z)
    {
      if (std::isnan(__a) || std::isnan(__z))
	return __gnu_cxx::__quiet_NaN<_Tp>();
      else
        return __parabolic_cylinder(__a, __z).first;
    }

  /**
   * 
   */
  template<typename _Tp>
    _Tp
    __parabolic_cyl_v(_Tp __a, _Tp __z)
    {
      if (std::isnan(__a) || std::isnan(__z))
	return __gnu_cxx::__quiet_NaN<_Tp>();
      else
        return __parabolic_cylinder(__a, __z).second;
    }

  /**
   *  
   */
  template<typename _Tp>
    _Tp
    __parabolic_cyl_w(_Tp __a, _Tp __z)
    {
      return _Tp{0};
    }
} // namespace __detail

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std

#endif // _GLIBCXX_BITS_SF_PARAB_CYL_TCC
