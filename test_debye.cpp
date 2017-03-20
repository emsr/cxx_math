/*
$HOME/bin_tr29124/bin/g++ -std=gnu++17 -g -Wall -Wextra -Wno-psabi -I. -o test_debye test_debye.cpp -lquadmath -Lwrappers/debug -lwrap_boost
LD_LIBRARY_PATH=wrappers/debug:$LD_LIBRARY_PATH ./test_debye > test_debye.txt

PATH=wrappers/debug:$PATH $HOME/bin/bin/g++ -std=gnu++17 -g -Wall -Wextra -Wno-psabi -I. -o test_debye test_debye.cpp -lquadmath -Lwrappers/debug -lwrap_boost
./test_debye > test_debye.txt
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <ext/cmath>

  /**
   * Return the Debye integral or the incomplete Riemann zeta function:
   * @todo: We should return both the integral and it's complement.
   * @f[
   *    \zeta_x(s) = \frac{1}{\Gamma(s)}\int_{0}^{x}\frac{t^{s-1}}{e^t-1}dt
   *          = \sum{k=1}{\infty}k^{-s}P(s,kx)
   * @f]
   * @f[
   *    \Zeta_x(s) = \frac{1}{\Gamma(s)}\int_{x}^{\infty}\frac{t^{s-1}}{e^t-1}dt
   *          = \sum{k=1}{\infty}k^{-s}Q(s,kx)
   * @f]
   * where @f$ P(a,x), Q(a,x) @f$ is the incomplete gamma function ratios.
   * The Debye integrals are:
   * @f[
   *    D_n(x) = \frac{n}{x+n}\int_{0}^{x}\frac{t^n}{e^t-1}dt
   *           = \Gamma(n+1)[\zeta(n+1)-\zeta_x(n+1)]
   * @f]
   * and
   * @f[
   *    \int_{0}^{x}\frac{t^n}{e^t-1}dt = \Gamma(n+1)\zeta_x(n+1)
   * @f]
   */
  template<typename _Tp>
    _Tp
    __debye(unsigned int __n, _Tp __x)
    {
      if (__isnan(__x))
	return std::numeric_limits<_Tp>::quiet_NaN();
      else if (__n < 1 || __n > 20)
	return _Tp{-1};
      else if (__x >= _Tp{3})
	{
	  // For values up to 4.80 the list of zeta functions
	  // and the sum up to k < K are huge enough to gain
	  // numeric stability in the sum

	  // List of n! zeta(n+1)
	  static constexpr std::size_t __num_nfact_zetanp1 = 26;
	  static constexpr long double
	  __nfact_zetanp1[__num_nfact_zetanp1]
	  { 0.0L, // inf
	    1.644934066848226436472415166646025189221L,
	    2.404113806319188570799476323022899981535L,
	    6.493939402266829149096022179247007416657L,
	    2.488626612344087823195277167496882003334e+01L,
	    1.220811674381338967657421515749104633481e+02L,
	    7.260114797149844353246542358918536669129e+02L,
	    5.060549875237639470468573602083608424904e+03L,
	    4.040097839874763488532782365545085427880e+04L,
	    3.632409114223826268071435255657477648916e+05L,
	    3.630593311606628712990618842832054105454e+06L,
	    3.992662298773108670232707324047201489782e+07L,
	    4.790603798898314524268767644990636347182e+08L,
	    6.227402193410971764192853408947415910063e+09L,
	    8.718095783017206784519122031036435756615e+10L,
	    1.307694352218913820890099907485110170283e+12L,
	    2.092294967948151090663165568811151437906e+13L,
	    3.556887858592237159756123967161824480923e+14L,
	    6.402385922818921400735649453323975529936e+15L,
	    1.216452164536393966698766962740413842385e+17L,
	    2.432903168507861321737256818243197497087e+18L,
	    5.109095435437028567765027486047348085447e+19L,
	    1.124000861780891230602152949001944312688e+21L,
	    2.585201827987687776778026178504241061606e+22L,
	    6.204484202247755610769915204946357633986e+23L,
	    1.551121027447213289898317465714050200972e+25L,
	  };

	  const auto _S_eps = __gnu_cxx::__epsilon(__x);

	  // n!zeta(n) is the integral for x=inf, Abramowitz & Stegun 27.1.3
	  auto __sum = _Tp{0};
	  if (__n < __num_nfact_zetanp1)
	    __sum += _Tp(__nfact_zetanp1[__n]);
	  else
	    {
	      // Try to compute n!zeta(n+1).
	      if (std::__detail::_S_num_factorials<_Tp>)
		__sum += std::__detail::__factorial<_Tp>(__n)
		       * std::__detail::__riemann_zeta<_Tp>(__n + 1);
	      else
		return __gnu_cxx::__infinity(__x);
	    }

	  // the number of terms needed in the k-sum for x = 0, 1, 2, 3...
	  // Reflects the n=1 case, because higher n need less terms.
	  static constexpr std::size_t __num_kLim = 14;
	  static constexpr std::size_t
	    __kLim[__num_kLim]
	    {0, 0, 0, 13, 10, 8, 7, 6, 5, 5, 4, 4, 4, 3};


	  /**
	   * Compute the Debye integral:
	   * @f[
	   *    D_n(x) = 1 - \sum_{k = 1}^{\infty} e^{-kx}
	   *       \frac{n}{k}\sum_{m=0}^{n}\frac{n!}{(n-m)!}frac{1}{(kx)^m}
	   * @f]
	   * Abramowitz & Stegun 27.1.2
	   */
	  const auto __xi = static_cast<std::size_t>(__x);
	  const std::size_t __kmax = (__xi < __num_kLim ? __kLim[__xi] : 3);
	  auto __term = _Tp{0};
	  for(unsigned int __k = 1; __k <= __kmax; ++__k)
	    {
	      const auto __xk = __x * __k;
	      auto __ksum = _Tp{1} / __xk;
	      auto __kterm = _Tp(__n) * __ksum / __xk;  // n / (xk)^2
	      for (unsigned int __s = 1; __s <= __n; ++__s)
		__ksum += std::exchange(__kterm,
					_Tp(__n - __s) * __kterm / __xk);

	      __term -= std::exp(-__xk) * __ksum * std::pow(__x, _Tp(__n + 1));
	    }
	  __sum += __term;
	  if (std::abs(__term) < _S_eps * std::abs(__sum))
	    return __sum;
	  return __sum;
	}
      else
	{
	  // List of absolute values of Bernoulli numbers of index 2n,
	  // multiplied  by (2\pi)^{2n}/(2n)!, and 2 subtracted.
	  // @f[
	  //    (-1)^{n+1}\frac{(2\pi)^{2n} B_{2n}}{(2n)!} = 2[\zeta(2n) - 1]
	  // @f]
          // where @f$ \zeta(s) @f$ is the Riemann zeta function.
	  const auto _S_1_2pi = __gnu_cxx::__const_one_div_2_pi(__x);
	  static constexpr std::size_t __num_coeff = 71;
	  static constexpr long double
	  __coeff[__num_coeff]
	  { 0.0L,
	    1.289868133696452872944830333292e+00L,
	    1.646464674222763830320073930823e-01L,
	    3.468612396889827942903585958184e-02L,
	    8.154712395888678757370477017305e-03L,
	    1.989150255636170674291917800638e-03L,
	    4.921731066160965972759960954793e-04L,
	    1.224962701174096585170902102707e-04L,
	    3.056451881730374346514297527344e-05L,
	    7.634586529999679712923289243879e-06L,
	    1.907924067745592226304077366899e-06L,
	    4.769010054554659800072963735060e-07L,
	    1.192163781025189592248804158716e-07L,
	    2.980310965673008246931701326140e-08L,
	    7.450668049576914109638408036805e-09L,
	    1.862654864839336365743529470042e-09L,
	    4.656623667353010984002911951881e-10L,
	    1.164154417580540177848737197821e-10L,
	    2.910384378208396847185926449064e-11L,
	    7.275959094757302380474472711747e-12L,
	    1.818989568052777856506623677390e-12L,
	    4.547473691649305030453643155957e-13L,
	    1.136868397525517121855436593505e-13L,
	    2.842170965606321353966861428348e-14L,
	    7.105427382674227346596939068119e-15L,
	    1.776356842186163180619218277278e-15L,
	    4.440892101596083967998640188409e-16L,
	    1.110223024969096248744747318102e-16L,
	    2.775557561945046552567818981300e-17L,
	    6.938893904331845249488542992219e-18L,
	    1.734723476023986745668411013469e-18L,
	    4.336808689994439570027820336642e-19L,
	    1.084202172491329082183740080878e-19L,
	    2.710505431220232916297046799365e-20L,
	    6.776263578041593636171406200902e-21L,
	    1.694065894509399669649398521836e-21L,
	    4.235164736272389463688418879636e-22L,
	    1.058791184067974064762782460584e-22L,
	    2.646977960169798160618902050189e-23L,
	    6.617444900424343177893912768629e-24L,
	    1.654361225106068880734221123349e-24L,
	    4.135903062765153408791935838694e-25L,
	    1.033975765691286264082026643327e-25L,
	    2.584939414228213340076225223666e-26L,
	    6.462348535570530772269628236053e-27L,
	    1.615587133892632406631747637268e-27L,
	    4.038967834731580698317525293132e-28L,
	    1.009741958682895139216954234507e-28L,
	    2.524354896707237808750799932127e-29L,
	    6.310887241768094478219682436680e-30L,
	    1.577721810442023614704107565240e-30L,
	    3.944304526105059031370476640000e-31L,
	    9.860761315262647572437533499000e-32L,
	    2.465190328815661892443976898000e-32L,
	    6.162975822039154730370601500000e-33L,
	    1.540743955509788682510501190000e-33L,
	    3.851859888774471706184973900000e-34L,
	    9.629649721936179265360991000000e-35L,
	    2.407412430484044816328953000000e-35L,
	    6.018531076210112040809600000000e-36L,
	    1.504632769052528010200750000000e-36L,
	    3.761581922631320025497600000000e-37L,
	    9.403954806578300063715000000000e-38L,
	    2.350988701644575015901000000000e-38L,
	    5.877471754111437539470000000000e-39L,
	    1.469367938527859384580000000000e-39L,
	    3.673419846319648458500000000000e-40L,
	    9.183549615799121117000000000000e-41L,
	    2.295887403949780249000000000000e-41L,
	    5.739718509874450320000000000000e-42L,
	    1.434929627468612270000000000000e-42L,
	  };

	  /**
	   * Compute the Debye integral:
	   * @f[
	   *    D_n(x) = 1 - \frac{n x}{2(n+1)}
	   *       + n \sum_{k = 1}^{\infty} \frac{B_{2k} x^{2k}}{(2k + n)(2k)!}
	   * @f]
           * for @f$ |x| < 2\pi @f$.
	   * Abramowitz-Stegun 27.1.1
	   */
	  auto __sum = _Tp{0};

	  const auto _S_eps = __gnu_cxx::__epsilon(__x);
	  const auto __x2pi = __x * _S_1_2pi;
	  const auto __x2pi2 = __x2pi * __x2pi;
	  auto __x2pi2k = _Tp{1};
	  for(unsigned int __k = 1; __k < __num_coeff - 1; ++__k)
	     {
	       const auto __sumold = __sum;

	       __x2pi2k *= __x2pi2;
	       __sum += (_Tp{2} + __coeff[__k]) * __x2pi2k / _Tp(2 * __k + __n);

	       ++__k;
	       __x2pi2k *= __x2pi2;
	       __sum -= (_Tp{2} + __coeff[__k]) * __x2pi2k / _Tp(2 * __k + __n);

	       if (std::abs(__sum - __sumold) < _S_eps)
        	 break;
	     }
	  __sum += _Tp{1} / _Tp(__n) - __x / _Tp(2 * (1 + __n));
	  return __sum * std::pow(__x, _Tp(__n));
	}
    }

template<typename _Tp>
  void
  test_debye(_Tp __proto = _Tp{})
  {
    std::cout.precision(__gnu_cxx::__max_digits10(__proto));
    std::cout << std::showpoint << std::scientific;
    auto width = 8 + std::cout.precision();

    std::cout << '\n' << '\n';
    std::cout << ' ' << std::setw(width) << "x"
	      << ' ' << std::setw(width) << "Debye_1(x)"
	      << ' ' << std::setw(width) << "Debye_2(x)"
	      << ' ' << std::setw(width) << "Debye_3(x)"
	      << ' ' << std::setw(width) << "Debye_4(x)"
	      << ' ' << std::setw(width) << "Debye_5(x)"
	      << '\n';
    for (int i = -50; i <= +200; ++i)
      {
	auto x = _Tp{0.1L} * i;
	std::cout << ' ' << std::setw(width) << x;
	for (int n = 1; n <= 5; ++n)
	  std::cout << ' ' << std::setw(width) << __debye(n, x);
	std::cout << '\n';
      }
  }

int
main()
{
  test_debye(1.0);

  return 0;
}

