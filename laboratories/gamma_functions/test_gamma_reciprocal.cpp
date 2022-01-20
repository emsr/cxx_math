/**
 *
 */

/**
 * Look at the formula for the reciprocal of the gamma for the Temme gamma
 * \frac{1}{\Gamma(1 +- \mu)}
 */

#include <cmath>
#include <limits>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <complex>

#include <ext/float128_io.h>

//#include <mpreal.h>
//#include <ext/math_const_mpreal.h>
//#include <math_mpreal.h>
//#include <bits/numeric_limits_mpreal.h>

  /**
   * 
   */
  template<typename _Tp>
    std::vector<emsr::num_traits_t<_Tp>>
    __gamma_reciprocal_series_coef(std::size_t __n, _Tp __proto = _Tp{})
    {
      using _Val = _Tp;
      using _Real = emsr::num_traits_t<_Val>;
      const auto _S_eps = __gnu_cxx::__epsilon(std::real(__proto));
      const auto _S_gamma_e = emsr::egamma_v<_Tp>;
      auto __sign = [](std::size_t __i){ return (__i & 1u) == 1u ? -1 : +1; };
      std::vector<_Real> __c;
      __c.push_back(_Real{0});
      __c.push_back(_Real{1});
      for (auto __j = 1u; __j < __n; ++__j)
	{
	  auto __sum = _Real{0};
	  for (auto __k = 1u; __k < __j; ++__k)
	    __sum += __sign(__k) * __c[__k]
		   * (_Real{1} + std::__detail::__riemann_zeta_m_1(_Real(__j + 1 - __k)));
	  __c.push_back((_S_gamma_e * __c[__j] + __sign(__j) * __sum) / __j);
	  if (std::abs(__c.back()) < _S_eps)
	    break;
	}
      return __c;
    }

  /**
   * Return the reciprocal of the Gamma function by series.
   * The reciprocal of the Gamma function is given by
   * @f[
   *   \frac{1}{\Gamma(a)} = \sum_{k=1}^{\infty} c_k a^k
   * @f]
   * where the coefficients are defined by recursion:
   * @f[
   *   c_{k+1} = \frac{1}{k}\left[\gamma_E c_k
   *           + (-1)^k\sum_{j=1}^{k-1}(-1)^j\zeta(j+1-k)c_j\right]
   * @f]
   * where @f$ c_1 = 1 @f$
   */
  template<typename _Tp>
    _Tp
    __gamma_reciprocal_series(_Tp __a)
    {
      static constexpr std::array<__float128, 50>
      _S_c
      {{
	 0.0000000000000000000000000000000000000000Q,
	 1.0000000000000000000000000000000000000000Q,
	 0.5772156649015328606065120900824024310432Q,
	-0.6558780715202538810770195151453904812811Q,
	-0.0420026350340952355290039348754298187119Q,
	 0.1665386113822914895017007951021052357187Q,
	-0.0421977345555443367482083012891873913015Q,
	-0.0096219715278769735621149216723481989747Q,
	 0.0072189432466630995423950103404465727093Q,
	-0.0011651675918590651121139710840183886674Q,
	-0.0002152416741149509728157299630536478063Q,
	 0.0001280502823881161861531986263281643238Q,
	-0.0000201348547807882386556893914210218186Q,
	-0.0000012504934821426706573453594738330926Q,
	 0.0000011330272319816958823741296203307448Q,
	-0.0000002056338416977607103450154130020573Q,
	 0.0000000061160951044814158178624986828556Q,
	 0.0000000050020076444692229300556650480601Q,
	-0.0000000011812745704870201445881265654365Q,
	 0.0000000001043426711691100510491540332313Q,
	 0.0000000000077822634399050712540499373115Q,
	-0.0000000000036968056186422057081878158781Q,
	 0.0000000000005100370287454475979015481319Q,
	-0.0000000000000205832605356650678322242954Q,
	-0.0000000000000053481225394230179823700171Q,
	 0.0000000000000012267786282382607901588941Q,
	-0.0000000000000001181259301697458769513765Q,
	 0.0000000000000000011866922547516003325796Q,
	 0.0000000000000000014123806553180317815559Q,
	-0.0000000000000000002298745684435370206591Q,
	 0.0000000000000000000171440632192733743337Q,
	 0.0000000000000000000001337351730493693114Q,
	-0.0000000000000000000002054233551766672789Q,
	 0.0000000000000000000000273603004860799984Q,
	-0.0000000000000000000000017323564459105165Q,
	-0.0000000000000000000000000236061902449928Q,
	 0.0000000000000000000000000186498294171728Q,
	-0.0000000000000000000000000022180956242072Q,
	 0.0000000000000000000000000001297781974948Q,
	 0.0000000000000000000000000000011806974748Q,
	-0.0000000000000000000000000000011245843493Q,
	 0.0000000000000000000000000000001277085176Q,
	-0.0000000000000000000000000000000073914512Q,
	 0.0000000000000000000000000000000000113476Q,
	 0.0000000000000000000000000000000000463914Q,
	-0.0000000000000000000000000000000000053474Q,
	 0.0000000000000000000000000000000000003208Q,
	-0.0000000000000000000000000000000000000044Q,
	-0.0000000000000000000000000000000000000013Q,
	 0.0000000000000000000000000000000000000002Q,
      }};
      const auto _S_eps = __gnu_cxx::__epsilon(std::real(__a));
      auto __ak = _Tp{1};
      auto __gam = _Tp{0};
      for (auto __k = 1u; __k < _S_c.size(); ++__k)
	{
	  __ak *= __a;
	  auto __term = _S_c[__k] * __ak;
	  __gam += __term;
	  if (std::abs(__term) < _S_eps)
	    break;
	}
      return __gam;
    }

  /**
   * Return the reciprocal of the Gamma function by infinite product.
   * The reciprocal of the Gamma function is given by
   * @f[
   *   \frac{1}{\Gamma(a)} = ae^{\gamma_E a}\Pi_{k=1}^{\infty}
   *                     (\left 1+\frac{a}{k}\right)e^{-a/k}
   * @f]
   */
  template<typename _Tp>
    _Tp
    __gamma_reciprocal_prod(_Tp __a)
    {
      const auto _S_eps = __gnu_cxx::__epsilon(std::real(__a));
      const auto _S_gamma_e = emsr::egamma_v<_Tp>;
      const auto _S_max_iter = 10000;
      auto __gam = __a * std::exp(_S_gamma_e * __a);
      for (auto __k = 1u; __k < _S_max_iter; ++__k)
	{
	  const auto __rat = __a / _Tp(__k);
	  __gam *= (_Tp{1} + __rat) * std::exp(-__rat);
	  if (std::abs(__rat) < _S_eps)
	    break;
	}
      return __gam;
    }

  /**
   * Return the reciprocal of the Gamma function:
   * @f[
   *   \frac{1}{\Gamma(a)}
   * @f]
   *
   * @param __a The argument of the reciprocal of the gamma function.
   * @return  The reciprocal of the gamma function.
   */
  template<typename _Tp>
    _Tp
    __gamma_reciprocal(_Tp __a)
    {
      using _Real = emsr::num_traits_t<_Tp>;

      if (std::isnan(__a))
	return __gnu_cxx::__quiet_NaN(__a);
      else
	{
	  const auto _S_pi = emsr::pi_v<_Tp>;
	  const auto __an = emsr::fp_is_integer(__a);
	  if (__an)
	    {
	      auto __n = __an();
	      if (__n <= 0)
		return _Tp{0};
	      else if (__n < int(std::__detail::_S_num_factorials<_Real>))
		return _Tp{1}
		    / _Real(std::__detail::_S_factorial_table[__n - 1].__factorial);
	      else
	        {
		  auto __k = int(std::__detail::_S_num_factorials<_Real>);
		  auto __rgam = _Tp{1}
			      / _Real(std::__detail::_S_factorial_table[__k - 1].__factorial);
		  while (__k < __n && std::abs(__rgam) > _Real{0})
		    __rgam /= _Real(__k++);
		  return __rgam;
		}
	    }
	  else if (std::real(__a) > _Real{1})
	    {
	      auto __n = int(std::floor(std::real(__a)));
	      auto __nu = __a - _Tp(__n);
	      auto __rgam = __gamma_reciprocal_series(__nu);
	      while (std::real(__a) > _Real{1} && std::abs(__rgam) > _Tp{0})
	        __rgam /= (__a -= _Real{1});
	      return __rgam;
	    }
	  else if (std::real(__a) > _Real{0})
	    return __gamma_reciprocal_series(__a);
	  else
	    return std::__detail::__sin_pi(__a)
		 * std::__detail::__gamma(_Tp{1} - __a) / _S_pi;
	}
    }

  /**
   * @brief A structure for the gamma functions required by the Temme series
   * 	    expansions of @f$ N_\nu(x) @f$ and @f$ K_\nu(x) @f$.
   * @f[
   *   \Gamma_1 = \frac{1}{2\mu}
   * 	 \left[\frac{1}{\Gamma(1 - \mu)} - \frac{1}{\Gamma(1 + \mu)}\right]
   * @f]
   * and
   * @f[
   *   \Gamma_2 = \frac{1}{2}
   *     \left[\frac{1}{\Gamma(1 - \mu)} + \frac{1}{\Gamma(1 + \mu)}\right]
   * @f]
   * where @f$ -1/2 <= \mu <= 1/2 @f$ is @f$ \mu = \nu - N @f$ and @f$ N @f$.
   * is the nearest integer to @f$ \nu @f$.
   * The values of @f$ \Gamma(1 + \mu) @f$ and @f$ \Gamma(1 - \mu) @f$
   * are returned as well.
   *
   * The accuracy requirements on this are high for @f$ |\mu| < 0 @f$.
   */
  template<typename _Tp>
    struct __gamma_temme_t
    {
      /// The input parameter of the gamma functions
      _Tp __mu_arg;
      /// The output function @f$ 1/\Gamma(1 + \mu) @f$
      _Tp __gamma_plus_value;
      /// The output function @f$ 1/\Gamma(1 - \mu) @f$
      _Tp __gamma_minus_value;
      /// The output function @f$ \Gamma_1(\mu) @f$
      _Tp __gamma_1_value;
      /// The output function @f$ \Gamma_2(\mu) @f$
      _Tp __gamma_2_value;
    };

  /**
   * @brief Compute the gamma functions required by the Temme series
   * 	    expansions of @f$ N_\nu(x) @f$ and @f$ K_\nu(x) @f$.
   * @f[
   *   \Gamma_1 = \frac{1}{2\mu}
   * 	 \left[\frac{1}{\Gamma(1 - \mu)} - \frac{1}{\Gamma(1 + \mu)}\right]
   * @f]
   * and
   * @f[
   *   \Gamma_2 = \frac{1}{2}
   *     \left[\frac{1}{\Gamma(1 - \mu)} + \frac{1}{\Gamma(1 + \mu)}\right]
   * @f]
   * where @f$ -1/2 <= \mu <= 1/2 @f$ is @f$ \mu = \nu - N @f$ and @f$ N @f$.
   * is the nearest integer to @f$ \nu @f$.
   * The values of @f$ \Gamma(1 + \mu) @f$ and @f$ \Gamma(1 - \mu) @f$
   * are returned as well.
   *
   * The accuracy requirements on this are exquisite.
   *
   * @param __mu     The input parameter of the gamma functions.
   * @param[out] __gam1   The output function @f$ \Gamma_1(\mu) @f$
   * @param[out] __gam2   The output function @f$ \Gamma_2(\mu) @f$
   * @param[out] __gamp  The output function @f$ 1/\Gamma(1 + \mu) @f$
   * @param[out] __gamm  The output function @f$ 1/\Gamma(1 - \mu) @f$
   */
  template<typename _Tp>
    __gnu_cxx::__gamma_temme_t<_Tp>
    __gamma_temme(_Tp __mu)
    {
      using __gammat_t = __gnu_cxx::__gamma_temme_t<_Tp>;
      const auto _S_eps = __gnu_cxx::__epsilon(__mu);
      const auto _S_gamma_E = emsr::egamma_v<_Tp>;

      if (std::abs(__mu) < _S_eps)
	return __gammat_t{__mu, _Tp{1}, _Tp{1}, -_S_gamma_E, _Tp{1}};
      else
	{
	  _Tp __gamp, __gamm;
	  if (std::real(__mu) <= _Tp{0})
	    {
	      __gamp = __gamma_reciprocal_series(_Tp{1} + __mu);
	      __gamm = -__gamma_reciprocal_series(-__mu) / __mu;
	    }
	  else
	    {
	      __gamp = __gamma_reciprocal_series(__mu) / __mu;
	      __gamm = __gamma_reciprocal_series(_Tp{1} - __mu);
	    }
	  auto __gam1 = (__gamm - __gamp) / (_Tp{2} * __mu);
	  auto __gam2 = (__gamm + __gamp) / _Tp{2};
	  return __gammat_t{__mu, __gamp, __gamm, __gam1, __gam2};
	}
    }

  template<typename _Tp>
    __gamma_temme_t<_Tp>
    __gamma_temme_std(_Tp __mu)
    {
      const auto _S_eps = __gnu_cxx::__epsilon(__mu);
      const auto _S_gamma_E = emsr::egamma_v<_Tp>;
      auto __gamp = _Tp{1} / std::tgamma(_Tp{1} + __mu);
      auto __gamm = _Tp{1} / std::tgamma(_Tp{1} - __mu);
      auto __gam1 = (std::abs(__mu) < _S_eps)
		  ? -_S_gamma_E
		  : (__gamm - __gamp) / (_Tp{2} * __mu);
      auto __gam2 = (__gamm + __gamp) / _Tp{2};

      return __gamma_temme_t<_Tp>{__mu, __gamp, __gamm, __gam1, __gam2};
    }


template<typename _Tp>
  void
  plot_gamma_reciprocal(_Tp __proto)
  {
    std::cout.precision(__gnu_cxx::__digits10(__proto));
    std::cout << std::showpoint << std::scientific;
    auto width = 8 + std::cout.precision();
    const auto del = _Tp{1} / _Tp{100};
    for (auto __k = -500; __k <= 1000; ++__k)
      {
	auto __a = __k * del;
	auto __gammar = __gamma_reciprocal(__a);
	std::cout << ' ' << std::setw(width) << __a
		<< ' ' << std::setw(width) << __gammar
    		<< '\n';
      }
    std::cout << "\n\n";
  }


template<typename _Tp>
  void
  test_gamma_reciprocal(_Tp __proto)
  {
    using _Val = _Tp;
    using _Real = emsr::num_traits_t<_Val>;

    std::cout.precision(__gnu_cxx::__digits10(__proto));
    std::cout << std::showpoint << std::scientific;
    auto width = 8 + std::cout.precision();

    std::size_t __n = 50;
    auto __c = __gamma_reciprocal_series_coef<_Real>(__n, __proto);

    std::cout << '\n'
	      << ' ' << std::setw(4) << "k"
	      << ' ' << std::setw(width) << "c"
    	      << '\n';
    for (auto __k = 0u; __k < __c.size(); ++__k)
      std::cout << ' ' << std::setw(4) << __k
		<< ' ' << std::setw(width) << __c[__k]
    		<< '\n';

    std::cout << '\n'
	      << ' ' << std::setw(width) << "a"
	      << ' ' << std::setw(width) << "1/G(a) ser"
	      << ' ' << std::setw(width) << "1/G(a) prd"
	      << ' ' << std::setw(width) << "1/std::tgm"
	      << ' ' << std::setw(width) << "1/G(a)"
	      << ' ' << std::setw(width) << "del ser"
	      << ' ' << std::setw(width) << "del prd"
	      << ' ' << std::setw(width) << "del"
    	      << '\n';
    const auto del = _Tp{1} / _Tp{100};
    for (auto __k = -500; __k <= 1000; ++__k)
      {
	auto __a = __k * del;
	auto __gammargs = __gamma_reciprocal_series(__a);
	auto __gammargp = __gamma_reciprocal_prod(__a);
	auto __gammarstd = _Tp{1} / std::tgamma(__a);
	auto __gammar = __gamma_reciprocal(__a);
	std::cout << ' ' << std::setw(width) << __a
		<< ' ' << std::setw(width) << __gammargs
		<< ' ' << std::setw(width) << __gammargp
		<< ' ' << std::setw(width) << __gammarstd
		<< ' ' << std::setw(width) << __gammar
		<< ' ' << std::setw(width) << (__gammargs - __gammarstd) / __gammarstd
		<< ' ' << std::setw(width) << (__gammargp - __gammarstd) / __gammarstd
		<< ' ' << std::setw(width) << (__gammar - __gammarstd) / __gammarstd
    		<< '\n';
      }
  }

template<typename _Tp>
  void
  test_gamma_temme(_Tp __proto)
  {
    std::cout.precision(__gnu_cxx::__digits10(__proto));
    std::cout << std::showpoint << std::scientific;
    auto width = 8 + std::cout.precision();

    std::cout << '\n'
	      << ' ' << std::setw(width) << "a"
	      << ' ' << std::setw(width) << "1/Gamma(1+mu)"
	      << ' ' << std::setw(width) << "1/Gamma(1-mu)"
	      << ' ' << std::setw(width) << "Gamma_1"
	      << ' ' << std::setw(width) << "Gamma_2"
	      << ' ' << std::setw(width) << "1/std::tgamma(1+mu)"
	      << ' ' << std::setw(width) << "1/std::tgamma(1-mu)"
	      << ' ' << std::setw(width) << "tgamma_1"
	      << ' ' << std::setw(width) << "tgamma_2"
	      << ' ' << std::setw(width) << "delta (1+mu)"
	      << ' ' << std::setw(width) << "delta (1-mu)"
	      << ' ' << std::setw(width) << "delta 1"
	      << ' ' << std::setw(width) << "delta 2"
    	      << '\n';
    const auto del = _Tp{1} / _Tp{100};
    for (auto k = -100; k <= 100; ++k)
      {
	auto mu = k * del;
	auto tggnu = __gamma_temme(mu);
	auto tgstd = __gamma_temme_std(mu);
	std::cout << ' ' << std::setw(width) << mu
		<< ' ' << std::setw(width) << tggnu.__gamma_plus_value
		<< ' ' << std::setw(width) << tggnu.__gamma_minus_value
		<< ' ' << std::setw(width) << tggnu.__gamma_1_value
		<< ' ' << std::setw(width) << tggnu.__gamma_2_value
		<< ' ' << std::setw(width) << tgstd.__gamma_plus_value
		<< ' ' << std::setw(width) << tgstd.__gamma_minus_value
		<< ' ' << std::setw(width) << tgstd.__gamma_1_value
		<< ' ' << std::setw(width) << tgstd.__gamma_2_value
		<< ' ' << std::setw(width) << (tggnu.__gamma_plus_value - tgstd.__gamma_plus_value) / tgstd.__gamma_plus_value
		<< ' ' << std::setw(width) << (tggnu.__gamma_minus_value - tgstd.__gamma_minus_value) / tgstd.__gamma_minus_value
		<< ' ' << std::setw(width) << (tggnu.__gamma_1_value - tgstd.__gamma_1_value) / tgstd.__gamma_1_value
		<< ' ' << std::setw(width) << (tggnu.__gamma_2_value - tgstd.__gamma_2_value) / tgstd.__gamma_2_value
    		<< '\n';
      }
  }

int
main()
{
  plot_gamma_reciprocal(1.0);

  test_gamma_reciprocal(1.0f);

  test_gamma_reciprocal(1.0);

  test_gamma_reciprocal(1.0l);

  //test_gamma_reciprocal(1.0q);

  //test_gamma_reciprocal(mpfr::mpreal(1,128));

  test_gamma_temme(1.0f);

  test_gamma_temme(1.0);

  test_gamma_temme(1.0l);

  //test_gamma_temme(1.0q);
}
