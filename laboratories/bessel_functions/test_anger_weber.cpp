/**
 *
 */

#include <cmath>
#include <ext/math_util.h>

  /**
   * 
   */
  template<typename _Tp>
    struct __anger_weber_t
    {
      _Tp __nu;
      _Tp __z;
      _Tp __J_value;
      _Tp __E_value;
    };

  /**
   * A smart Gamma reciprocal function/iterator.
   */
  template<typename _Tp>
    struct _GammaReciprocal
    {
      explicit _GammaReciprocal(_Tp __a)
      : _M_arg(__a),
        _M_int(__gnu_cxx::__fp_is_integer(__a))
      { }

      _Tp
      operator()()
      {
	if (this->_M_int && this->_M_arg <= _Tp{0})
	  return _Tp{0};
	else
	  {
	    if (this->_M_start)
	      return (this->_M_gam /= (this->_M_arg += _Tp{1}));
	    else
	      {
	        this->_M_start = true;
	        this->_M_gam = std::__detail::__gamma_reciprocal(this->_M_arg);
		return this->_M_gam;
	      }
	  }
      }

      _GammaReciprocal&
      operator++()
      {
	this->_M_arg += _Tp{1};
	return *this;
      }

      _GammaReciprocal&
      operator++(int)
      {
	auto __temp = *this;
	this->_M_arg += _Tp{1};
	return __temp;
      }

      _Tp _M_arg;
      bool _M_int;
      bool _M_start = false;
    };

  /**
   * Compute a sum used for Anger and Weber functions:
   * @f[
   *    S_1(\nu,z) = \sum_{k=0}^{\infty}\frac{(-1)^k(\frac{z}{2})^{2k}}
   *   {\Gamma(k+\frac{\nu}{2}+1) \Gamma(k-\frac{\nu}{2}+1)}
   * @f]
   */
  template<typename _Tp>
    _Tp
    __anger_weber_sum_1(_Tp __nu, _Tp __z)
    {
      const auto _S_max_iter = 10000u;
      const auto _S_eps = __gnu_cxx::__epsilon(__z);
      const auto __z2 = __z / _Tp{2};
      auto _GamArg11 = _Tp{1} + __nu / _Tp{2};
      auto _GamArg12 = _Tp{1} - __nu / _Tp{2};
      auto _Gam11 = std::tgamma(_GamArg11);
      auto _Gam12 = std::tgamma(_GamArg12);
      auto __term1 = _Tp{1} / (_Gam11 * _Gam12);
      auto _S1 = __term1;
      for (auto __k = 1u; __k < _S_max_iter; ++__k)
	{
	  __term1 *= -__z2 / _GamArg11 * __z2 / _GamArg12;
	  _S1 += __term1;
	  _GamArg11 += _Tp{1};
	  _GamArg12 += _Tp{1};

	  if (std::abs(__term1) < _S_eps * std::abs(_S1))
	    return _S1;
	}
      return _Tp{0};
    }

  /**
   * Compute a sum used for Anger and Weber functions.
   * Assumes n == 2m, m > 0.
   * @f[
   *    S_1(\nu,z) = \sum_{k=0}^{\infty}\frac{(-1)^k(\frac{z}{2})^{2k}}
   *   {\Gamma(k+\frac{\nu}{2}+1) \Gamma(k-\frac{\nu}{2}+1)}
   * @f]
   */
  template<typename _Tp>
    _Tp
    __anger_weber_sum_1_even_int(int __n, _Tp __z)
    {
      const auto _S_max_iter = 10000u;
      const auto _S_eps = __gnu_cxx::__epsilon(__z);
      const auto __z2 = __z / _Tp{2};
      const auto __m = __n / 2;
      const auto __k_start = __m;
      auto _GamArg11 = _Tp(1 + __m + __k_start);
      auto _Gam11 = std::tgamma(_GamArg11);
      auto _GamArg12 = _Tp(1 - __m + __k_start);
      auto _Gam12 = std::tgamma(_GamArg12);
      auto __term1 = ((__k_start & 1) ? -1 : +1)
		   * std::pow(__z2, _Tp(2 * __k_start)) / (_Gam11 * _Gam12);
      auto _S1 = __term1;
      for (auto __k = 1u; __k < _S_max_iter; ++__k)
	{
	  __term1 *= -__z2 / _GamArg11 * __z2 / _GamArg12;
	  _S1 += __term1;
	  _GamArg11 += _Tp{1};
	  _GamArg12 += _Tp{1};

	  if (std::abs(__term1) < _S_eps * std::abs(_S1))
	    return _S1;
	}
      return _Tp{0};
    }

  /**
   * Compute a sum used for Anger and Weber functions:
   * @f[
   *    S_2(\nu,z) = \sum_{k=0}^{\infty}\frac{(-1)^k(\frac{z}{2})^{2k+1}}
   *   {\Gamma(k+\frac{\nu}{2}+\frac{3}{2}) \Gamma(k-\frac{\nu}{2}+\frac{3}{2})}
   * @f]
   */
  template<typename _Tp>
    _Tp
    __anger_weber_sum_2(_Tp __nu, _Tp __z)
    {
      const auto _S_max_iter = 10000u;
      const auto _S_eps = __gnu_cxx::__epsilon(__z);
      const auto __z2 = __z / _Tp{2};
      auto _GamArg21 = _Tp{3} / _Tp{2} + __nu / _Tp{2};
      auto _GamArg22 = _Tp{3} / _Tp{2} - __nu / _Tp{2};
      auto _Gam21 = std::tgamma(_GamArg21);
      auto _Gam22 = std::tgamma(_GamArg22);
      auto __term2 = __z2 / (_Gam21 * _Gam22);
      auto _S2 = __term2;
      for (auto __k = 1u; __k < _S_max_iter; ++__k)
	{
	  __term2 *= -__z2 / _GamArg21 * __z2 / _GamArg22;
	  _S2 += __term2;
	  _GamArg21 += _Tp{1};
	  _GamArg22 += _Tp{1};

	  if (std::abs(__term2) < _S_eps * std::abs(_S2))
	    return _S2;
	}
      return _Tp{0};
    }

  /**
   * Compute a sum used for Anger and Weber functions.
   * Assumes n == 2m+1, m > 0.
   * @f[
   *    S_2(\nu,z) = \sum_{k=0}^{\infty}\frac{(-1)^k(\frac{z}{2})^{2k+1}}
   *   {\Gamma(k+\frac{\nu}{2}+\frac{3}{2}) \Gamma(k-\frac{\nu}{2}+\frac{3}{2})}
   * @f]
   */
  template<typename _Tp>
    _Tp
    __anger_weber_sum_2_odd_int(int __n, _Tp __z)
    {
      const auto _S_max_iter = 10000u;
      const auto _S_eps = __gnu_cxx::__epsilon(__z);
      const auto __z2 = __z / _Tp{2};
      const auto __m = (__n - 1) / 2;
      const auto __k_start = __m;
      auto _GamArg21 = _Tp{2} + __m + __k_start;
      auto _Gam21 = std::tgamma(_GamArg21);
      auto _GamArg22 = _Tp{1} - __m + __k_start;
      auto _Gam22 = std::tgamma(_GamArg22);
      auto __term2 = ((__k_start & 1) ? -1 : +1)
		   * std::pow(__z2, _Tp(2 * __k_start + 1)) / (_Gam21 * _Gam22);
      auto _S2 = __term2;
      for (auto __k = 1u; __k < _S_max_iter; ++__k)
	{
	  __term2 *= -__z2 / _GamArg21 * __z2 / _GamArg22;
	  _S2 += __term2;
	  _GamArg21 += _Tp{1};
	  _GamArg22 += _Tp{1};

	  if (std::abs(__term2) < _S_eps * std::abs(_S2))
	    return _S2;
	}
      return _Tp{0};
    }

  /**
   * 
   */
  template<typename _Tp>
    __anger_weber_t<_Tp>
    __anger_weber_sum_new(_Tp __nu, _Tp __z)
    {
      if (__nu < _Tp{0})
	{
	  auto __AW = __anger_weber_sum_new(-__nu, -__z);
	  __AW.__E_value = -__AW.__E_value;
	  return __AW;
	}
      else
	{
	  auto __nuint = __gnu_cxx::__fp_is_integer(__nu);

	  auto _S1 = _Tp{0};
	  if (__nuint && __nuint() > 0 && __nuint() % 2 == 0)
	    _S1 = __anger_weber_sum_1_even_int(__nuint(), __z);
	  else
	    _S1 = __anger_weber_sum_1(__nu, __z);

	  auto _S2 = _Tp{0};
	  if (__nuint && __nuint() > 0 && __nuint() % 2 == 1)
	    _S2 = __anger_weber_sum_2_odd_int(__nuint(), __z);
	  else
	    _S2 = __anger_weber_sum_2(__nu, __z);

	  auto __ph = std::__detail::__sincos_pi(__nu / _Tp{2});
	  return __anger_weber_t<_Tp>{__nu, __z,
				      __ph.__cos_v * _S1
				    + __ph.__sin_v * _S2,
				      __ph.__sin_v * _S1
				    - __ph.__cos_v * _S2};
	}
    }

  /**
   * 
   */
  template<typename _Tp>
    __anger_weber_t<_Tp>
    __anger_weber_sum(_Tp __nu, _Tp __z)
    {
      const auto _S_eps = __gnu_cxx::__epsilon(__z);

      auto __nuint = __gnu_cxx::__fp_is_integer(__nu);

      if (__nu < _Tp{0})
	{
	  auto __AW = __anger_weber_sum(-__nu, -__z);
	  __AW.__E_value = -__AW.__E_value;
	  return __AW;
	}
      else if (__nuint && __nuint() > 1)
	{
	  auto __n = __nuint();
	  if (__n & 1)
	    {
	      const auto __z2 = __z / _Tp{2};
	      auto _GamArg11 = _Tp{1} + __nu / _Tp{2};
	      auto _GamArg12 = _Tp{1} - __nu / _Tp{2};
	      auto _Gam11 = std::tgamma(_GamArg11);
	      auto _Gam12 = std::tgamma(_GamArg12);
	      auto __term1 = _Tp{1} / (_Gam11 * _Gam12);
	      auto _S1 = __term1;
	      for (auto __k = 1u; __k < 10000u; ++__k)
		{
		  __term1 *= -__z2 / _GamArg11 * __z2 / _GamArg12;
		  _S1 += __term1;
		  _GamArg11 += _Tp{1};
		  _GamArg12 += _Tp{1};

		  if (std::abs(__term1) < _S_eps * std::abs(_S1))
		    break;
		}
	      return __anger_weber_t<_Tp>{__nu, __z,
					  _Tp{0},
					  -(((__n / 2) & 1) ? -1 : +1) * _S1};
	    }
	  else
	    {
	      const auto __z2 = __z / _Tp{2};
	      auto _GamArg21 = _Tp{3} / _Tp{2} + __nu / _Tp{2};
	      auto _GamArg22 = _Tp{3} / _Tp{2} - __nu / _Tp{2};
	      auto _Gam21 = std::tgamma(_GamArg21);
	      auto _Gam22 = std::tgamma(_GamArg22);
	      auto __term2 = __z2 / (_Gam21 * _Gam22);
	      auto _S2 = __term2;
	      for (auto __k = 1u; __k < 10000u; ++__k)
		{
		  __term2 *= -__z2 / _GamArg21 * __z2 / _GamArg22;
		  _S2 += __term2;
		  _GamArg21 += _Tp{1};
		  _GamArg22 += _Tp{1};

		  if (std::abs(__term2) < _S_eps * std::abs(_S2))
		    break;
		}
	      return __anger_weber_t<_Tp>{__nu, __z,
					  _Tp{0},
					 -((__n / 2) & 1 ? -1 : +1) * _S2};
	    }
	}
      else
	{
	  const auto __z2 = __z / _Tp{2};
	  auto _GamArg11 = _Tp{1} + __nu / _Tp{2};
	  auto _GamArg12 = _Tp{1} - __nu / _Tp{2};
	  auto _GamArg21 = _Tp{3} / _Tp{2} + __nu / _Tp{2};
	  auto _GamArg22 = _Tp{3} / _Tp{2} - __nu / _Tp{2};
	  auto _Gam11 = std::tgamma(_GamArg11);
	  auto _Gam12 = std::tgamma(_GamArg12);
	  auto _Gam21 = std::tgamma(_GamArg21);
	  auto _Gam22 = std::tgamma(_GamArg22);
	  auto __term1 = _Tp{1} / (_Gam11 * _Gam12);
	  auto _S1 = __term1;
	  auto __term2 = __z2 / (_Gam21 * _Gam22);
	  auto _S2 = __term2;
	  for (auto __k = 1u; __k < 10000u; ++__k)
	    {
	      __term1 *= -__z2 / _GamArg11 * __z2 / _GamArg12;
	      _S1 += __term1;
	      _GamArg11 += _Tp{1};
	      _GamArg12 += _Tp{1};

	      __term2 *= -__z2 / _GamArg21 * __z2 / _GamArg22;
	      _S2 += __term2;
	      _GamArg21 += _Tp{1};
	      _GamArg22 += _Tp{1};

	      if (std::abs(__term1) < _S_eps * std::abs(_S1)
	       && std::abs(__term2) < _S_eps * std::abs(_S2))
		break;
	    }
	  //auto [__sin, __cos] = __sincos_pi(__nu / _Tp{2});
	  auto __ph = std::__detail::__sincos_pi(__nu / _Tp{2});
	  return __anger_weber_t<_Tp>{__nu, __z,
				      __ph.__cos_v * _S1
				    + __ph.__sin_v * _S2,
				      __ph.__sin_v * _S1
				    - __ph.__cos_v * _S2};
	}
    }

  /**
   * Compute Anger and Weber functions for fixed order @f$ \nu @f$
   * and large agument @f$ |z| @f$.
   *
   * @see http://dlmf.nist.gov/11.10#i
   */
  template<typename _Tp>
    __anger_weber_t<_Tp>
    __anger_weber_asymp_arg(_Tp __nu, _Tp __z)
    {
      using _Real = decltype(std::real(__z));
      const auto _S_eps = __gnu_cxx::__epsilon<_Real>();
      const auto _S_pi = __gnu_cxx::numbers::__pi_v<_Real>;
      const auto _S_max_iter = 1000u;
      const auto __z2 = __z * __z;

      auto __F_z2k = _Tp{1};
      auto __G_z2k = _Tp{1};

      auto __Fsum = __F_z2k;
      auto __Gsum = __G_z2k;
      for (auto __k = 1u; __k < _S_max_iter; ++__k)
	{
	  __F_z2k *= (__nu - _Tp(2 * __k - 1)) * (__nu + _Tp(2 * __k - 1))
		   / __z2;
	  __Fsum += __F_z2k;
	  __G_z2k *= (__nu - _Tp(2 * __k)) * (__nu + _Tp(2 * __k))
		   / __z2;
	  __Gsum += __G_z2k;
	}

      auto __ph = std::__detail::__sincos_pi(__nu / _Tp{2});
      auto _Bess = __cyl_bessel(__nu, __z);
      return __anger_weber_t<_Tp>{__nu, __z,
				  _Bess._J_value
				    + __ph.__sin_v
				* (__Fsum + __nu * __Gsum / __z) / _S_pi / __z,
				 -_Bess._N_value
				    - (_Tp{1} + __ph.__cos_v) * __Fsum
					/ _S_pi / __z
				    - (_Tp{1} - __ph.__cos_v) * __Gsum
					* __nu / _S_pi / __z / __z};
    }

  /**
   * Compute Anger and Weber functions for large order @f$ |\nu| @f$
   * and fixed agument @f$ z @f$.
   *
   * @see http://dlmf.nist.gov/11.10#ii
   */
  template<typename _Tp>
    __anger_weber_t<_Tp>
    __anger_weber_asymp_order(_Tp __nu, _Tp __z)
    {
      using _Real = decltype(std::real(__z));
      const auto _S_pi = __gnu_cxx::numbers::__pi_v<_Real>;
      const auto __sinnp = __gnu_cxx::sin_pi(__nu);
      const auto __sinnpd2 = __gnu_cxx::sin_pi(__nu / _Tp{2});
      const auto __cosnpd2 = __gnu_cxx::cos_pi(__nu / _Tp{2});
      const auto __nufact = __nu * __z / (__nu * __nu - _Tp{1});
      return __anger_weber_t<_Tp>{__nu, __z,
				  __sinnp * (_Tp{1} - __nufact) / __nu / _S_pi,
				  _Tp{2} * (__sinnpd2 + __nufact * __cosnpd2)
					 / __nu / _S_pi};
    }

  /**
   * Compute Anger and Weber functions for large order @f$ \nu @f$
   * and fixed ratio @f$ z/\nu @f$.
   *
   * @see http://dlmf.nist.gov/11.10#iii
   */
  template<typename _Tp>
    __anger_weber_t<_Tp>
    __anger_weber_asymp_uniform(_Tp __nu, _Tp __z)
    {
    }

  /**
   * Use the reciprocal gamma function... Fails.  WTF.
   */
  template<typename _Tp>
    __anger_weber_t<_Tp>
    __anger_weber_sum_recip(_Tp __nu, _Tp __z)
    {
      //using _Val = _Tp;
      //using _Real = __gnu_cxx::__num_traits_t<_Val>;
      const auto _S_eps = __gnu_cxx::__epsilon(__z);

      const auto __z2 = __z / _Tp{2};
      auto _GamArg11 = _Tp{1} + __nu / _Tp{2};
      auto _GamArg12 = _Tp{1} - __nu / _Tp{2};
      auto _GamArg21 = _Tp{3} / _Tp{2} + __nu / _Tp{2};
      auto _GamArg22 = _Tp{3} / _Tp{2} - __nu / _Tp{2};
      auto _Gam11 = std::__detail::__gamma_reciprocal(_GamArg11);
      auto _Gam12 = std::__detail::__gamma_reciprocal(_GamArg12);
      auto _Gam21 = std::__detail::__gamma_reciprocal(_GamArg21);
      auto _Gam22 = std::__detail::__gamma_reciprocal(_GamArg22);
      auto __term1 = _Gam11 * _Gam12;
      auto _S1 = __term1;
      auto __term2 = __z2 * _Gam21 * _Gam22;
      auto _S2 = __term2;
      for (auto __k = 1u; __k < 10000u; ++__k)
	{
	  __term1 *= -__z2 / _GamArg11 * __z2 / _GamArg12;
	  _S1 += __term1;
	  _GamArg11 += _Tp{1};
	  _GamArg12 += _Tp{1};

	  __term2 *= -__z2 / _GamArg21 * __z2 / _GamArg22;
	  _S2 += __term2;
	  _GamArg21 += _Tp{1};
	  _GamArg22 += _Tp{1};

	  if (std::abs(__term1) < _S_eps * std::abs(_S1)
	   && std::abs(__term2) < _S_eps * std::abs(_S2))
	    break;
	}
      //auto [__sin, __cos] = __sincos_pi(__nu / _Tp{2});
      auto __ph = std::__detail::__sincos_pi(__nu / _Tp{2});
      return __anger_weber_t<_Tp>{__nu, __z,
				  __ph.__cos_v * _S1
				+ __ph.__sin_v * _S2,
				  __ph.__sin_v * _S1
				- __ph.__cos_v * _S2};
    }

  /**
   * Compute the Anger @f$ {\boldmath J}_\nu(z) @f$
   * and Weber @f$ {\boldmath E}_\nu(z) @f$ functions
   * for order @f$ \nu @f$ and agument @f$ z @f$.
   *
   * @see http://dlmf.nist.gov/11.10#ii
   */
  template<typename _Tp>
    _Tp
    __assoc_anger_weber_asymp(_Tp __nu, _Tp __z)
    {
      auto _Bessel = __cyl_bessel(__nu, __z);
      auto _Weber = __anger_weber(__nu, __z);
    }

  /**
   * Compute the associated Anger and Weber function @f$ A_\nu(z) @f$
   * for order @f$ \nu @f$ and agument @f$ z @f$.
   * We use the relationship:
   * @f[
   *   \boldmath{J}_\nu(z) = J_\nu(z) + \sin(\nu \pi) \boldmath{A}_\nu(z)
   * @f]
   * Note that for integer order n @f$ \boldmath{A}_n(z) = 0 @f$
   * since @f$ \boldmath{J}_n(z) = J_n(z) @f$.
   *
   * @see http://dlmf.nist.gov/11.10#v
   */
  template<typename _Tp>
    _Tp
    __assoc_anger_weber(_Tp __nu, _Tp __z)
    {
      auto _Bessel = std::cyl_bessel_j(__nu, __z);
      auto _Weber = __anger_weber_sum_new(__nu, __z);
      if (__gnu_cxx::__fp_is_integer(__nu))
	return _Tp{0};
      else
        return (_Weber.__J_value - _Bessel) / __gnu_cxx::sin_pi(__nu);
    }

  /**
   * @todo: Find out if
   * @f[
   *   \boldmath{J}_\nu(z) + i\boldmath{E}_\nu(z)
   * @f]
   * is a thing.
   */

  /**
   * \frac{1 - \cos(\pi x)}{\pi x}
   */
  template<typename _Tp>
  _Tp
  __cosc_pi(_Tp __x)
  {
    const auto _S_eps = __gnu_cxx::__epsilon(__x);
    const auto _S_pi = __gnu_cxx::numbers::__pi_v<_Tp>;
    if (std::abs(__x) < _Tp{100} * _S_eps)
      return _S_pi * __x / _Tp{2};
    else
      return (_Tp{1} - __gnu_cxx::cos_pi(__x)) / _S_pi / __x;
  }


template<typename _Tp>
  void
  test_anger_weber(_Tp proto = _Tp{})
  {
    std::cout.precision(__gnu_cxx::__digits10(proto));
    auto width = std::cout.precision() + 8;
    std::cout << std::showpoint << std::scientific;

    //std::cout << "\n\n Write J and E values\n";
    //std::cout << " --------------------\n";
    const auto twk = _Tp{1}/_Tp{1000};
    for (auto nu : {_Tp{0}, _Tp{1}/_Tp{2}, _Tp{1}, _Tp{3}/_Tp{2},
		    _Tp{2} - twk, _Tp{2},
		    _Tp{3} - twk, _Tp{3},
		    _Tp{5}})
      {
	std::cout << "\n\n nu = " << std::setw(4) << nu << '\n';
	std::cout << ' ' << std::setw(4) << "z"
		  << ' ' << std::setw(width) << "Jbold"
		  << ' ' << std::setw(width) << "Ebold"
		  << '\n';
	std::cout << ' ' << std::setw(4) << "-"
		  << ' ' << std::setw(width) << "-----"
		  << ' ' << std::setw(width) << "-----"
		  << '\n';
	const auto del = _Tp{1} / _Tp{10};
	for (int k = -80; k <= 80; ++k)
	  {
	    auto z = del * k;
	    //auto AW = __anger_weber_sum(nu, z);
	    auto AW = __anger_weber_sum_new(nu, z);
	    std::cout << ' ' << std::setw(4) << AW.__z
		      << ' ' << std::setw(width) << AW.__J_value
		      << ' ' << std::setw(width) << AW.__E_value
		      << '\n';
	  }
      }

    std::cout << "\n\n Test J and E values at zero\n";
    std::cout << " ---------------------------\n";
    for (auto nu : {_Tp{0}, _Tp{1}/_Tp{2}, _Tp{1}, _Tp{3}/_Tp{2},
		    _Tp{2} - twk, _Tp{2},
		    _Tp{3} - twk, _Tp{3},
		    _Tp{5}})
      {
	auto AW = __anger_weber_sum_new(nu, _Tp{0});
	std::cout << "\n\n nu = " << std::setw(4) << AW.__nu << '\n';
	std::cout << ' ' << std::setw(width) << AW.__J_value
		  << ' ' << std::setw(width) << __gnu_cxx::sinc_pi(nu)
		  << ' ' << std::setw(width) << AW.__E_value
		  << ' ' << std::setw(width) << __cosc_pi(nu)
		  << '\n';
      }

    std::cout << "\n\n Test J values for integer order\n";
    std::cout << " -------------------------------\n";
    for (auto nu : {_Tp{0}, _Tp{1}, _Tp{2}, _Tp{3}, _Tp{5}})
      {
	std::cout << "\n\n nu = " << std::setw(4) << nu << '\n';
	const auto del = _Tp{1} / _Tp{10};
	for (int k = 0; k <= 80; ++k)
	  {
	    auto z = del * k;
	    auto AW = __anger_weber_sum_new(nu, z);
	    std::cout << ' ' << std::setw(4) << AW.__z
		      << ' ' << std::setw(width) << AW.__J_value
		      << ' ' << std::setw(width) << std::cyl_bessel_j(nu, z)
		      << '\n';
	  }
      }

    std::cout << "\n\n Write A values\n";
    std::cout << " -------------------------------\n";
    for (auto nu : {_Tp{0}, _Tp{1}/_Tp{2}, _Tp{1}, _Tp{3}/_Tp{2},
		    _Tp{2} - twk, _Tp{2},
		    _Tp{3} - twk, _Tp{3},
		    _Tp{5}})
      {
	std::cout << "\n\n nu = " << std::setw(4) << nu << '\n';
	std::cout << ' ' << std::setw(4) << "z"
		  << ' ' << std::setw(width) << "Abold"
		  << '\n';
	std::cout << ' ' << std::setw(4) << "-"
		  << ' ' << std::setw(width) << "-----"
		  << '\n';
	const auto del = _Tp{1} / _Tp{10};
	for (int k = 0; k <= 80; ++k)
	  {
	    auto z = del * k;
	    auto AW = __assoc_anger_weber(nu, z);
	    std::cout << ' ' << std::setw(4) << z
		      << ' ' << std::setw(width) << AW
		      << '\n';
	  }
      }

    std::cout << "\n\n Test A values for integer order\n";
    std::cout << " -------------------------------\n";
    for (auto nu : {_Tp{0}, _Tp{1}, _Tp{2}, _Tp{3}, _Tp{5}})
      {
	std::cout << "\n\n nu = " << std::setw(4) << nu << '\n';
	const auto del = _Tp{1} / _Tp{10};
	for (int k = 0; k <= 80; ++k)
	  {
	    auto z = del * k;
	    auto AWm = __assoc_anger_weber(nu - twk, z);
	    auto AW = __assoc_anger_weber(nu, z);
	    auto AWp = __assoc_anger_weber(nu + twk, z);
	    std::cout << ' ' << std::setw(4) << z
		      << ' ' << std::setw(width) << AWm
		      << ' ' << std::setw(width) << AW
		      << ' ' << std::setw(width) << AWp
		      << '\n';
	  }
      }
  }

int
main()
{
  auto AW2 [[maybe_unused]] = __anger_weber_sum_new(2.0, -8.0);
  auto BX2 [[maybe_unused]] = __anger_weber_sum_new(1.999, -8.0);
  auto AW3 [[maybe_unused]] = __anger_weber_sum_new(3.0, -8.0);
  auto BX3 [[maybe_unused]] = __anger_weber_sum_new(2.999, -8.0);
  test_anger_weber(1.0);
}
