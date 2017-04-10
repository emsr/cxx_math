#!  /bin/bash

tool="cp -f"
makedir="mkdir -p"

#rm -rf "testsuite"

utildir="testsuite/util"
test_dir="testsuite/special_functions"
text_dir="testsuite/ext/special_functions"
tr1_dir="testsuite/tr1/5_numerical_facilities/special_functions"

suffix="_tr29124"
if [ $# -ge 1 ]; then
  suffix="$1"
fi

#src_dir="$HOME/gcc${suffix}/libstdc++-v3"
src_dir=.


${makedir} ${utildir}

${tool} specfun_testcase.h              ${utildir}
${tool} specfun_stats.h                 ${utildir}


${makedir} ${test_dir}/01_assoc_laguerre
${makedir} ${test_dir}/02_assoc_legendre
${makedir} ${test_dir}/03_beta
${makedir} ${test_dir}/04_comp_ellint_1
${makedir} ${test_dir}/05_comp_ellint_2
${makedir} ${test_dir}/06_comp_ellint_3
${makedir} ${test_dir}/07_cyl_bessel_i
${makedir} ${test_dir}/08_cyl_bessel_j
${makedir} ${test_dir}/09_cyl_bessel_k
${makedir} ${test_dir}/10_cyl_neumann
${makedir} ${test_dir}/11_ellint_1
${makedir} ${test_dir}/12_ellint_2
${makedir} ${test_dir}/13_ellint_3
${makedir} ${test_dir}/14_expint
${makedir} ${test_dir}/15_hermite
${makedir} ${test_dir}/16_laguerre
${makedir} ${test_dir}/17_legendre
${makedir} ${test_dir}/18_riemann_zeta
${makedir} ${test_dir}/19_sph_bessel
${makedir} ${test_dir}/20_sph_legendre
${makedir} ${test_dir}/21_sph_neumann

${tool} check/check_assoc_laguerre.cc   ${test_dir}/01_assoc_laguerre/check_value.cc
${tool} check/check_assoc_legendre.cc   ${test_dir}/02_assoc_legendre/check_value.cc
${tool} check/check_beta.cc             ${test_dir}/03_beta/check_value.cc
${tool} check/check_comp_ellint_1.cc    ${test_dir}/04_comp_ellint_1/check_value.cc
${tool} check/check_comp_ellint_2.cc    ${test_dir}/05_comp_ellint_2/check_value.cc
${tool} check/check_comp_ellint_3.cc    ${test_dir}/06_comp_ellint_3/check_value.cc
${tool} check/check_cyl_bessel_i.cc     ${test_dir}/07_cyl_bessel_i/check_value.cc
${tool} check/pr56216_cyl_bessel_i.cc   ${test_dir}/07_cyl_bessel_i/pr56216.cc
${tool} check/check_cyl_bessel_j.cc     ${test_dir}/08_cyl_bessel_j/check_value.cc
${tool} check/origin_cyl_bessel_j.cc    ${test_dir}/08_cyl_bessel_j/check_origin.cc
${tool} check/check_cyl_bessel_k.cc     ${test_dir}/09_cyl_bessel_k/check_value.cc
${tool} check/check_cyl_neumann.cc      ${test_dir}/10_cyl_neumann/check_value.cc
${tool} check/origin_cyl_neumann.cc     ${test_dir}/10_cyl_neumann/check_origin.cc
${tool} check/check_ellint_1.cc         ${test_dir}/11_ellint_1/check_value.cc
${tool} check/check_ellint_2.cc         ${test_dir}/12_ellint_2/check_value.cc
${tool} check/check_ellint_3.cc         ${test_dir}/13_ellint_3/check_value.cc
${tool} check/check_expint.cc           ${test_dir}/14_expint/check_value.cc
${tool} check/pr68397.cc                ${test_dir}/14_expint/pr68397.cc
${tool} check/check_hermite.cc          ${test_dir}/15_hermite/check_value.cc
${tool} check/check_laguerre.cc         ${test_dir}/16_laguerre/check_value.cc
${tool} check/check_legendre.cc         ${test_dir}/17_legendre/check_value.cc
${tool} check/check_riemann_zeta.cc     ${test_dir}/18_riemann_zeta/check_value.cc
${tool} check/check_sph_bessel.cc       ${test_dir}/19_sph_bessel/check_value.cc
${tool} check/check_sph_legendre.cc     ${test_dir}/20_sph_legendre/check_value.cc
${tool} check/check_sph_neumann.cc      ${test_dir}/21_sph_neumann/check_value.cc


${makedir} ${text_dir}/airy_ai
${makedir} ${text_dir}/airy_bi
${makedir} ${text_dir}/bernoulli
${makedir} ${text_dir}/binomial
${makedir} ${text_dir}/chebyshev_t
${makedir} ${text_dir}/chebyshev_u
${makedir} ${text_dir}/chebyshev_v
${makedir} ${text_dir}/chebyshev_w
${makedir} ${text_dir}/clausen_cl
${makedir} ${text_dir}/comp_ellint_d
${makedir} ${text_dir}/conf_hyperg
${makedir} ${text_dir}/conf_hyperg_lim
${makedir} ${text_dir}/coshint
${makedir} ${text_dir}/cosint
${makedir} ${text_dir}/cos_pi
${makedir} ${text_dir}/cyl_hankel_1
${makedir} ${text_dir}/cyl_hankel_2
${makedir} ${text_dir}/dawson
${makedir} ${text_dir}/debye
${makedir} ${text_dir}/dilog
${makedir} ${text_dir}/dirichlet_beta
${makedir} ${text_dir}/dirichlet_eta
${makedir} ${text_dir}/dirichlet_lambda
${makedir} ${text_dir}/double_factorial
${makedir} ${text_dir}/ellint_d
${makedir} ${text_dir}/ellint_rc
${makedir} ${text_dir}/ellint_rd
${makedir} ${text_dir}/ellint_rf
${makedir} ${text_dir}/ellint_rg
${makedir} ${text_dir}/ellint_rj
${makedir} ${text_dir}/ellnome
${makedir} ${text_dir}/euler
${makedir} ${text_dir}/eulerian_1
${makedir} ${text_dir}/eulerian_2
${makedir} ${text_dir}/expint
${makedir} ${text_dir}/factorial
${makedir} ${text_dir}/fresnel_c
${makedir} ${text_dir}/fresnel_s
${makedir} ${text_dir}/gamma_reciprocal
${makedir} ${text_dir}/gegenbauer
${makedir} ${text_dir}/heuman_lambda
${makedir} ${text_dir}/hurwitz_zeta
${makedir} ${text_dir}/hyperg
${makedir} ${text_dir}/ibeta
${makedir} ${text_dir}/ibetac
${makedir} ${text_dir}/jacobi
${makedir} ${text_dir}/jacobi_sn
${makedir} ${text_dir}/jacobi_cn
${makedir} ${text_dir}/jacobi_dn
${makedir} ${text_dir}/lbinomial
${makedir} ${text_dir}/ldouble_factorial
${makedir} ${text_dir}/legendre_q
${makedir} ${text_dir}/lfactorial
${makedir} ${text_dir}/lgamma
${makedir} ${text_dir}/lfalling_factorial
${makedir} ${text_dir}/lrising_factorial
${makedir} ${text_dir}/owens_t
${makedir} ${text_dir}/pgamma
${makedir} ${text_dir}/falling_factorial
${makedir} ${text_dir}/rising_factorial
${makedir} ${text_dir}/psi
${makedir} ${text_dir}/qgamma
${makedir} ${text_dir}/radpoly
${makedir} ${text_dir}/sinc
${makedir} ${text_dir}/sinc_pi
${makedir} ${text_dir}/sinhint
${makedir} ${text_dir}/sinint
${makedir} ${text_dir}/sin_pi
${makedir} ${text_dir}/sph_bessel_i
${makedir} ${text_dir}/sph_bessel_k
${makedir} ${text_dir}/sph_hankel_1
${makedir} ${text_dir}/sph_hankel_2
${makedir} ${text_dir}/sph_harmonic
${makedir} ${text_dir}/stirling_1
${makedir} ${text_dir}/stirling_2
${makedir} ${text_dir}/tgamma
${makedir} ${text_dir}/tgamma_lower
${makedir} ${text_dir}/theta_1
${makedir} ${text_dir}/theta_2
${makedir} ${text_dir}/theta_3
${makedir} ${text_dir}/theta_4
${makedir} ${text_dir}/zernike

${tool} check/deathmatch_comp_ellint.cc   ${text_dir}/deathmatch_comp_ellint.cc
${tool} check/deathmatch_conf_hyperg.cc   ${text_dir}/deathmatch_conf_hyperg.cc
${tool} check/deathmatch_hyperg.cc        ${text_dir}/deathmatch_hyperg.cc

${tool} check/check_airy_ai.cc            ${text_dir}/airy_ai/check_value.cc
${tool} check/check_airy_bi.cc            ${text_dir}/airy_bi/check_value.cc
${tool} check/check_bernoulli.cc          ${text_dir}/bernoulli/check_value.cc
${tool} check/check_binomial.cc           ${text_dir}/binomial/check_value.cc
${tool} check/check_chebyshev_t.cc        ${text_dir}/chebyshev_t/check_value.cc
${tool} check/check_chebyshev_u.cc        ${text_dir}/chebyshev_u/check_value.cc
${tool} check/check_chebyshev_v.cc        ${text_dir}/chebyshev_v/check_value.cc
${tool} check/check_chebyshev_w.cc        ${text_dir}/chebyshev_w/check_value.cc
${tool} check/check_chi.cc                ${text_dir}/coshint/check_chi.cc
${tool} check/check_clausen_cl.cc         ${text_dir}/clausen_cl/check_value.cc
${tool} check/check_comp_ellint_d.cc      ${text_dir}/comp_ellint_d/check_value.cc
${tool} check/check_conf_hyperg.cc        ${text_dir}/conf_hyperg/check_value.cc
${tool} check/check_conf_hyperg_lim.cc    ${text_dir}/conf_hyperg_lim/check_value.cc
${tool} check/check_coshint.cc            ${text_dir}/coshint/check_value.cc
${tool} check/check_cosint.cc             ${text_dir}/cosint/check_value.cc
${tool} check/check_cos_pi.cc             ${text_dir}/cos_pi/check_value.cc
${tool} check/check_cyl_hankel_1.cc       ${text_dir}/cyl_hankel_1/check_value.cc
${tool} check/pr56216_cyl_hankel_1.cc     ${text_dir}/cyl_hankel_1/pr56216.cc
${tool} check/check_cyl_hankel_2.cc       ${text_dir}/cyl_hankel_2/check_value.cc
${tool} check/pr56216_cyl_hankel_2.cc     ${text_dir}/cyl_hankel_2/pr56216.cc
${tool} check/check_dawson.cc             ${text_dir}/dawson/check_value.cc
${tool} check/check_debye.cc              ${text_dir}/debye/check_value.cc
${tool} check/check_dilog.cc              ${text_dir}/dilog/check_value.cc
${tool} check/check_dirichlet_beta.cc     ${text_dir}/dirichlet_beta/check_value.cc
${tool} check/check_dirichlet_eta.cc      ${text_dir}/dirichlet_eta/check_value.cc
${tool} check/check_dirichlet_lambda.cc   ${text_dir}/dirichlet_lambda/check_value.cc
${tool} check/check_double_factorial.cc   ${text_dir}/double_factorial/check_value.cc
${tool} check/check_ellint_d.cc           ${text_dir}/ellint_d/check_value.cc
${tool} check/check_ellint_rc.cc          ${text_dir}/ellint_rc/check_value.cc
${tool} check/check_ellint_rd.cc          ${text_dir}/ellint_rd/check_value.cc
${tool} check/check_ellint_rf.cc          ${text_dir}/ellint_rf/check_value.cc
${tool} check/check_ellint_rg.cc          ${text_dir}/ellint_rg/check_value.cc
${tool} check/check_ellint_rj.cc          ${text_dir}/ellint_rj/check_value.cc
${tool} check/check_ellnome.cc            ${text_dir}/ellnome/check_value.cc
${tool} check/check_euler.cc              ${text_dir}/euler/check_value.cc
${tool} check/check_eulerian_1.cc         ${text_dir}/eulerian_1/check_value.cc
${tool} check/check_eulerian_2.cc         ${text_dir}/eulerian_2/check_value.cc
${tool} check/check_expint_en.cc          ${text_dir}/expint/check_value.cc
${tool} check/check_factorial.cc          ${text_dir}/factorial/check_value.cc
${tool} check/check_falling_factorial.cc  ${text_dir}/falling_factorial/check_value.cc
${tool} check/check_fresnel_c.cc          ${text_dir}/fresnel_c/check_value.cc
${tool} check/check_fresnel_s.cc          ${text_dir}/fresnel_s/check_value.cc
${tool} check/check_gamma_reciprocal.cc   ${text_dir}/gamma_reciprocal/check_value.cc
${tool} check/check_gegenbauer.cc         ${text_dir}/gegenbauer/check_value.cc
${tool} check/check_heuman_lambda.cc      ${text_dir}/heuman_lambda/check_value.cc
${tool} check/check_hurwitz_zeta.cc       ${text_dir}/hurwitz_zeta/check_value.cc
${tool} check/check_hyperg.cc             ${text_dir}/hyperg/check_value.cc
${tool} check/check_ibeta.cc              ${text_dir}/ibeta/check_value.cc
${tool} check/check_ibetac.cc             ${text_dir}/ibetac/check_value.cc
${tool} check/check_jacobi.cc             ${text_dir}/jacobi/check_value.cc
${tool} check/check_jacobi_sn.cc          ${text_dir}/jacobi_sn/check_value.cc
${tool} check/check_jacobi_cn.cc          ${text_dir}/jacobi_cn/check_value.cc
${tool} check/check_jacobi_dn.cc          ${text_dir}/jacobi_dn/check_value.cc
${tool} check/check_lbinomial.cc          ${text_dir}/lbinomial/check_value.cc
${tool} check/check_ldouble_factorial.cc  ${text_dir}/ldouble_factorial/check_value.cc
${tool} check/check_legendre_q.cc         ${text_dir}/legendre_q/check_value.cc
${tool} check/check_lfactorial.cc         ${text_dir}/lfactorial/check_value.cc
${tool} check/check_lfalling_factorial.cc ${text_dir}/lfalling_factorial/check_value.cc
${tool} check/check_lgamma.cc             ${text_dir}/lgamma/check_value.cc
${tool} check/check_lrising_factorial.cc  ${text_dir}/lrising_factorial/check_value.cc
${tool} check/check_owens_t.cc            ${text_dir}/owens_t/check_value.cc
${tool} check/check_pgamma.cc             ${text_dir}/pgamma/check_value.cc
${tool} check/check_psi.cc                ${text_dir}/psi/check_value.cc
${tool} check/check_qgamma.cc             ${text_dir}/qgamma/check_value.cc
${tool} check/check_radpoly.cc            ${text_dir}/radpoly/check_value.cc
${tool} check/check_rising_factorial.cc   ${text_dir}/rising_factorial/check_value.cc
${tool} check/check_shi.cc                ${text_dir}/sinhint/check_shi.cc
${tool} check/check_sinc.cc               ${text_dir}/sinc/check_value.cc
${tool} check/check_sinc_pi.cc            ${text_dir}/sinc_pi/check_value.cc
${tool} check/check_sinhint.cc            ${text_dir}/sinhint/check_value.cc
${tool} check/check_sinint.cc             ${text_dir}/sinint/check_value.cc
${tool} check/check_sin_pi.cc             ${text_dir}/sin_pi/check_value.cc
${tool} check/check_sph_bessel_i.cc       ${text_dir}/sph_bessel_i/check_value.cc
${tool} check/check_sph_bessel_k.cc       ${text_dir}/sph_bessel_k/check_value.cc
${tool} check/check_sph_hankel_1.cc       ${text_dir}/sph_hankel_1/check_value.cc
${tool} check/check_sph_hankel_2.cc       ${text_dir}/sph_hankel_2/check_value.cc
${tool} check/check_sph_harmonic.cc       ${text_dir}/sph_harmonic/check_value.cc
${tool} check/check_stirling_1.cc         ${text_dir}/stirling_1/check_value.cc
${tool} check/check_stirling_2.cc         ${text_dir}/stirling_2/check_value.cc
${tool} check/check_tgamma.cc             ${text_dir}/tgamma/check_value.cc
${tool} check/check_tgamma_lower.cc       ${text_dir}/tgamma_lower/check_value.cc
${tool} check/check_theta_1.cc            ${text_dir}/theta_1/check_value.cc
${tool} check/check_theta_2.cc            ${text_dir}/theta_2/check_value.cc
${tool} check/check_theta_3.cc            ${text_dir}/theta_3/check_value.cc
${tool} check/check_theta_4.cc            ${text_dir}/theta_4/check_value.cc
${tool} check/check_zernike.cc            ${text_dir}/zernike/check_value.cc


${makedir} ${tr1_dir}

${tool} testcase.h ${tr1_dir}

${makedir} ${tr1_dir}/01_assoc_laguerre
${makedir} ${tr1_dir}/02_assoc_legendre
${makedir} ${tr1_dir}/03_beta
${makedir} ${tr1_dir}/04_comp_ellint_1
${makedir} ${tr1_dir}/05_comp_ellint_2
${makedir} ${tr1_dir}/06_comp_ellint_3
${makedir} ${tr1_dir}/07_conf_hyperg
${makedir} ${tr1_dir}/08_cyl_bessel_i
${makedir} ${tr1_dir}/09_cyl_bessel_j
${makedir} ${tr1_dir}/10_cyl_bessel_k/airy.cc
${makedir} ${tr1_dir}/11_cyl_neumann
${makedir} ${tr1_dir}/12_ellint_1
${makedir} ${tr1_dir}/13_ellint_2
${makedir} ${tr1_dir}/14_ellint_3
${makedir} ${tr1_dir}/15_expint
${makedir} ${tr1_dir}/16_hermite
${makedir} ${tr1_dir}/17_hyperg
${makedir} ${tr1_dir}/18_laguerre
${makedir} ${tr1_dir}/19_legendre
${makedir} ${tr1_dir}/20_riemann_zeta
${makedir} ${tr1_dir}/21_sph_bessel
${makedir} ${tr1_dir}/22_sph_legendre
${makedir} ${tr1_dir}/23_sph_neumann

${tool} check/check_tr1_assoc_laguerre.cc   ${tr1_dir}/01_assoc_laguerre/check_value.cc
${tool} check/check_tr1_assoc_legendre.cc   ${tr1_dir}/02_assoc_legendre/check_value.cc
${tool} check/check_tr1_beta.cc	            ${tr1_dir}/03_beta/check_value.cc
${tool} check/check_tr1_comp_ellint_1.cc    ${tr1_dir}/04_comp_ellint_1/check_value.cc
${tool} check/check_tr1_comp_ellint_2.cc    ${tr1_dir}/05_comp_ellint_2/check_value.cc
${tool} check/check_tr1_comp_ellint_3.cc    ${tr1_dir}/06_comp_ellint_3/check_value.cc
${tool} check/check_tr1_conf_hyperg.cc      ${tr1_dir}/07_conf_hyperg/check_value.cc
${tool} check/check_tr1_cyl_bessel_i.cc     ${tr1_dir}/08_cyl_bessel_i/check_value.cc
${tool} check/check_tr1_cyl_bessel_j.cc     ${tr1_dir}/09_cyl_bessel_j/check_value.cc
${tool} check/check_tr1_cyl_bessel_k.cc     ${tr1_dir}/10_cyl_bessel_k/check_value.cc
${tool} check/check_tr1_cyl_neumann.cc      ${tr1_dir}/11_cyl_neumann/check_value.cc
${tool} check/check_tr1_ellint_1.cc	    ${tr1_dir}/12_ellint_1/check_value.cc
${tool} check/check_tr1_ellint_2.cc	    ${tr1_dir}/13_ellint_2/check_value.cc
${tool} check/check_tr1_ellint_3.cc	    ${tr1_dir}/14_ellint_3/check_value.cc
${tool} check/check_tr1_expint.cc           ${tr1_dir}/15_expint/check_value_neg.cc
${tool} check/check_tr1_hermite.cc	    ${tr1_dir}/16_hermite/check_value.cc
${tool} check/check_tr1_hyperg.cc	    ${tr1_dir}/17_hyperg/check_value.cc
${tool} check/check_tr1_laguerre.cc	    ${tr1_dir}/18_laguerre/check_value.cc
${tool} check/check_tr1_legendre.cc	    ${tr1_dir}/19_legendre/check_value.cc
${tool} check/check_tr1_riemann_zeta.cc     ${tr1_dir}/20_riemann_zeta/check_value_neg.cc
${tool} check/check_tr1_sph_bessel.cc       ${tr1_dir}/21_sph_bessel/check_value.cc
${tool} check/check_tr1_sph_legendre.cc     ${tr1_dir}/22_sph_legendre/check_value.cc
${tool} check/check_tr1_sph_neumann.cc      ${tr1_dir}/23_sph_neumann/check_value.cc
