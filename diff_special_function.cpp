
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

#define STD 1

#if STD
#  include <cmath>
#  include <array>
#else
#  include <cmath>
#  include <tr1/cmath>
#  include <tr1/array>
#endif
#include <bits/specfun.h>
#include "wrap_gsl.h"
#include "wrap_boost.h"
#include "wrap_burkhardt.h"

#include "test_func.tcc"

///
///
///
int
main()
{
    using _TpGSL = double;
    using Real = double;

    const auto _S_pi = __gnu_cxx::__math_constants<Real>::__pi;

    //  Unsigned integer orders for various polynomials, harmonics, and spherical bessels.
    std::vector<unsigned int> vorder{0, 1, 2, 3, 4, 5, 10, 20, 50, 100};

    // Integer orders for various polynomials, harmonics, and spherical bessels.
    std::vector<int> iorder{0, 1, 2, 5, 10, 20, 50, 100};

    //  ... corresponding "_TpGSL" integer orders for GSL.
    std::vector<_TpGSL> dvorder{std::begin(vorder), std::end(vorder)};

    //  Orders for spherical bessel functions.
    std::vector<unsigned int> sborder{0, 1, 2, 3, 4, 5, 10, 20, 50, 100};

    // Orders for cylindrical Bessel functions.
    std::vector<Real> cyl_neg_order{-5, -2, -1, -Real{2.0Q/3.0Q},
				    -Real{0.5Q}, -Real{1.0Q/3.0Q}};

    //  Orders for cylindrical Bessel functions.
    std::vector<_TpGSL> cyl_order{0, _TpGSL{1}/_TpGSL{3},
				 _TpGSL{0.5Q}, _TpGSL{2}/_TpGSL{3},
				 1, 2, 3, 5, 10, 20, 50, 100};

    // Orders for spherical bessel functions.
    std::vector<unsigned int> sph_order{0, 1, 2, 5, 10, 20, 50, 100};

    const unsigned int num_phi = 19; // 0 - 180 degrees.
    _TpGSL phi[num_phi];
    for (unsigned int i = 0; i < num_phi; ++i)
      phi[i] = _TpGSL{10} * i * _S_pi / _TpGSL{180};
    std::vector<_TpGSL> vphid(phi, phi + num_phi);

    std::vector<_TpGSL> vab{0, 0.5, 1, 2, 5, 10, 20};

    std::string basename;

#if STD
    using __gnu_cxx::airy_ai;
    using __gnu_cxx::airy_bi;
    using       std::assoc_laguerre;
    using       std::assoc_legendre;
    using __gnu_cxx::bernoulli;
    using       std::beta;
    using __gnu_cxx::binomial;
    using __gnu_cxx::chebyshev_t;
    using __gnu_cxx::chebyshev_u;
    using __gnu_cxx::chebyshev_v;
    using __gnu_cxx::chebyshev_w;
    using __gnu_cxx::clausen;
    using __gnu_cxx::clausen_c;
    using __gnu_cxx::clausen_s;
    using __gnu_cxx::comp_ellint_d;
    using       std::comp_ellint_1;
    using       std::comp_ellint_2;
    using       std::comp_ellint_3;
    using __gnu_cxx::conf_hyperg;
    using __gnu_cxx::conf_hyperg_lim;
    using __gnu_cxx::coshint;
    using __gnu_cxx::cosint;
    using __gnu_cxx::cos_pi;
    using       std::cyl_bessel_i;
    using       std::cyl_bessel_j;
    using       std::cyl_bessel_k;
    using __gnu_cxx::cyl_hankel_1;
    using __gnu_cxx::cyl_hankel_2;
    using       std::cyl_neumann;
    using __gnu_cxx::dawson;
    using __gnu_cxx::dilog;
    using __gnu_cxx::dirichlet_beta;
    using __gnu_cxx::dirichlet_eta;
    using __gnu_cxx::double_factorial;
    using       std::ellint_1;
    using       std::ellint_2;
    using       std::ellint_3;
    using __gnu_cxx::ellint_d;
    using __gnu_cxx::ellint_rc;
    using __gnu_cxx::ellint_rd;
    using __gnu_cxx::ellint_rf;
    using __gnu_cxx::ellint_rg;
    using __gnu_cxx::ellint_rj;
    using       std::expint;
    using __gnu_cxx::expint;
    using __gnu_cxx::factorial;
    using __gnu_cxx::fresnel_c;
    using __gnu_cxx::fresnel_s;
    using __gnu_cxx::gegenbauer;
    using       std::hermite;
    using __gnu_cxx::heuman_lambda;
    using __gnu_cxx::hurwitz_zeta;
    using __gnu_cxx::hyperg;
    using __gnu_cxx::ibeta;
    using __gnu_cxx::ibetac;
    using __gnu_cxx::jacobi;
    using __gnu_cxx::jacobi_sn;
    using __gnu_cxx::jacobi_cn;
    using __gnu_cxx::jacobi_dn;
    using __gnu_cxx::jacobi_zeta;
    using       std::laguerre;
    using __gnu_cxx::lbinomial;
    using __gnu_cxx::ldouble_factorial;
    using       std::legendre;
    using __gnu_cxx::legendre_q;
    using __gnu_cxx::lfactorial;
    using __gnu_cxx::lpochhammer_lower;
    using __gnu_cxx::lpochhammer;
    using __gnu_cxx::owens_t;
    using __gnu_cxx::pgamma;
    using __gnu_cxx::pochhammer_lower;
    using __gnu_cxx::pochhammer;
    using __gnu_cxx::psi;
    using __gnu_cxx::qgamma;
    using __gnu_cxx::radpoly;
    using       std::riemann_zeta;
    using __gnu_cxx::sinhc;
    using __gnu_cxx::sinhc_pi;
    using __gnu_cxx::sinc;
    using __gnu_cxx::sinc_pi;
    using __gnu_cxx::sinhc;
    using __gnu_cxx::sinhc_pi;
    using __gnu_cxx::sinhint;
    using __gnu_cxx::sinint;
    using __gnu_cxx::sin_pi;
    using       std::sph_bessel;
    using __gnu_cxx::sph_bessel_i;
    using __gnu_cxx::sph_bessel_k;
    using __gnu_cxx::sph_hankel_1;
    using __gnu_cxx::sph_hankel_2;
    using __gnu_cxx::sph_harmonic;
    using       std::sph_legendre;
    using       std::sph_neumann;
    using __gnu_cxx::tgamma_lower;
    using __gnu_cxx::tgamma;
    using __gnu_cxx::theta_1;
    using __gnu_cxx::theta_2;
    using __gnu_cxx::theta_3;
    using __gnu_cxx::theta_4;
    using __gnu_cxx::theta_s;
    using __gnu_cxx::theta_c;
    using __gnu_cxx::theta_d;
    using __gnu_cxx::theta_n;
    using __gnu_cxx::zernike;
#else
    using  std::tr1::assoc_laguerre;
    using  std::tr1::assoc_legendre;
    using  std::tr1::beta;
    using  std::tr1::comp_ellint_1;
    using  std::tr1::comp_ellint_2;
    using  std::tr1::comp_ellint_3;
    using  std::tr1::conf_hyperg;
    using  std::tr1::cyl_bessel_i;
    using  std::tr1::cyl_bessel_j;
    using  std::tr1::cyl_bessel_k;
    using  std::tr1::cyl_neumann;
    using  std::tr1::ellint_1;
    using  std::tr1::ellint_2;
    using  std::tr1::ellint_3;
    using  std::tr1::expint;
    using  std::tr1::hermite;
    using  std::tr1::hyperg;
    using  std::tr1::laguerre;
    using  std::tr1::legendre;
    using  std::tr1::riemann_zeta;
    using  std::tr1::sph_bessel;
    using  std::tr1::sph_legendre;
    using  std::tr1::sph_neumann;
#endif // STD

#if STD
    //  Airy Ai functions.
    std::cout << "airy_ai" << '\n';
    basename = "diff_airy_ai";
    rundiff(airy_ai, gsl::airy_ai, basename,
	    "x", fill_argument(std::make_pair(Real{-10}, Real{+10}),
			       std::make_pair(true, true), 41));

    //  Airy Bi functions.
    std::cout << "airy_bi" << '\n';
    basename = "diff_airy_bi";
    rundiff(airy_bi, gsl::airy_bi, basename,
	    "x", fill_argument(std::make_pair(Real{-10}, Real{+10}),
			       std::make_pair(true, true), 41));
#endif // STD

    //  Associated Laguerre polynomials.
    std::cout << "assoc_laguerre" << '\n';
    basename = "diff_assoc_laguerre";
    rundiff(assoc_laguerre, gsl::assoc_laguerre, basename,
	    "n", vorder, "m", vorder,
	    "x", fill_argument(std::make_pair(Real{0}, Real{100}),
	    		       std::make_pair(true, true), 101));


    //  Associated Legendre functions.
    std::cout << "assoc_legendre" << '\n';
    basename = "diff_assoc_legendre";
    rundiff(assoc_legendre, gsl::assoc_legendre, basename,
	    "l", vorder, "m", vorder,
	    "x", fill_argument(std::make_pair(Real{-1}, Real{1}),
	    		       std::make_pair(true, true), 1001));


    //  Beta function.
    std::cout << "beta" << '\n';
    basename = "diff_beta";
    rundiff(beta, gsl::beta, basename,
	    "x", fill_argument(std::make_pair(Real{0}, Real{100}),
			       std::make_pair(false, true), 101),
	    "y", fill_argument(std::make_pair(Real{0}, Real{100}),
			       std::make_pair(false, true), 101));


#if STD
    // Binomial coefficient.
    std::cout << "binomial" << '\n';
    basename = "diff_binomial";
    rundiff(binomial<Real>, gsl::choose, basename,
	    "n", fill_argument(std::make_pair(0U, 50U),
	    		       std::make_pair(true, true), 51),
	    "k", fill_argument(std::make_pair(0U, 50U),
	    		       std::make_pair(true, true), 51));

    // Log binomial coefficient.
    std::cout << "lbinomial" << '\n';
    basename = "diff_lbinomial";
    rundiff(lbinomial<Real>, gsl::lnchoose, basename,
	    "n", fill_argument(std::make_pair(0U, 200U),
			       std::make_pair(true, true), 201),
	    "k", fill_argument(std::make_pair(0U, 200U),
			       std::make_pair(true, true), 201));
#endif // STD


    //  Complete elliptic integrals of the first kind.
    //  Avoid poles at |x| = 1.
    std::cout << "comp_ellint_1" << '\n';
    basename = "diff_comp_ellint_1";
    rundiff(comp_ellint_1, gsl::comp_ellint_1, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 101));


    //  Complete elliptic integrals of the second kind.
    //  Avoid poles at |x| = 1.
    std::cout << "comp_ellint_2" << '\n';
    basename = "diff_comp_ellint_2";
    rundiff(comp_ellint_2, gsl::comp_ellint_2, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 101));


    //  Complete elliptic integrals of the third kind.
    //  Avoid poles at |x| = 1 and at nu = 1.
    std::cout << "comp_ellint_3" << '\n';
    basename = "diff_comp_ellint_3";
    rundiff(comp_ellint_3, gsl::comp_ellint_3, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 101),
	    "nu", fill_argument(std::make_pair(Real{0}, Real{1}),
				std::make_pair(true, false), 11));


    //  Confluent hypergeometric functions.
    //  Skip the singularity at c = 0.
    std::cout << "conf_hyperg" << '\n';
    basename = "diff_conf_hyperg";
    rundiff(conf_hyperg, gsl::conf_hyperg, basename,
	    "a", vab,
	    "c", fill_argument(std::make_pair(Real{0}, Real{10}),
			       std::make_pair(false, true), 11),
	    "x", fill_argument(std::make_pair(Real{-10}, Real{10}),
			       std::make_pair(true, true), 201));


    //  Regular modified cylindrical Bessel functions.
    std::cout << "cyl_bessel_i" << '\n';
    basename = "diff_cyl_bessel_i";
    rundiff(cyl_bessel_i, gsl::cyl_bessel_i, basename,
	    "nu", cyl_order,
	    "x", fill_argument(std::make_pair(Real{0}, Real{100}),
			       std::make_pair(true, true), 1001));


    //  Cylindrical Bessel functions (of the first kind).
    std::cout << "cyl_bessel_j" << '\n';
    basename = "diff_cyl_bessel_j";
    rundiff(cyl_bessel_j, gsl::cyl_bessel_j, basename,
	    "nu", cyl_order,
	    "x", fill_argument(std::make_pair(Real{0}, Real{100}),
			       std::make_pair(true, true), 1001));


    //  Irregular modified cylindrical Bessel functions.
    // Skip the pole at the origin.
    std::cout << "cyl_bessel_k" << '\n';
    basename = "diff_cyl_bessel_k";
    rundiff(cyl_bessel_k, gsl::cyl_bessel_k, basename,
	    "nu", cyl_order,
	    "x", fill_argument(std::make_pair(Real{0}, Real{100}),
			       std::make_pair(false, true), 1001));

#if STD
/*
    // Cylindrical Hankel functions of the first kind.
    std::cout << "cyl_hankel_1" << '\n';
    basename = "cyl_hankel_1";
    rundiff(cyl_hankel_1, beast::cyl_hankel_1, basename,
	    "nu", cyl_order,
	    "x", fill_argument(fill_argument(std::make_pair(Real{0}, Real{5}),
					     std::make_pair(false, true), 21),
			       fill_argument(std::make_pair(Real{0}, Real{100}),
					     std::make_pair(false, true), 21)));

    // Cylindrical Hankel functions of the second kind.
    std::cout << "cyl_hankel_2" << '\n';
    basename = "cyl_hankel_2";
    rundiff(cyl_hankel_2, beast::cyl_hankel_2, basename,
	    "nu", cyl_order,
	    "x", fill_argument(fill_argument(std::make_pair(Real{0}, Real{5}),
					     std::make_pair(false, true), 21),
			       fill_argument(std::make_pair(Real{0}, Real{100}),
					     std::make_pair(false, true), 21)));
*/
#endif // STD


    //  Cylindrical Neumann functions.
    // Skip the pole at the origin.
    std::cout << "cyl_neumann" << '\n';
    basename = "diff_cyl_neumann";
    rundiff(cyl_neumann, gsl::cyl_neumann, basename,
	    "nu", cyl_order,
	    "x", fill_argument(std::make_pair(Real{0}, Real{100}),
			       std::make_pair(false, true), 1001), 101);


    //  Elliptic integrals of the first kind.
    //  Avoid poles at |x| = 1.
    std::cout << "ellint_1" << '\n';
    basename = "diff_ellint_1";
    rundiff(ellint_1, gsl::ellint_1, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 101),
	    "phi", vphid);


    //  Elliptic integrals of the second kind.
    //  Avoid poles at |x| = 1.
    std::cout << "ellint_2" << '\n';
    basename = "diff_ellint_2";
    rundiff(ellint_2, gsl::ellint_2, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 101),
	    "phi", vphid);


    //  Elliptic integrals of the third kind.
    //  Avoid poles at |x| = 1 and at nu = 1.
    std::cout << "ellint_3" << '\n';
    basename = "diff_ellint_3";
    rundiff(ellint_3, gsl::ellint_3, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 101),
	    "nu", fill_argument(std::make_pair(Real{0}, Real{1}),
				std::make_pair(true, false), 11),
	    "phi", vphid);


    //  Exponential integral.
    //  Skip the pole at 0.
    std::cout << "expint" << '\n';
    basename = "diff_expint_neg";
    rundiff(expint, gsl::expint, basename,
	    "x", fill_argument(std::make_pair(Real{-50}, Real{0}),
			       std::make_pair(true, false), 51));
    basename = "diff_expint_pos";
    rundiff(expint, gsl::expint, basename,
	    "x", fill_argument(std::make_pair(Real{0}, Real{50}),
			       std::make_pair(false, true), 51));

    // Dawson integral.
    std::cout << "dawson" << '\n';
    basename = "diff_dawson";
    rundiff(dawson, gsl::dawson, basename,
	    "x", fill_argument(std::make_pair(Real{0}, Real{+20}),
			       std::make_pair(false, true), 201));


    //  Hermite polynomials
    std::cout << "hermite" << '\n';
    basename = "diff_hermite";
    rundiff(hermite, gsl::hermite, basename,
	    "n", vorder,
	    "x", fill_argument(std::make_pair(Real{-10}, Real{10}),
	  		       std::make_pair(true, true), 101));


    //  Hypergeometric functions.
    //  Skip the singularity at c = 0.
    //  Skip the singularities at x = -1.
    std::cout << "hyperg" << '\n';
    basename = "diff_hyperg";
    rundiff(hyperg, gsl::hyperg, basename,
	    "a", vab, "b", vab,
	    "c", fill_argument(std::make_pair(Real{0}, Real{10}),
			       std::make_pair(false, true), 11),
	    "x", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(true, false), 21));


    //  Laguerre polynomials.
    std::cout << "laguerre" << '\n';
    basename = "diff_laguerre";
    rundiff(laguerre, gsl::laguerre, basename,
	    "n", vorder,
	    "x", fill_argument(std::make_pair(Real{0}, Real{100}),
	  		       std::make_pair(true, true), 1001));


    //  Legendre polynomials.
    std::cout << "legendre" << '\n';
    basename = "diff_legendre";
    rundiff(legendre, gsl::legendre_p, basename,
	    "l", vorder,
	    "x", fill_argument(std::make_pair(Real{-1}, Real{1}),
	  		       std::make_pair(true, true), 1001));


    //  Riemann zeta function.
    //  Skip the pole at 1.
    std::cout << "riemann_zeta" << '\n';
    basename = "diff_riemann_zeta_neg";
    rundiff(riemann_zeta, gsl::riemann_zeta, basename,
	    "x", fill_argument(std::make_pair(Real{-10}, Real{1}),
			       std::make_pair(true, false), 56));
    basename = "diff_riemann_zeta_pos";
    rundiff(riemann_zeta, gsl::riemann_zeta, basename,
	    "x", fill_argument(std::make_pair(Real{1}, Real{30}),
			       std::make_pair(false, true), 146));

#if STD
    //  Hurwitz zeta function.
    std::cout << "hurwitz_zeta" << '\n';
    //  Skip the pole at 1.
    basename = "diff_hurwitz_zeta";
    rundiff(hurwitz_zeta, gsl::hurwitz_zeta, basename,
	    "s", fill_argument(std::make_pair(Real{1}, Real{30}),
			       std::make_pair(false, true), 146),
	    "a", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 26));
#endif // STD


    //  Spherical Bessel functions.
    std::cout << "sph_bessel" << '\n';
    basename = "diff_sph_bessel";
    rundiff(sph_bessel, gsl::sph_bessel, basename,
	    "n", sborder,
	    "x", fill_argument(std::make_pair(Real{0}, Real{100}),
	  		       std::make_pair(true, true), 1001));


    //  Spherical Legendre functions.
    std::cout << "sph_legendre" << '\n';
    basename = "diff_sph_legendre";
    rundiff(sph_legendre, gsl::sph_legendre, basename,
	    "l", vorder, "m", vorder,
	    "theta", fill_argument(std::make_pair(Real{0}, _S_pi),
	    			   std::make_pair(true, true), 1001));


    //  Spherical Neumann functions.
    // Skip the pole at the origin.
    std::cout << "sph_neumann" << '\n';
    basename = "diff_sph_neumann";
    rundiff(sph_neumann, gsl::sph_neumann, basename,
	    "n", sborder,
	    "x", fill_argument(std::make_pair(Real{0}, Real{100}),
	  		       std::make_pair(false, true), 1001));

#if STD
    //  Carlson elliptic functions R_C.
    std::cout << "ellint_rc" << '\n';
    basename = "diff_ellint_rc";
    rundiff(ellint_rc, gsl::ellint_rc, basename,
	    "x", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 11),
	    "y", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 11));

    //  Carlson elliptic functions R_D.
    std::cout << "ellint_rd" << '\n';
    basename = "diff_ellint_rd";
    rundiff(ellint_rd, gsl::ellint_rd, basename,
	    "x", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 11),
	    "y", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(true, true), 11),
	    "z", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 11));

    //  Carlson elliptic functions R_F.
    std::cout << "ellint_rf" << '\n';
    basename = "diff_ellint_rf";
    rundiff(ellint_rf, gsl::ellint_rf, basename,
	    "x", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 11),
	    "y", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(true, true), 11),
	    "z", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 11));

      // Carlson elliptic functions R_G.
      std::cout << "ellint_rg" << '\n';
      basename = "diff_ellint_rg";
      rundiff(ellint_rg, beast::ellint_rg, basename,
	      "x", fill_argument(std::make_pair(Real{0}, +Real{5}),
				 std::make_pair(false, true), 11),
	      "y", fill_argument(std::make_pair(Real{0}, +Real{5}),
				 std::make_pair(true, true), 11),
	      "z", fill_argument(std::make_pair(Real{0}, +Real{5}),
				 std::make_pair(true, true), 11));

    //  Carlson elliptic functions R_J.
    std::cout << "ellint_rj" << '\n';
    basename = "diff_ellint_rj";
    rundiff(ellint_rj, gsl::ellint_rj, basename,
	    "x", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 11),
	    "y", fill_argument(std::make_pair(Real{0}, Real{5}),
		 	       std::make_pair(true, true), 11),
	    "z", fill_argument(std::make_pair(Real{0}, Real{5}),
		 	       std::make_pair(false, true), 11),
	    "p", fill_argument(std::make_pair(Real{0}, Real{5}),
		 	       std::make_pair(false, true), 11));

    //  Dilogarithm functions.
    std::cout << "dilog" << '\n';
    basename = "diff_dilog";
    rundiff(dilog, gsl::dilog, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{-10}, _TpGSL{1}),
			       std::make_pair(true, true), 23));

    //  Upper incomplete Gamma functions.
    std::cout << "tgamma" << '\n';
    basename = "diff_tgamma";
    rundiff(tgamma, gsl::tgamma, basename,
	    "a", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{5}),
			       std::make_pair(false, true), 11),
	    "x", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{5}),
			       std::make_pair(true, true), 11));

      // Lower incomplete Gamma functions.
      std::cout << "tgamma_lower" << '\n';
      basename = "diff_tgamma_lower";
      rundiff(tgamma_lower, gsl::tgamma_lower, basename,
	      "a", fill_argument(std::make_pair(Real{0}, Real{5}),
				 std::make_pair(false, true), 11),
	      "x", fill_argument(std::make_pair(Real{0}, Real{5}),
				 std::make_pair(true, true), 11));

    //  Incomplete Beta functions.
    std::cout << "ibeta" << '\n';
    basename = "diff_ibeta";
    rundiff(ibeta, gsl::ibeta, basename,
	    "a", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{5}),
			       std::make_pair(false, true), 11),
	    "b", fill_argument(std::make_pair(_TpGSL{5}, _TpGSL{0}),
			       std::make_pair(true, false), 11),
	    "x", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{1}),
			       std::make_pair(false, false), 21));

    //  Complementary incomplete Beta functions.
    std::cout << "ibetac" << '\n';
    basename = "diff_ibetac";
    rundiff(ibetac, beast::ibetac, basename,
	    "a", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{5}),
			       std::make_pair(false, true), 11),
	    "b", fill_argument(std::make_pair(_TpGSL{5}, _TpGSL{0}),
			       std::make_pair(true, false), 11),
	    "x", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{1}),
			       std::make_pair(false, false), 21));

    //  Digamma or psi functions.
    std::cout << "psi" << '\n';
    basename = "diff_psi";
    rundiff(psi, gsl::psi, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{-9.9375Q}, _TpGSL{10.0625Q}),
			       std::make_pair(true, true), 801));

    //  Sine integral or Si functions.
    std::cout << "sinint" << '\n';
    basename = "diff_sinint";
    rundiff(sinint, gsl::sinint, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{+10}),
			       std::make_pair(false, true), 101));

    //  Cosine integral or Ci functions.
    std::cout << "cosint" << '\n';
    basename = "diff_cosint";
    rundiff(cosint, gsl::cosint, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{+10}),
			       std::make_pair(false, true), 101));

    //  Hyperbolic sine integral or Shi functions.
    std::cout << "sinhint" << '\n';
    basename = "diff_sinhint";
    rundiff(sinhint, gsl::sinhint, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{+5}),
			       std::make_pair(false, true), 101));

    //  Hyperbolic cosine integral or Chi functions.
    std::cout << "coshint" << '\n';
    basename = "diff_coshint";
    rundiff(coshint, gsl::coshint, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{+5}),
			       std::make_pair(false, true), 101));

    // Dawson integral.
    std::cout << "dawson" << '\n';
    basename = "diff_dawson";
    rundiff(dawson, gsl::dawson, basename,
	     "x", fill_argument(std::make_pair(Real{0}, Real{+20}),
				std::make_pair(false, true), 201));

    // Jacobian elliptic integrals.
    std::cout << "jacobi_sn" << '\n';
    basename = "diff_jacobi_sn";
    rundiff(jacobi_sn, gsl::jacobi_sn, basename,
	     "k", fill_argument(std::make_pair(Real{-1}, Real{+1}),
				std::make_pair(true, true), 21),
	     "u", fill_argument(std::make_pair(Real{-5}, Real{+5}),
				std::make_pair(true, true), 101));

    // Jacobian elliptic integrals.
    std::cout << "jacobi_cn" << '\n';
    basename = "diff_jacobi_cn";
    rundiff(jacobi_cn, gsl::jacobi_cn, basename,
	     "k", fill_argument(std::make_pair(Real{-1}, Real{+1}),
				std::make_pair(true, true), 21),
	     "u", fill_argument(std::make_pair(Real{-5}, Real{+5}),
				std::make_pair(true, true), 101));

    // Jacobian elliptic integrals.
    std::cout << "jacobi_dn" << '\n';
    basename = "diff_jacobi_dn";
    rundiff(jacobi_dn, gsl::jacobi_dn, basename,
	     "k", fill_argument(std::make_pair(Real{-1}, Real{+1}),
				std::make_pair(true, true), 21),
	     "u", fill_argument(std::make_pair(Real{-5}, Real{+5}),
				std::make_pair(true, true), 101));

    //  Exponential integral E_n.
    std::cout << "expint" << '\n';
    basename = "diff_expint_en";
    rundiff(expint, gsl::expint, basename,
	    "n", {0, 1, 2, 3, 5},
	    "x", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{+5}),
			       std::make_pair(false, true), 101));


    //  Fresnel cosine integral.
    std::cout << "fresnel_c" << '\n';
    basename = "diff_fresnel_c";
    rundiff(fresnel_c, gsl::fresnel_c, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{-20}, _TpGSL{+20}),
			       std::make_pair(false, true), 401));

    //  Fresnel sine integral.
    std::cout << "fresnel_s" << '\n';
    basename = "diff_fresnel_s";
    rundiff(fresnel_s, gsl::fresnel_s, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{-20}, _TpGSL{+20}),
			       std::make_pair(false, true), 401));

    //  Dawson integral.
    std::cout << "dawson" << '\n';
    basename = "diff_dawson";
    rundiff(dawson, gsl::dawson, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{0}, _TpGSL{+5}),
			       std::make_pair(false, true), 101));

    // Normalized sine cardinal function.
    std::cout << "sinc" << '\n';
    basename = "diff_sinc";
    rundiff(sinc, gsl::sinc, basename,
	    "x", fill_argument(std::make_pair(Real{-20}, Real{+20}),
			       std::make_pair(true, true), 401));

    //  Sine cardinal function.
    std::cout << "sinc_pi" << '\n';
    basename = "diff_sinc_pi";
    rundiff(sinc_pi, gsl::sinc_pi, basename,
	    "x", fill_argument(std::make_pair(_TpGSL{-20}, _TpGSL{+20}),
			       std::make_pair(false, true), 401));

    // Log upper Pochhammer symbol.
    std::cout << "lpochhammer" << '\n';
    basename = "diff_lpochhammer";
    rundiff(lpochhammer, beast::lpochhammer, basename,
	    "a", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 21),
	    "x", {Real{1}, Real{2}, Real{5}, Real{10}, Real{20}, Real{50}, Real{100}});

    // Log lower Pochhammer symbol.
    std::cout << "lpochhammer_lower" << '\n';
    basename = "diff_lpochhammer_lower";
    rundiff(lpochhammer_lower, beast::lpochhammer_lower, basename,
	    "a", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 21),
	    "x", {Real{0}, Real{1}, Real{2}, Real{5}, Real{10}, Real{20}, Real{50}, Real{100}});

    // Upper Pochhammer symbols (see boost::rising_factorial).
    std::cout << "pochhammer" << '\n';
    basename = "diff_pochhammer";
    rundiff(pochhammer, beast::pochhammer, basename,
	    "a", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 21),
	    "x", dvorder);

    // Lower Pochhammer symbols (see boost::falling_factorial).
    std::cout << "pochhammer_lower" << '\n';
    basename = "diff_pochhammer_lower";
    rundiff(pochhammer_lower, beast::pochhammer_lower, basename,
	    "a", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 21),
	    "x", {Real{0}, Real{1}, Real{2}, Real{5}, Real{10}, Real{20}, Real{50}, Real{100}});
/*
    // Regular modified spherical bessel functions.
    std::cout << "sph_bessel_i" << '\n';
    basename = "diff_sph_bessel_i";
    rundiff(sph_bessel_i, gsl::sph_bessel_i, basename,
	    "n", sph_order,
	    "x", fill_argument(
		       fill_argument(std::make_pair(Real{0}, Real{5}),
				     std::make_pair(true, true), 21),
		       fill_argument(std::make_pair(Real{0}, Real{100}),
				     std::make_pair(true, true), 21)));

    // Irregular modified spherical bessel functions.
    std::cout << "sph_bessel_k" << '\n';
    basename = "diff_sph_bessel_k";
    rundiff(sph_bessel_k, gsl::sph_bessel_k, basename,
	    "n", sph_order,
	    "x", fill_argument(
			fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(false, true), 21),
			fill_argument(std::make_pair(Real{0}, Real{100}),
			       std::make_pair(false, true), 21)));
*/
    // Legendre functions of the second kind.
    std::cout << "legendre_q" << '\n';
    basename = "diff_legendre_q";
    rundiff(legendre_q, gsl::legendre_q, basename,
	    "l", vorder,
	    "x", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 21));

    // Factorial.
    std::cout << "factorial" << '\n';
    basename = "diff_factorial";
    rundiff(factorial<Real>, gsl::factorial, basename,
	    "n", fill_argument(std::make_pair(0U, 50U),
			       std::make_pair(true, true), 51));

    // Log factorial.
    std::cout << "lfactorial" << '\n';
    basename = "diff_lfactorial";
    rundiff(lfactorial<Real>, gsl::lfactorial, basename,
	    "n", fill_argument(std::make_pair(0U, 500U),
			       std::make_pair(true, true), 501));

    // Double factorial.
    std::cout << "double_factorial" << '\n';
    basename = "diff_double_factorial";
    rundiff(double_factorial<Real>, gsl::double_factorial, basename,
	    "n", fill_argument(std::make_pair(0, 50),
			       std::make_pair(true, true), 51));

    // Log double factorial.
    std::cout << "ldouble_factorial" << '\n';
    basename = "diff_ldouble_factorial";
    rundiff(ldouble_factorial<Real>, gsl::ldouble_factorial, basename,
	    "n", fill_argument(std::make_pair(0, 500),
			       std::make_pair(true, true), 501));

    // Binomial coefficient.
    std::cout << "binomial" << '\n';
    basename = "diff_binomial";
    rundiff(binomial<Real>, gsl::choose, basename,
	    "n", fill_argument(std::make_pair(0U, 50U),
			       std::make_pair(true, true), 51),
	    "k", fill_argument(std::make_pair(0U, 50U),
			       std::make_pair(true, true), 51));

    // Log binomial coefficient.
    std::cout << "lbinomial" << '\n';
    basename = "diff_lbinomial";
    rundiff(lbinomial<Real>, gsl::lnchoose, basename,
	    "n", fill_argument(std::make_pair(0U, 200U),
			       std::make_pair(true, true), 201),
	    "k", fill_argument(std::make_pair(0U, 200U),
			       std::make_pair(true, true), 201));

    // Gegenbauer polynomials.
    std::cout << "gegenbauer" << '\n';
    basename = "diff_gegenbauer";
    rundiff(gegenbauer, gsl::gegenpoly_n, basename,
	    "n", vorder,
	    "alpha", fill_argument(std::make_pair(Real{0}, Real{5}),
				   std::make_pair(true, true), 11),
            "x", fill_argument(std::make_pair(Real{0}, Real{20}),
			       std::make_pair(true, true), 41));

    // Chebyshev polynomials of the first kind.
    std::cout << "chebyshev_t - UNTESTED" << '\n';
/*
    basename = "diff_chebyshev_t";
    rundiff(chebyshev_t, gsl::chebyshev_t, basename,
	     "n", {0U, 1U, 5U, 8U, 10U, 20U, 40U, 100U},
	     "x", fill_argument(std::make_pair(Real{-1}, Real{+1}),
				std::make_pair(true, true), 21));
*/
    // Chebyshev polynomials of the second kind.
    std::cout << "chebyshev_u - UNTESTED" << '\n';
    basename = "diff_chebyshev_u";

    // Chebyshev polynomials of the third kind.
    std::cout << "chebyshev_v - UNTESTED" << '\n';
    basename = "diff_chebyshev_v";

    // Chebyshev polynomials of the fourth kind.
    std::cout << "chebyshev_w - UNTESTED" << '\n';
    basename = "diff_chebyshev_w";

    // Jacobi polynomials.
    std::cout << "jacobi" << '\n';
    basename = "diff_jacobi";
    rundiff(jacobi, gsl::jacobi, basename,
	    "n", vorder,
	    "alpha", fill_argument(std::make_pair(Real{0}, Real{5}),
				   std::make_pair(true, true), 11),
            "beta", fill_argument(std::make_pair(Real{0}, Real{5}),
				  std::make_pair(true, true), 21),
            "x", fill_argument(std::make_pair(Real{-10}, Real{10}),
				  std::make_pair(true, true), 41));

    // Radial polynomials.
    std::cout << "radpoly" << '\n';
    basename = "diff_radpoly";
    rundiff(radpoly, gsl::radpoly, basename,
	    "n", vorder, "m", vorder,
            "rho", fill_argument(std::make_pair(Real{0}, Real{1}),
				 std::make_pair(true, true), 21));

    // Zernike polynomials.
    std::cout << "zernike" << '\n';
    basename = "diff_zernike";
    rundiff(zernike, gsl::zernike, basename,
	    "n", vorder, "m", iorder,
            "rho", fill_argument(std::make_pair(Real{0}, Real{1}),
				 std::make_pair(true, true), 21),
            "phi", vphid);

    // Confluent hypergeometric limit functions.
    // Skip the singularity at c = 0.
    std::cout << "conf_hyperg_lim" << '\n';
    basename = "diff_conf_hyperg_lim";
    rundiff(conf_hyperg_lim, gsl::conf_hyperg_lim, basename,
	    "c", fill_argument(std::make_pair(Real{0}, Real{10}),
			       std::make_pair(false, true), 11),
	    "x", fill_argument(std::make_pair(Real{-10}, Real{10}),
			       std::make_pair(true, true), 21));

    // Heuman lambda functions.
    // Avoid poles at |x| = 1.
    std::cout << "heuman_lambda" << '\n';
    basename = "diff_heuman_lambda";
    rundiff(heuman_lambda, beast::heuman_lambda, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 21),
	    "phi", vphid);

    // Elliptic D integrals.
    // Avoid poles at |x| = 1.
    std::cout << "ellint_d" << '\n';
    basename = "diff_ellint_d";
    rundiff(ellint_d, beast::ellint_d, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 21),
	    "phi", vphid);

    // Complementary elliptic D integrals.
    // Avoid poles at |x| = 1.
    std::cout << "comp_ellint_d" << '\n';
    basename = "diff_comp_ellint_d";
    rundiff(comp_ellint_d, beast::comp_ellint_d, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 21));

    // Jacobi zeta functions.
    // Avoid poles at |x| = 1.
    std::cout << "jacobi_zeta" << '\n';
    basename = "diff_jacobi_zeta";
    rundiff(jacobi_zeta, beast::jacobi_zeta, basename,
	    "k", fill_argument(std::make_pair(Real{-1}, Real{1}),
			       std::make_pair(false, false), 21),
	    "phi", vphid);

/*
    // Cylindrical Hankel functions of the first kind.
    std::cout << "cyl_hankel_1" << '\n';
    basename = "diff_cyl_hankel_1";
    rundiff(cyl_hankel_1, beast::cyl_hankel_1, basename,
	    "nu", cyl_neg_order,
	    "x", fill_argument(
		       fill_argument(std::make_pair(Real{0}, Real{5}),
				     std::make_pair(true, true), 21),
		       fill_argument(std::make_pair(Real{0}, Real{100}),
				     std::make_pair(true, true), 21)));

    // Cylindrical Hankel functions of the second kind.
    std::cout << "cyl_hankel_2" << '\n';
    basename = "diff_cyl_hankel_2";
    rundiff(cyl_hankel_2, beast::cyl_hankel_2, basename,
	    "nu", cyl_neg_order,
	    "x", fill_argument(
		       fill_argument(std::make_pair(Real{0}, Real{5}),
				     std::make_pair(true, true), 21),
		       fill_argument(std::make_pair(Real{0}, Real{100}),
				     std::make_pair(true, true), 21)));

    // Spherical Hankel functions of the first kind.
    std::cout << "sph_hankel_1" << '\n';
    basename = "diff_sph_hankel_1";
    rundiff(sph_hankel_1, beast::sph_hankel_1, basename,
	     "n", sph_order,
	     "x", fill_argument(
			fill_argument(std::make_pair(Real{0}, Real{5}),
				      std::make_pair(true, true), 21),
			fill_argument(std::make_pair(Real{0}, Real{100}),
				      std::make_pair(true, true), 21)));

    // Spherical Hankel functions of the second kind.
    std::cout << "sph_hankel_2" << '\n';
    basename = "diff_sph_hankel_2";
    rundiff(sph_hankel_2, beast::sph_hankel_2, basename,
	    "n", sph_order,
	    "x", fill_argument(
		       fill_argument(std::make_pair(Real{0}, Real{5}),
				     std::make_pair(true, true), 21),
		       fill_argument(std::make_pair(Real{0}, Real{100}),
				     std::make_pair(true, true), 21)));
*/

    // Spherical harmonic functions.
    std::cout << "sph_harmonic" << '\n';
    basename = "diff_sph_harmonic";
    rundiff(sph_harmonic, beast::sph_harmonic, basename,
	    "l", vorder, "m", iorder,
	    "theta", fill_argument(std::make_pair(Real{0}, _S_pi),
				   std::make_pair(true, true), 21),
	    "phi", vphid);

/*
    // Dirichlet eta function.
    std::cout << "dirichlet_eta" << '\n';
    // Skip the pole at 1.
    basename = "diff_dirichlet_eta";
    rundiff(dirichlet_eta, gsl::dirichlet_eta, basename,
	    "s", fill_argument(
		       fill_argument(std::make_pair(Real{-10}, Real{1}),
				     std::make_pair(true, false), 56),
		       fill_argument(std::make_pair(Real{1}, Real{30}),
				     std::make_pair(false, true), 146)));
*/

    // Owens T functions.
    std::cout << "owens_t" << '\n';
    basename = "diff_owens_t";
    rundiff(owens_t, beast::owens_t, basename,
	    "h", fill_argument(std::make_pair(Real{-5}, Real{5}),
			       std::make_pair(true, true), 41),
	    "a", fill_argument(std::make_pair(Real{0}, Real{5}),
			       std::make_pair(true, true), 21));

    // clausen_c function.
    std::cout << "clausen_c" << '\n';
    basename = "diff_clausen_c";
    rundiff(clausen_c, gsl::clausen_c, basename,
	    "m", fill_argument(std::make_pair(2U, 2U),
			       std::make_pair(true, true), 1),
	    "w", fill_argument(std::make_pair(Real{-10}, Real{+10}),
			       std::make_pair(true, true), 41));

    // Bernoulli numbers.
    std::cout << "bernoulli" << '\n';
    basename = "diff_bernoulli";
    rundiff(bernoulli<Real>, beast::bernoulli, basename,
	    "n", fill_argument(std::make_pair(0U, 100U),
			       std::make_pair(true, true), 101));

    // Reperiodized sine function.
    std::cout << "sin_pi" << '\n';
    basename = "diff_sin_pi";
    rundiff(sin_pi, beast::sin_pi, basename,
	    "x", fill_argument(std::make_pair(Real{-20}, Real{+50}),
			       std::make_pair(false, true), 701));

    // Reperiodized cosine function.
    std::cout << "cos_pi" << '\n';
    basename = "diff_cos_pi";
    rundiff(cos_pi, beast::cos_pi, basename,
	    "x", fill_argument(std::make_pair(Real{-20}, Real{+50}),
			       std::make_pair(false, true), 701));

#endif // STD

  return 0;
}

