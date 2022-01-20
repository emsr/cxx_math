/**
 *
 */

#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#include <cmath>
#include <limits>
#include <iostream>
#include <iomanip>
#include <ext/summation.h>
#include <emsr/fp_type_util.h>
#include <statistics.h>

#include <3rdparty/lerchphi/Source/lerchphi.h>

  /**
   * A functor for a vanWijnGaarden compressor.
   * vanWijnGaarden requires:
   *   _Tp operator()(int) that returns a term in the original defining series.
   */
  template<typename _Tp>
    class __lerch_term
    {
    public:

      using value_type = _Tp;

      __lerch_term(value_type __z, value_type __s, value_type __a)
      : _M_z{__z}, _M_s{__s}, _M_a{__a}
      { }

      value_type
      operator()(std::size_t __i) const
      {
	return std::pow(_M_z, value_type(__i))
	     / std::pow(_M_a + value_type(__i), _M_s);
      }

    private:

      value_type _M_z;
      value_type _M_s;
      value_type _M_a;
    };

  /**
   * This function blows up on nonpositive integeral a.
   */
  template<typename _Tp>
    _Tp
    __lerch_sum(_Tp __z, _Tp __s, _Tp __a)
    {
      const auto _S_nan = __gnu_cxx::__quiet_NaN(__s);
      const auto _S_eps = __gnu_cxx::__epsilon(__s);

      const auto __aint = emsr::fp_is_integer(__a);
      if (__aint && __aint() <= 0)
	return _S_nan;
      else if (std::abs(std::abs(__z) - _Tp{1}) < _S_eps
		&& std::real(__s) <= _Tp{1} + _S_eps)
	return _S_nan;
      else if (std::abs(__z) > _Tp{1} + _S_eps)
	return _S_nan;
      else
	{
	  constexpr auto _S_maxit = 100000u;
	  auto __zpow = _Tp{1};
	  auto __sum = std::pow(__a, -__s);
	  for (auto __k = 1u; __k < _S_maxit; ++__k)
	    {
	      __zpow *= __z;
	      auto __term = __zpow * std::pow(__a + __k, -__s);
	      __sum += __term;
	      if (std::abs(__term / __sum) < _S_eps)
		break;
	    }
	  return __sum;
	}
    }

  /**
   * This function blows up on nonpositive integeral a.
   */
  template<typename _Tp>
    _Tp
    __lerch_vanwijngaarden_sum(_Tp __z, _Tp __s, _Tp __a)
    {
      const auto _S_nan = __gnu_cxx::__quiet_NaN(__s);
      const auto _S_eps = __gnu_cxx::__epsilon(__s);

      const auto __aint = emsr::fp_is_integer(__a);
      if (__aint && __aint() <= 0)
	return _S_nan;
      else if (std::abs(std::abs(__z) - _Tp{1}) < _S_eps
		&& std::real(__s) <= _Tp{1} + _S_eps)
	return _S_nan;
      else if (std::abs(__z) > _Tp{1} + _S_eps)
	return _S_nan;
      else if (__z < _Tp{0})
	{
	  constexpr auto _S_maxit = 100000u;
	  using __lerch_t = __lerch_term<_Tp>;
	  auto __lerch_fun = __lerch_t(__z, __s, __a);
	  __gnu_cxx::_VanWijngaardenSum<_Tp> __sum;
	  for (auto __k = 0u; __k < _S_maxit; ++__k)
	    {
	      auto __temp = __lerch_fun(__k);
	      __sum += __temp;
	      if (std::abs(__temp / __sum) < _S_eps)
		break;
	    }
	  return __sum();
	}
      else
	{
	  constexpr auto _S_maxit = 100000u;
	  using __lerch_t = __lerch_term<_Tp>;
	  auto __lerch_fun = __lerch_t(__z, __s, __a);
	  __gnu_cxx::_VanWijngaardenCompressor<__lerch_t> __term(__lerch_fun);
	  __gnu_cxx::_VanWijngaardenSum<_Tp> __sum;
	  for (auto __k = 0u; __k < _S_maxit; ++__k)
	    {
	      auto __temp = __term[__k];
	      __sum += __temp;
	      if (std::abs(__temp / __sum) < _S_eps)
		break;
	    }
	  return __sum();
	}
    }

  /**
   * This function blows up on nonpositive integeral a.
   *  As usual, the binomial coefficient kills this for practical purposes.
   */
  template<typename _Tp>
    _Tp
    __lerch_double_sum(_Tp __z, _Tp __s, _Tp __a)
    {
      const auto _S_nan = __gnu_cxx::__quiet_NaN(__s);
      const auto _S_eps = __gnu_cxx::__epsilon(__s);

      const auto __aint = emsr::fp_is_integer(__a);
      if (__aint && __aint() <= 0)
	return _S_nan;
      else if (std::abs(std::abs(__z) - _Tp{1}) < _S_eps
		&& std::real(__s) <= _Tp{1} + _S_eps)
	return _S_nan;
      else if (std::abs(__z) > _Tp{1} + _S_eps)
	return _S_nan;
      else
	{
	  constexpr auto _S_maxit = 10000u;
	  auto __lerch = std::pow(__a, -__s);
	  const auto __zfrac = -__z / (_Tp{1} - __z);
	  auto __zfact = _Tp{1};
	  for (auto __n = 1u; __n < _S_maxit; ++__n)
	    {
	      auto __term = std::pow(__a, -__s);
	      auto __binomial = _Tp{1};
	      __gnu_cxx::_VanWijngaardenSum<_Tp> __sum(__term);
	      for (auto __k = 1; __k <= __n; ++__k)
		{
		  __binomial *= -_Tp(__n - __k + 1) / _Tp(__k);
		  __term *= __z * __binomial * std::pow(__a + __k, -__s);
		  __sum += __term;
		}
	      __zfact *= __zfrac;
	      __lerch += __zfact * __sum();
	      if (std::abs(__zfact * __sum() / __lerch) < _S_eps)
		break;
	    }
	  __lerch /= (_Tp{1} - __z);
	  return __lerch;
	}
    }

  /**
   * Try the WenigerDelta<MonotoneVanWijngaarden> composition.
   */
  template<typename _Tp>
    _Tp
    __lerch_delta_vanwijngaarden_sum(_Tp __z, _Tp __s, _Tp __a)
    {
      const auto _S_eps = __gnu_cxx::__epsilon(__s);
      constexpr auto _S_maxit = 1000u;

      __gnu_cxx::_WenigerDeltaSum<__gnu_cxx::_VanWijngaardenSum<_Tp>> _WDvW;
      if (__z >= _Tp{0})
	{
	  using __lerch_t = __lerch_term<_Tp>;
	  using __lerch_cmp_t = __gnu_cxx::_VanWijngaardenCompressor<__lerch_t>;
	  auto _VwT = __lerch_cmp_t(__lerch_t(__z, __s, __a));
	  for (auto __k = 0u; __k < _S_maxit; ++__k)
	    {
	      auto __term = _VwT[__k];
	      _WDvW += __term;
	      if (std::abs(__term) < _S_eps * std::abs(_WDvW()))
		break;
	    }
	  return _WDvW();
	}
      else
	{
	  auto _LT = __lerch_term<_Tp>(__z, __s, __a);
	  for (auto __k = 0u; __k < _S_maxit; ++__k)
	    {
	      auto __term = _LT(__k);
	      _WDvW += __term;
	      if (std::abs(__term) < _S_eps * std::abs(_WDvW()))
		break;
	    }
	  return _WDvW();
	}
    }

  /**
   * This function blows up on nonpositive integeral a.
   */
  template<typename _Tp>
    _Tp
    __lerch_phi(_Tp __z, _Tp __s, _Tp __a)
    {
      const auto _S_nan = __gnu_cxx::__quiet_NaN(__s);
      const auto _S_eps = __gnu_cxx::__epsilon(__s);

      if (std::isnan(__z) || std::isnan(__s) || std::isnan(__a))
	return _S_nan;
      else if (std::abs(std::abs(__z) - _Tp{1}) < _S_eps
		&& std::real(__s) <= _Tp{1} + _S_eps)
	return _S_nan;
      else if (std::abs(__z) > _Tp{1} + _S_eps)
	return _S_nan;
      else
	{
	  const auto __aint = emsr::fp_is_integer(__a);

	  const auto __sint = emsr::fp_is_integer(__s);
	  const bool __tinyz = std::abs(__z) < _S_eps; // _S_min?
	  const bool __smallz = !__tinyz && (std::abs(__z) < _Tp{0.5});

	  if (__aint && __aint() <= 0)
	    return _S_nan;
	  else if (__a < _Tp{0})
	    {
	      if (__sint)
		{
		  int __sign = __sint() % 2 == 0 ? +1 : -1;
		  if (__tinyz)
		    return __sign * _Tp{1} / std::pow(std::abs(__a), __s);
		  else
		    {
		      auto __m = -int(std::floor(__a));
		      auto __a1 = __a + _Tp(__m);
		      auto __sum1 = _Tp{0};
		      for (int __i = 0; __i < __m; ++__i)
			{
			  __sum1 += __sign * std::pow(std::abs(__z), __i)
				  / std::pow(std::abs(__a + __i), _Tp(__sint()));
			  if (__z < _Tp{0})
			    __sign = -__sign;
			}
		      auto __sum = _Tp{0};
		      if (__smallz)
			__sum = __lerch_sum(__z, __s, __a1);
		      else
			__sum
			  = __lerch_delta_vanwijngaarden_sum(__z, __s, __a1);
		      __sign = 1;
		      if (__z < _Tp{0} && __m % 2 != 0)
			__sign = -1;
		      return __sum1
			   + __sum * __sign * std::pow(std::abs(__z), __m);
		    }
		}
	      else // s is not an integer - Phi is complex.
		return _S_nan;
	    }
	  else if (__tinyz)
	    return _Tp{1} / std::pow(__a, __s);
	  else // a > 0
	    {
	      if (__smallz)
		return __lerch_sum(__z, __s, __a);
	      else
		return __lerch_delta_vanwijngaarden_sum(__z, __s, __a);
	    }
	}
    }

  /**
   * Return the Hurwitz zeta function by evaluating the Lerch trancendent:
   * @f[
   *   \zeta(s,a) = \Phi(1,s,a)
   * @f]
   * @param[in] __s The argument s > 1
   * @param[in] __a The parameter
   */
  template<typename _Tp>
    _Tp
    __hurwitz_zeta_lerch(_Tp __s, _Tp __a)
    {
      return __lerch_phi(_Tp{1}, __s, __a);
    }

  /**
   * Return the Riemann zeta function by evaluating the Lerch trancendent:
   * @f[
   *   \zeta(s) = \Phi(1,s,1)
   * @f]
   * @param[in] __s The argument s > 1
   */
  template<typename _Tp>
    _Tp
    __riemann_zeta_lerch(_Tp __s)
    {
      return __lerch_phi(_Tp{1}, __s, _Tp{1});
    }

  /**
   * Return the Dirichlet beta function by evaluating the Lerch trancendent:
   * @f[
   *   \beta(s) = \frac{1}{2^s}\Phi(-1,s,\frac{1}{2})
   * @f]
   * @param[in] __s The argument s > 1
   */
  template<typename _Tp>
    _Tp
    __dirichlet_beta_lerch(_Tp __s)
    {
      return __lerch_phi(_Tp{-1}, __s, _Tp{0.5L}) / std::pow(_Tp{2}, __s);
    }

  /**
   * Return the Dirichlet eta function by evaluating the Lerch trancendent:
   * @f[
   *   \eta(s) = \Phi(-1,s,1)
   * @f]
   * @param[in] __s The argument s > 1
   */
  template<typename _Tp>
    _Tp
    __dirichlet_eta_lerch(_Tp __s)
    {
      return __lerch_phi(_Tp{-1}, __s, _Tp{1});
    }

  /**
   * Return the Dirichlet lambda function by evaluating the Lerch trancendent:
   * @f[
   *   \beta(s) = \frac{1}{2^s}\Phi(1,s,\frac{1}{2})
   * @f]
   * @param[in] __s The argument s > 1
   */
  template<typename _Tp>
    _Tp
    __dirichlet_lambda_lerch(_Tp __s)
    {
      return __lerch_phi(_Tp{1}, __s, _Tp{0.5L}) / std::pow(_Tp{2}, __s);
    }

  /**
   * Return the polylog function by evaluating the Lerch trancendent:
   * @f[
   *   \L_s(z) = \Phi(z,s,1)
   * @f]
   * @param[in] __s The argument s > 1
   */
  template<typename _Tp>
    _Tp
    __polylog_lerch(_Tp __s, _Tp __z)
    {
      return __lerch_phi(__z, __s, _Tp{1});
    }

  /**
   * Return the Legendre chi function by evaluating the Lerch trancendent:
   * @f[
   *   \chi_\nu(z) = \frac{z}{2^\nu}\Phi(z^2,\nu,1)
   * @f]
   * @param[in] __s The argument s > 1
   */
  template<typename _Tp>
    _Tp
    __legendre_chi(_Tp __nu, _Tp __z)
    {
      return __z * __lerch_phi(__z * __z, __nu, _Tp{0.5L})
	   / std::pow(_Tp{2}, __nu);
    }

  /**
   * 
   */
  template<typename _Tp>
    _Tp
    __fermi_dirac_lerch(_Tp __s, _Tp __mu)
    {
      auto __expmu = std::exp(-__mu);
      auto __gamsp1 = std::tgamma(_Tp{1} + __s);
      return __gamsp1 * __lerch_phi(-__expmu, _Tp{1} + __s, _Tp{1}) / __expmu;
    }

  /**
   * 
   */
  template<typename _Tp>
    _Tp
    __bose_einstein_lerch(_Tp __s, _Tp __mu)
    {
      auto __expmu = std::exp(__mu);
      auto __gamsp1 = std::tgamma(_Tp{1} + __s);
      return __expmu * __gamsp1 * __lerch_phi(__expmu, _Tp{1} + __s, _Tp{1});
    }

  float
  lerch_phif(float __z, float __s, float __a)
  { return __lerch_phi<float>(__z, __s, __a); }

  long double
  lerch_phil(long double __z, long double __s, long double __a)
  { return __lerch_phi<long double>(__z, __s, __a); }

  template<typename _Tpz, typename _Tps, typename _Tpa>
    emsr::fp_promote_t<_Tpz, _Tps, _Tpa>
    lerch_phi(_Tpz __z, _Tps __s, _Tpa __a)
    {
      using __type = emsr::fp_promote_t<_Tpz, _Tps, _Tpa>;
      return __lerch_phi<__type>(__z, __s, __a);
    }


struct lerch_testcase
{
  double phi;
  double z;
  double s;
  double a;
  int flag;
};

lerch_testcase
lerch_tests[12]
{
  { 1.0000000000000000e+00, -1.0000000000000000e+00,  2.0000000000000000e+00,  1.0000000000000000e+00, 1},
  { 1.0000000000000000e+00,  9.9999000000000005e-01,  2.0000000000000000e+00, -1.0000000000000000e+00, 2},
  { 1.0000000000000000e+00,  9.9999000000000005e-01,  2.2999999999999998e+00, -1.5000000000000000e+00, 3},
  { 1.8420680923134405e+01,  9.9999998999999995e-01,  1.0000000000000000e+00,  1.0000000000000000e+00, 0},
  { 1.6448253852467796e+00,  9.9999000000000005e-01,  2.0000000000000000e+00,  1.0000000000000000e+00, 0},
  { 8.2246832662591696e-01, -9.9999000000000005e-01,  2.0000000000000000e+00,  1.0000000000000000e+00, 0},
  { 9.5971489709979654e-04,  9.9999000000000005e-01,  2.0000000000000000e+00,  1.0000000000000000e+03, 0},
  { 1.4275808137603091e-01,  2.9999999999999999e-01,  2.0000000000000000e+00, -4.5000000000000000e+00, 0},
  { 1.0000025000111110e+00,  1.0000000000000001e-05,  2.0000000000000000e+00,  1.0000000000000000e+00, 0},
  { 9.9998425044098438e-01, -6.3000000000000000e-05,  2.0000000000000000e+00,  1.0000000000000000e+00, 0},
  { 6.5909228798196373e-01,  3.4709929976435479e-06,  1.0000000000000000e+00,  1.5172413793103448e+00, 0},
  { 2.5880201290103731e+17,  2.9999999999999997e-04,  2.0000000000000000e+00, -3.0000000000000102e+00, 0},
};

int
main()
{
  using Tp = double;
  constexpr auto _S_nan = std::numeric_limits<Tp>::quiet_NaN();

  std::cout.precision(std::numeric_limits<Tp>::digits10);
  auto width = 8 + std::numeric_limits<Tp>::digits10;

  std::cout << "case " << std::setw(2) << "i"
	    << std::setw(width) << "z"
	    << std::setw(width) << "s"
	    << std::setw(width) << "a"
	    << std::setw(width) << "phi0"
	    << std::setw(6) << "flag"
	    << std::setw(width) << "phi"
	    << std::setw(width) << "phi-phi0"
	    << std::setw(width) << "lphi"
	    << std::setw(width) << "lphi-phi0"
	    << std::setw(width) << "phi-lphi"
	    << '\n';
  std::cout << "---- " << std::setw(2) << "-"
	    << std::setw(width) << "---------"
	    << std::setw(width) << "---------"
	    << std::setw(width) << "---------"
	    << std::setw(width) << "---------"
	    << std::setw(6) << "----"
	    << std::setw(width) << "---------"
	    << std::setw(width) << "---------"
	    << std::setw(width) << "---------"
	    << std::setw(width) << "---------"
	    << std::setw(width) << "---------"
	    << '\n';
  for (int i = 0; i < 12; ++i)
    {
      const auto& tcase = lerch_tests[i];
      std::cout << "case " << std::setw(2) << i + 1
                << std::setw(width) << tcase.z
                << std::setw(width) << tcase.s
                << std::setw(width) << tcase.a
                << std::setw(width) << tcase.phi
		<< std::setw(6) << tcase.flag;
      auto phi = Tp{0};
      try
	{
	  phi = lerch_phi(tcase.z, tcase.s, tcase.a);
	  auto test0 = phi - tcase.phi;
	  std::cout << std::setw(width) << phi
                    << std::setw(width) << test0;
	}
      catch (...)
	{
	  std::cout << std::setw(width) << "fail";
	  std::cout << std::setw(width) << "fail";
	  phi = _S_nan;
	}
      double acc = 2 * std::numeric_limits<Tp>::epsilon();
      double lphi = 0.0;
      int iter = 0;
      auto ok = lerchphi(&tcase.z, &tcase.s, &tcase.a, &acc, &lphi, &iter);
      if (ok == 0)
	std::cout << std::setw(width) << lphi
		  << std::setw(width) << lphi - tcase.phi
		  << std::setw(width) << phi - lphi;
      else
	std::cout << std::setw(width) << "fail"
		  << std::setw(width) << "fail"
		  << std::setw(width) << "fail";
      if (ok != tcase.flag)
	std::cout << std::setw(12) << "flag error";

      std::cout << '\n';
    }

  auto s = 1.0;
  auto a = 2.0;
  std::cout << "\n Phi(z,1,2) Tests\n";
  std::cout << " s = " << std::setw(width) << s << '\n';
  std::cout << " a = " << std::setw(width) << a << '\n';
  for (int iz = -99; iz <= +99; ++iz)
    {
      auto z = 0.01 * iz;
      auto lerch1 = __lerch_sum(z, s, a);
      auto lerch2 = __lerch_vanwijngaarden_sum(z, s, a);
      //auto lerch3 = __lerch_double_sum(z, s, a);
      auto lerch4 = __lerch_delta_vanwijngaarden_sum(z, s, a);
      double acc = 2 * std::numeric_limits<Tp>::epsilon();
      double lphi = 0.0;
      int iter = 0;
      auto ok = lerchphi(&z, &s, &a, &acc, &lphi, &iter);
      if (ok != 0)
	lphi = _S_nan;
      std::cout << ' ' << std::setw(width) << z
		<< ' ' << std::setw(width) << lerch1
		<< ' ' << std::setw(width) << lerch2
		//<< ' ' << std::setw(width) << lerch3
		<< ' ' << std::setw(width) << lerch4
		<< ' ' << std::setw(width) << lerch2 - lerch1
		<< ' ' << std::setw(width) << lerch4 - lerch1
		<< ' ' << std::setw(width) << lerch4 - lphi
		<< '\n';
    }

  s = 2.0;
  a = 1.0;
  std::cout << "\n Phi(z,2,1) Tests\n";
  std::cout << " s = " << std::setw(width) << s << '\n';
  std::cout << " a = " << std::setw(width) << a << '\n';
  for (int iz = -99; iz <= +99; ++iz)
    {
      auto z = 0.01 * iz;
      auto lerch1 = __lerch_sum(z, s, a);
      auto lerch2 = __lerch_vanwijngaarden_sum(z, s, a);
      //auto lerch3 = __lerch_double_sum(z, s, a);
      auto lerch4 = __lerch_delta_vanwijngaarden_sum(z, s, a);
      double acc = 2 * std::numeric_limits<Tp>::epsilon();
      double lphi = 0.0;
      int iter = 0;
      auto ok = lerchphi(&z, &s, &a, &acc, &lphi, &iter);
      if (ok != 0)
	lphi = _S_nan;
      std::cout << ' ' << std::setw(width) << z
		<< ' ' << std::setw(width) << lerch1
		<< ' ' << std::setw(width) << lerch2
		//<< ' ' << std::setw(width) << lerch3
		<< ' ' << std::setw(width) << lerch4
		<< ' ' << std::setw(width) << lerch2 - lerch1
		<< ' ' << std::setw(width) << lerch4 - lerch1
		<< ' ' << std::setw(width) << lerch4 - lphi
		<< '\n';
    }

  std::cout << "\nDilogarithm Tests\n";
  _Statistics<Tp> dilog_stats;
  s = 2.0;
  a = 1.0;
  std::cout << '\n';
  std::cout << " s = " << std::setw(width) << s << '\n';
  std::cout << " a = " << std::setw(width) << a << '\n';
  std::cout << std::setw(width) << "z"
	    << std::setw(width) << "z Phi(z, s, 1)"
	    << std::setw(width) << "Li_s(z)"
	    << std::setw(width) << "zPhi - Li"
	    << '\n';
  for (int iz = -99; iz <= +99; ++iz)
    {
      auto z = 0.01 * iz;
      auto zlerch = _S_nan;
      try
	{
	  zlerch = z * lerch_phi(z, s, a);
	}
      catch (...)
	{
	  std::cout << " fail\n";
	}
      auto dilog = __gnu_cxx::dilog(z);
      auto delta = zlerch - dilog;
      dilog_stats << delta;
      std::cout << ' ' << std::setw(width) << z
		<< ' ' << std::setw(width) << zlerch
		<< ' ' << std::setw(width) << dilog
		<< ' ' << std::setw(width) << delta
		<< '\n';
    }
  std::cout << "// mean(Phi - zeta)    : " << dilog_stats.mean() << '\n';
  std::cout << "// variance(Phi - zeta): " << dilog_stats.variance() << '\n';
  std::cout << "// stddev(Phi - zeta)  : " << dilog_stats.std_deviation() << '\n';

  std::cout << "\nRiemann Zeta Tests\n";
  _Statistics<Tp> riemann_stats;
  auto z = 1.0;
  a = 1.0;
  std::cout << '\n';
  std::cout << " z = " << std::setw(width) << z << '\n';
  std::cout << " a = " << std::setw(width) << a << '\n';
  std::cout << std::setw(width) << "s"
	    << std::setw(width) << "Phi(1, s, 1)"
	    << std::setw(width) << "zeta(s)"
	    << std::setw(width) << "Phi - zeta"
	    << '\n';
  for (int is = 101; is <= 200; ++is)
    {
      auto s = 0.01 * is;
      auto lerch = _S_nan;
      try
	{
	  lerch = lerch_phi(z, s, a);
	}
      catch (...)
	{
	}
      auto zeta = std::riemann_zeta(s);
      auto delta = lerch - zeta;
      riemann_stats << delta;
      std::cout << ' ' << std::setw(width) << s
		<< ' ' << std::setw(width) << lerch
		<< ' ' << std::setw(width) << zeta
		<< ' ' << std::setw(width) << delta
		<< '\n';
    }
  std::cout << "// mean(Phi - zeta)    : " << riemann_stats.mean() << '\n';
  std::cout << "// variance(Phi - zeta): " << riemann_stats.variance() << '\n';
  std::cout << "// stddev(Phi - zeta)  : " << riemann_stats.std_deviation() << '\n';

  std::cout << "\nHurwitz Zeta Tests\n";
  for (int ia = 1; ia <= 10; ++ia)
    {
      _Statistics<Tp> hurwitz_stats;
      auto a = 1.0 * ia;
      auto z = 1.0;
      std::cout << '\n';
      std::cout << " z = " << std::setw(width) << z << '\n';
      std::cout << " a = " << std::setw(width) << a << '\n';
      std::cout << std::setw(width) << "s"
		<< std::setw(width) << "Phi(1, s, a)"
		<< std::setw(width) << "zeta(s, a)"
		<< std::setw(width) << "Phi - zeta"
		<< '\n';
      for (int is = 101; is <= 200; ++is)
	{
	  auto s = 0.01 * is;
	  auto lerch = _S_nan;
	  try
	    {
	      lerch = lerch_phi(z, s, a);
	    }
	  catch (...)
	    {
	    }
	  auto zeta = __gnu_cxx::hurwitz_zeta(s, a);
	  auto delta = lerch - zeta;
	  hurwitz_stats << delta;
	  std::cout << ' ' << std::setw(width) << s
		    << ' ' << std::setw(width) << lerch
		    << ' ' << std::setw(width) << zeta
		    << ' ' << std::setw(width) << delta
		    << '\n';
	}
      std::cout << "// mean(Phi - zeta)    : " << hurwitz_stats.mean() << '\n';
      std::cout << "// variance(Phi - zeta): " << hurwitz_stats.variance() << '\n';
      std::cout << "// stddev(Phi - zeta)  : " << hurwitz_stats.std_deviation() << '\n';
    }

  std::cout << '\n';
  for (int ia = 1; ia <= 10; ++ia)
    {
      auto a = 1.0 * ia;
      std::cout << "\n a = " << std::setw(width) << a << '\n';
      for (int is = 0; is <= 50; ++is)
	{
	  auto s = 0.1 * is;
	  std::cout << "\n s = " << std::setw(width) << s << '\n' << '\n';
	  for (int iz = -99; iz <= +99; ++iz)
	    {
	      auto z = 0.01 * iz;
	      auto lerch1 = __lerch_sum(z, s, a);
	      auto lerch2 = __lerch_vanwijngaarden_sum(z, s, a);
	      //auto lerch3 = __lerch_double_sum(z, s, a);
	      auto lerch4 = __lerch_delta_vanwijngaarden_sum(z, s, a);
	      double acc = 2 * std::numeric_limits<Tp>::epsilon();
	      double lphi = 0.0;
	      int iter = 0;
	      auto ok = lerchphi(&z, &s, &a, &acc, &lphi, &iter);
	      if (ok != 0)
	        lphi = _S_nan;
	      std::cout << ' ' << std::setw(width) << z
			<< ' ' << std::setw(width) << lerch1
			<< ' ' << std::setw(width) << lerch2
			//<< ' ' << std::setw(width) << lerch3
			<< ' ' << std::setw(width) << lerch4
			<< ' ' << std::setw(width) << lerch2 - lerch1
			<< ' ' << std::setw(width) << lerch4 - lerch1
			<< ' ' << std::setw(width) << lerch4 - lphi
			<< '\n';
	    }
	}
    }

  //auto lerch1 = __lerch_vanwijngaarden_sum(-0.75, Tp{1}, Tp{2});
  //auto lerch2 = __lerch_vanwijngaarden_sum(-0.5, Tp{0}, Tp{1});
}
