// Math extensions -*- C++ -*-

// Copyright (C) 2016-2019 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file ext/root_finding.tcc
 *  This file is a GNU extension to the Standard C++ Library.
 */

#ifndef _EXT_ROOT_SEARCH_TCC
#define _EXT_ROOT_SEARCH_TCC 1

#pragma GCC system_header

#include <stdexcept>
#include <cmath>
#include <tuple> // For tie.

#include <ext/math_constants.h>

namespace __gnu_cxx _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /**
   * Given a function @c __func and an initial range @c __x_lower
   * to @c __x_upper, the routine expands the range geometrically until a root
   * is bracketed by the returned values @c __x_lower and @c __x_upper
   * (in which case __root_bracket returns true)
   * or until the range becomes unacceptably large
   * (in which case __root_bracket returns false).
   * Success is guaranteed for a function which has opposite signs
   * for sufficiently large and small arguments.
   *
   * @param __func  A simple one-argument function returning a value.
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _Func>
    bool
    __root_bracket(_Func __func, _Tp& __x_lower, _Tp& __x_upper,
		   std::size_t __max_iter)
    {
      const _Tp __golden = __gnu_cxx::math::__phi_v<_Tp>;

      if (__x_lower >= __x_upper)
	std::__throw_domain_error(__N("__root_bracket: "
				      "Initial range must be ordered"));
      auto __f_lower = __func(__x_lower);
      auto __f_upper = __func(__x_upper);
      for (std::size_t __i = 0; __i < __max_iter; ++__i)
	{
	  if (__f_lower * __f_upper < _Tp{0})
	    return true;
	  if (std::abs(__f_lower) < std::abs(__f_upper))
	    __f_lower = __func(__x_lower += __golden * (__x_lower - __x_upper));
	  else
	    __f_upper = __func(__x_upper += __golden * (__x_upper - __x_lower));
	}
      return false;
    }


  /**
   * Given a function @c __func defined on an interval @c __x_lower
   * to @c __x_upper, the routine subdivides the interval
   * into @c n equally-spaced segments and searches for zero crossings
   * of the function.
   *
   * @param __func  A simple one-argument function returning a value.
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __n  The number of subdivisions of the interval
   * @param __xb  The output vector of root bounds
   */
  template<typename _Tp, typename _Func>
    std::vector<std::pair<_Tp, _Tp>>
    __root_brackets(_Func __func,
		    _Tp __x_lower, _Tp __x_upper, std::size_t __n)
    {
      std::vector<std::pair<_Tp, _Tp>> __xb;
      auto __dx = (__x_upper - __x_lower) / _Tp(__n);
      auto __x = __x_lower;
      auto __f_lo = __func(__x);
      for (std::size_t __i = 0; __i < __n; ++__i)
	{
	  __x += __dx;
	  auto __f_hi = __func(__x);
	  if (__f_lo * __f_hi <= _Tp{0})
	    __xb.emplace_back(__x - __dx, __x);
	  __f_lo = __f_hi;
	}

      return __xb;
    }


  /**
   * Using bisection, find the root of a function @c __func
   * known to lie between @c __x_lower and @c __x_upper.
   * The returned root is refined until its accuracy is <tt>+/- __eps</tt>.
   *
   * @param __func  A simple one-argument function returning a value.
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __eps  The tolerance
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _Func>
    _Tp
    __root_bisect(_Func __func, _Tp __x_lower, _Tp __x_upper,
		  _Tp __eps, std::size_t __max_iter)
    {
      auto __f = __func(__x_lower);
      auto __f_mid = __func(__x_upper);
      if (__f * __f_mid > _Tp{0})
	std::__throw_domain_error(__N("__root_bisect: "
				      "Root must be bracketed for bisection"));
      //  Orient search so that f > 0 lies at x + dx.
      auto __dx = __f < _Tp{0} ? __x_upper - __x_lower : __x_lower - __x_upper;
      auto __x = __f < _Tp{0} ? __x_lower : __x_upper;
      for (std::size_t __i = 0; __i < __max_iter; ++__i)
	{
	  __dx /= _Tp{2};
	  auto __x_mid = __x + __dx;
	  __f_mid = __func(__x_mid);
	  if (__f_mid < _Tp{0})
	    __x = __x_mid;
	  if (std::abs(__dx) < __eps || __f_mid == _Tp{0})
	    return __x_mid;
	}

      std::__throw_runtime_error(__N("__root_bisect: "
				     "Maximum number of bisections exceeded"));
    }


  /**
   * Using the secant method, find the root of a function @c __func
   * known to lie between @c __x_lower and @c __x_upper.
   * The returned root is refined until its accuracy is <tt>+/- __eps</tt>.
   *
   * @param __func  A simple one-argument function returning a value.
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __eps  The tolerance
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _Func>
    _Tp
    __root_secant(_Func __func, _Tp __x_lower, _Tp __x_upper,
		  _Tp __eps, std::size_t __max_iter)
    {
      _Tp __x_lo, __x;

      auto __f_lo = __func(__x_lower);
      auto __f = __func(__x_upper);
      if (std::abs(__f_lo) < std::abs(__f))
	{
	  __x = __x_lower;
	  __x_lo = __x_upper;
	  std::swap(__f_lo, __f);
	}
      else
	{
	  __x_lo = __x_lower;
	  __x = __x_upper;
	}

      for (std::size_t __i = 0; __i < __max_iter; ++__i)
	{
	  auto __dx = (__x_lo - __x) * __f / (__f - __f_lo);
	  __x_lo = __x;
	  __f_lo = __f;
	  __x += __dx;
	  __f = __func(__x);
	  if (std::abs(__dx) < __eps || __f == _Tp{0})
	    return __x;
	}

      std::__throw_runtime_error(__N("__root_secant: "
				     "Maximum number of iterations exceeded"));
    }


  /**
   * Using the false position method, find the root of a function @c __func
   * known to lie between @c __x_lower and @c __x_upper.
   * The returned root is refined until its accuracy is <tt>+/- __eps</tt>.
   *
   * @param __func  A simple one-argument function returning a value.
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __eps  The tolerance
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _Func>
    _Tp
    __root_false_position(_Func __func, _Tp __x_lower, _Tp __x_upper,
			  _Tp __eps, std::size_t __max_iter)
    {
      auto __f_lo = __func(__x_lower);
      auto __f_hi = __func(__x_upper);
      if (__f_lo * __f_hi > _Tp{0})
	std::__throw_domain_error(__N("__root_false_position: "
				      "Root must be bracketed"));

      _Tp __x_lo, __x_hi;
      if (__f_lo < _Tp{0})
	{
	  __x_lo = __x_lower;
	  __x_hi = __x_upper;
	}
      else
	{ 
	  __x_lo = __x_upper;
	  __x_hi = __x_lower;
	  std::swap(__f_lo, __f_hi);
	}

      auto __dx = __x_hi - __x_lo;
      for (std::size_t __i = 0; __i < __max_iter; ++__i)
	{
	  auto __x = __x_lo + __dx * __f_lo / (__f_lo - __f_hi);
	  auto __f = __func(__x);
	  _Tp __del;
	  if (__f < _Tp{0})
	    {
	      __del = __x_lo - __x;
	      __x_lo = __x;
	      __f_lo = __f;
	    }
	  else
	    {
	      __del = __x_hi - __x;
	      __x_hi = __x;
	      __f_hi = __f;
	    }
	  __dx = __x_hi - __x_lo;
	  if (std::abs(__del) < __eps || __f == _Tp{0})
	    return __x;
	}

      std::__throw_runtime_error(__N("__root_false_position: "
				     "Maximum number of iterations exceeded"));
    }


  /**
   * Using Ridder's method, find the root of a function @c __func known
   * to lie between @c __x_lower and @c __x_upper.
   * The returned root is refined until its accuracy is <tt>+/- __eps</tt>.
   *
   * @param __func  A simple one-argument function returning a value.
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __eps  The tolerance
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _Func>
    _Tp
    __root_ridder(_Func __func, _Tp __x_lower, _Tp __x_upper,
		  _Tp __eps, std::size_t __max_iter)
    {
      auto __f_hi = __func(__x_upper);
      auto __f_lo = __func(__x_lower);
      auto __x_hi = __x_upper;
      auto __x_lo = __x_lower;

      if (__f_lo * __f_hi > _Tp{0})
	std::__throw_domain_error(__N("__root_ridder: Root must be bracketed"));

      if (__f_lo == _Tp{0})
	return __x_lower;

      if (__f_hi == _Tp{0})
	return __x_upper;

      const _Tp __UNUSED = -1.0e30; // an exceedingly unlikely answer.
      auto __ans = __UNUSED;
      for (std::size_t __i = 0; __i < __max_iter; ++__i)
	{
	  auto __xm = (__x_lo + __x_hi) / _Tp{2};
	  auto __fm = __func(__xm);
	  auto __s = std::sqrt(__fm * __fm - __f_lo * __f_hi);
	  if (__s == _Tp{0})
	    return __ans;
	  auto __xnew = __xm + (__xm - __x_lo)
		      * (__f_lo >= __f_hi ? 1.0 : -1.0) * __fm / __s;
	  if (std::abs(__xnew - __ans) < __eps)
	    return __ans;
	  __ans = __xnew;
	  auto __fnew = __func(__ans);
	  if (__fnew == _Tp{0})
	    return __ans;
	  if (std::copysign(__fm, __fnew) != __fm)
	    {
	      __x_lo = __xm;
	      __f_lo = __fm;
	      __x_hi = __xnew;
	      __f_hi = __fnew;
	    }
	  else if (std::copysign(__f_lo, __fnew) != __f_lo)
	    {
	      __x_hi = __ans;
	      __f_hi = __fnew;
	    }
	  else if (std::copysign(__f_hi, __fnew) != __f_hi)
	    {
	      __x_lo = __ans;
	      __f_lo = __fnew;
	    }
	  else
	    std::__throw_runtime_error(__N("__root_ridder: "
					   "Some major malfunction"));

	  if (std::abs(__x_hi - __x_lo) < __eps)
	    return __ans;
	}

      std::__throw_runtime_error(__N("__root_ridder: "
				     "Maximum number of iterations exceeded"));
    }


  /**
   * Using Brent's method, find the root of a function @c __func known
   * to lie between @c __x_lower and @c __x_upper.
   * The returned root is refined until it's accuracy is <tt>+/- __eps</tt>.
   *
   * @param __func  A simple one-argument function returning a value.
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __eps  The tolerance
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _Func>
    _Tp
    __root_brent(_Func __func, _Tp __x_lower, _Tp __x_upper,
		 _Tp __eps, std::size_t __max_iter)
    {
      auto __x_a = __x_lower;
      auto __x_b = __x_upper;
      auto __x_c = __x_upper;
      auto __f_a = __func(__x_a);
      auto __f_b = __func(__x_b);

      const _Tp _S_eps = std::numeric_limits<_Tp>::epsilon();

      if (__f_a * __f_b > _Tp{0})
	std::__throw_domain_error(__N("__root_brent: Root must be bracketed"));

      auto __f_c = __f_b;
      for (std::size_t __iter = 0; __iter < __max_iter; ++__iter)
	{
	  _Tp __d, __e;
	  if (__f_b * __f_c > _Tp{0})
	    {
	      __x_c = __x_a;
	      __f_c = __f_a;
	      __e = __d = __x_b - __x_a;
	    }
	  if (std::abs(__f_c) < std::abs(__f_b))
	    {
	      __x_a = __x_b;
	      __x_b = __x_c;
	      __x_c = __x_a;
	      __f_a = __f_b;
	      __f_b = __f_c;
	      __f_c = __f_a;
	    }
	  auto __toler = _Tp{2} * _S_eps * std::abs(__x_b) + __eps / _Tp{2};
	  auto __xm = (__x_c - __x_b) / _Tp{2};
	  if (std::abs(__xm) <= __toler || __f_b == _Tp{0})
	    return __x_b;
	  if (std::abs(__e) >= __toler && std::abs(__f_a) > std::abs(__f_b))
	    {
	      _Tp __p, __q, __r;
	      auto __s = __f_b / __f_a;
	      if (__x_a == __x_c)
		{
		  __p = _Tp{2} * __xm * __s;
		  __q = _Tp{1} - __s;
		}
	      else
		{
		  __q = __f_a / __f_c;
		  __r = __f_b / __f_c;
		  __p = __s * (_Tp{2} * __xm * __q * (__q - __r)
		      - (__x_b - __x_a) * (__r - _Tp{1}));
		  __q = (__q - _Tp{1}) * (__r - _Tp{1}) * (__s - _Tp{1});
		}
	      if (__p > _Tp{0})
		__q = -__q;
	      __p = std::abs(__p);
	      auto __min1 = _Tp{3} * __xm * __q - std::abs(__toler * __q);
	      auto __min2 = std::abs(__e * __q);
	      if (_Tp{2} * __p < std::min(__min1, __min2))
		{
		  __e = __d;
		  __d = __p / __q;
		}
	      else
		{
		  __d = __xm;
		  __e = __d;
		}
	    }
	  else
	    {
	      __d = __xm;
	      __e = __d;
	    }
	  __x_a = __x_b;
	  __f_a = __f_b;
	  if (std::abs(__d) > __toler)
	    __x_b += __d;
	  else
	    __x_b += std::copysign(__toler, __xm);
	  __f_b = __func(__x_b);
	}

      std::__throw_runtime_error(__N("__root_brent: "
				     "Maximum number of iterations exceeded"));
    }


  /**
   * Using the Newton-Raphson method, find the root of a function @c __func
   * known to lie in the interval @c __x_lower to @c __x_upper.
   * The returned root is refined until its accuracy is
   * within <tt>+/- __eps</tt>.
   *
   * @f[
   *    x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)}
   * @f]
   *
   * @param __func A routine that provides both the function value
   *               and the first derivative of the function at the point x.
   *               The return type must be decomposable into [value, deriv].
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __eps  The tolerance
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _StateFunc>
    _Tp
    __root_newton(_StateFunc __func, _Tp __x_lower, _Tp __x_upper,
		  _Tp __eps, std::size_t __max_iter)
    {
      auto __x = (__x_lower + __x_upper) / _Tp{2};
      for (std::size_t __i = 0; __i < __max_iter; ++__i)
	{
	  const auto [__value, __deriv] = __func(__x);
	  const auto __dx = __value / __deriv;
	  __x -= __dx;
	  if ((__x_lower - __x) * (__x - __x_upper) < _Tp{0})
	    std::__throw_runtime_error(__N("__root_newton: "
					   "Jumped out of brackets"));
	  if (std::abs(__dx) < __eps)
	    return __x;
	}
      std::__throw_runtime_error(__N("__root_newton: "
				     "Maximum number of iterations exceeded"));
    }


  /**
   * Using the Halley method, find the root of a function @c __func
   * known to lie in the interval @c __x_lower to @c __x_upper.
   * The returned root is refined until its accuracy is
   * within <tt>+/- __eps</tt>.
   *
   * @f[
   *    x_{n+1} - x_n = -\frac{2 f(x_n) f'(x_n)}
   *                    {2 [f'(x_n)]^2 - f(x_n) f''(x_n)}
   * @f]
   * This form indicates the close relationship to the Newton method:
   * @f[
   *    x_{n+1} - x_n = -\frac{f'(x_n)}
   *                    {f'(x_n) - [f(x_n) f''(x_n)]/[2f'(x_n)]}
   * @f]
   *
   * @param __func A routine that provides both the function value, and the
   *               first and second derivative of the function at the point x.
   *               The return type must be decomposable into [val, der, der2].
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __eps  The tolerance
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _StateFunc>
    _Tp
    __root_halley(_StateFunc __func, _Tp __x_lower, _Tp __x_upper,
		  _Tp __eps, std::size_t __max_iter)
    {
      auto __x = (__x_lower + __x_upper) / _Tp{2};
      for (std::size_t __i = 0; __i < __max_iter; ++__i)
	{
	  const auto [__f, __df, __d2f] = __func(__x);
	  const auto __dx = _Tp{2} * __f * __df
			   / (_Tp{2} * __df * __df - __f * __d2f);
	  __x -= __dx;
	  if ((__x_lower - __x) * (__x - __x_upper) < _Tp{0})
	    std::__throw_runtime_error(__N("__root_halley: "
					   "Jumped out of brackets"));
	  if (std::abs(__dx) < __eps)
	    return __x;
	}
      std::__throw_runtime_error(__N("__root_halley: "
				     "Maximum number of iterations exceeded"));
    }


  /**
   * Using the Steffensen method, find the root of a function @c __func
   * known to lie in the interval @c __x_lower to @c __x_upper.
   * The returned root is refined until its accuracy is
   * within <tt>+/- __eps</tt>.
   *
   * @f[
   *    x_{n+1} = x_n - \frac{f(x_n)}{\frac{f(x_n + f(x_n))}{f(x_n)} - 1}
   * @f]
   *
   * The Steffensen method amounts to estimating the derivative using the
   * previous function value as a stepsize and applying the Newton iteration.
   *
   * This method is supposed to have quadratic convergence like Newton's
   * method but it only required te function values.  On the other hand,
   * the initial estimate generally must be tighter than for Newton's method.
   *
   * @param __func A routine that provides the function value at the point x.
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __eps  The tolerance
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _Func>
    _Tp
    __root_steffensen(_Func __func, _Tp __x_lower, _Tp __x_upper,
    		      _Tp __eps, std::size_t __max_iter)
    {
      auto __x = (__x_lower + __x_upper) / _Tp{2};
      for (std::size_t __i = 0; __i < __max_iter; ++__i)
	{
	  auto __fval = __func(__x);
	  auto __gval = __func(__x + __fval) / __fval - _Tp{1};
	  auto __dx = __fval / __gval;
	  __x -= __dx;
	  if ((__x_lower - __x) * (__x - __x_upper) < _Tp{0})
	    std::__throw_runtime_error(__N("__root_steffensen: "
					   "Jumped out of brackets"));
	  if (std::abs(__dx) < __eps)
	    return __x;
	}
      std::__throw_runtime_error(__N("__root_steffensen: "
				     "Maximum number of iterations exceeded"));
    }


  /**
   * Using a combination of Newton-Raphson and bisection, find the root
   * of a function @c __func known to lie in the interval @c __x_lower
   * to @c __x_upper.
   * The returned root is refined until its accuracy is
   * within <tt>+/- __eps</tt>.
   *
   * @param __func  A routine that provides both the function
   *                and the first derivative of the function at the point x.
   * @param __x_lower  The lower end of the search interval.
   * @param __x_upper  The upper end of the search interval.
   * @param __eps  The tolerance
   * @param __max_iter  The maximum number of iterations
   */
  template<typename _Tp, typename _StateFunc>
    _Tp
    __root_safe(_StateFunc __func, _Tp __x_lower, _Tp __x_upper,
		_Tp __eps, std::size_t __max_iter)
    {
      auto [__value_lower, __deriv_lower] = __func(__x_lower);
      auto [__value_upper, __deriv_upper] = __func(__x_upper);

      if (__value_lower * __value_upper > _Tp{0})
	std::__throw_domain_error(__N("__root_safe: Root must be bracketed"));

      if (__value_lower == _Tp{0})
	return __x_lower;
      if (__value_upper == _Tp{0})
	return __x_upper;

      _Tp __x_hi, __x_lo;
      if (__value_lower < _Tp{0})
	{
	  __x_lo = __x_lower;
	  __x_hi = __x_upper;
	}
      else
	{
	  __x_hi = __x_lower;
	  __x_lo = __x_upper;
	}

      auto __x = (__x_lower + __x_upper) / _Tp{2};
      auto __dxold = std::abs(__x_upper - __x_lower);
      auto __dx = __dxold;
      auto [__value, __deriv] = __func(__x);
      for (std::size_t __i = 0; __i < __max_iter; ++__i)
	{
	  if (((__x - __x_hi) * __deriv - __value)
	    * ((__x - __x_lo) * __deriv - __value) > _Tp{0}
	   || std::abs(_Tp{2} * __value)
	    > std::abs(__dxold * __deriv))
	    {
	      __dxold = __dx;
	      __dx = (__x_hi - __x_lo) / _Tp{2};
	      __x = __x_lo + __dx;
	      if (__x == __x_lo)
		return __x;
	    }
	  else
	    {
	      __dxold = __dx;
	      __dx = __value / __deriv;
	      auto __temp = __x;
	      __x -= __dx;
	      if (__temp == __x)
		return __x;
	    }
	  if (std::abs(__dx) < __eps)
	    return __x;

	  auto [__val, __der] = __func(__x);
	  __value = __val;
	  __deriv = __der;

	  if (__value < _Tp{0})
	    __x_lo = __x;
	  else
	    __x_hi = __x;
	}

      std::__throw_runtime_error(__N("__root_safe: "
				     "Maximum number of iterations exceeded"));
    }

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace __gnu_cxx

#endif // _EXT_ROOT_SEARCH_TCC
