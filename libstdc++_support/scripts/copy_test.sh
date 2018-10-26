#!/bin/bash

tool="cp -f"

suffix="_tr29124"
if [ $# -ge 1 ]; then
  suffix="$1"
fi

test_dir="$HOME/tr29124_test/testsuite/special_functions"

gcc_dir="$HOME/gcc${suffix}/libstdc++-v3/testsuite/special_functions"

${tool} ${test_dir}/01_assoc_laguerre/* ${gcc_dir}/01_assoc_laguerre/
${tool} ${test_dir}/02_assoc_legendre/* ${gcc_dir}/02_assoc_legendre/
${tool} ${test_dir}/03_beta/*           ${gcc_dir}/03_beta/
${tool} ${test_dir}/04_comp_ellint_1/*  ${gcc_dir}/04_comp_ellint_1/
${tool} ${test_dir}/05_comp_ellint_2/*  ${gcc_dir}/05_comp_ellint_2/
${tool} ${test_dir}/06_comp_ellint_3/*  ${gcc_dir}/06_comp_ellint_3/
${tool} ${test_dir}/07_cyl_bessel_i/*   ${gcc_dir}/07_cyl_bessel_i/
${tool} ${test_dir}/08_cyl_bessel_j/*   ${gcc_dir}/08_cyl_bessel_j/
${tool} ${test_dir}/09_cyl_bessel_k/*   ${gcc_dir}/09_cyl_bessel_k/
${tool} ${test_dir}/10_cyl_neumann/*    ${gcc_dir}/10_cyl_neumann/
${tool} ${test_dir}/11_ellint_1/*       ${gcc_dir}/11_ellint_1/
${tool} ${test_dir}/12_ellint_2/*       ${gcc_dir}/12_ellint_2/
${tool} ${test_dir}/13_ellint_3/*       ${gcc_dir}/13_ellint_3/
${tool} ${test_dir}/14_expint/*	        ${gcc_dir}/14_expint/
${tool} ${test_dir}/15_hermite/*        ${gcc_dir}/15_hermite/
${tool} ${test_dir}/16_laguerre/*       ${gcc_dir}/16_laguerre/
${tool} ${test_dir}/17_legendre/*       ${gcc_dir}/17_legendre/
${tool} ${test_dir}/18_riemann_zeta/*   ${gcc_dir}/18_riemann_zeta/
${tool} ${test_dir}/19_sph_bessel/*     ${gcc_dir}/19_sph_bessel/
${tool} ${test_dir}/20_sph_legendre/*   ${gcc_dir}/20_sph_legendre/
${tool} ${test_dir}/21_sph_neumann/*    ${gcc_dir}/21_sph_neumann/

text_dir="$HOME/tr29124_test/testsuite/ext/special_functions"
ext_dir="$HOME/gcc${suffix}/libstdc++-v3/testsuite/ext/special_functions"

${tool} ${text_dir}/airy_ai/*            ${ext_dir}/airy_ai
${tool} ${text_dir}/airy_bi/*            ${ext_dir}/airy_bi
${tool} ${text_dir}/bernoulli/*          ${ext_dir}/bernoulli
${tool} ${text_dir}/binomial/*           ${ext_dir}/binomial
${tool} ${text_dir}/chebyshev_t/*        ${ext_dir}/chebyshev_t
${tool} ${text_dir}/chebyshev_u/*        ${ext_dir}/chebyshev_u
${tool} ${text_dir}/chebyshev_v/*        ${ext_dir}/chebyshev_v
${tool} ${text_dir}/chebyshev_w/*        ${ext_dir}/chebyshev_w
${tool} ${text_dir}/clausen_cl/*         ${ext_dir}/clausen_cl
${tool} ${text_dir}/comp_ellint_d/*      ${ext_dir}/comp_ellint_d
${tool} ${text_dir}/conf_hyperg/*        ${ext_dir}/conf_hyperg
${tool} ${text_dir}/conf_hyperg_lim/*    ${ext_dir}/conf_hyperg_lim
${tool} ${text_dir}/coshint/*            ${ext_dir}/coshint
${tool} ${text_dir}/cosint/*             ${ext_dir}/cosint
${tool} ${text_dir}/cyl_hankel_1/*       ${ext_dir}/cyl_hankel_1
${tool} ${text_dir}/cyl_hankel_2/*       ${ext_dir}/cyl_hankel_2
${tool} ${text_dir}/dawson/*             ${ext_dir}/dawson
${tool} ${text_dir}/digamma/*            ${ext_dir}/digamma
${tool} ${text_dir}/dilog/*              ${ext_dir}/dilog
${tool} ${text_dir}/dirichlet_beta/*     ${ext_dir}/dirichlet_beta
${tool} ${text_dir}/dirichlet_eta/*      ${ext_dir}/dirichlet_eta
${tool} ${text_dir}/dirichlet_lambda/*   ${ext_dir}/dirichlet_lambda
${tool} ${text_dir}/double_factorial/*   ${ext_dir}/double_factorial
${tool} ${text_dir}/ellint_d/*           ${ext_dir}/ellint_d
${tool} ${text_dir}/ellint_rc/*          ${ext_dir}/ellint_rc
${tool} ${text_dir}/ellint_rd/*          ${ext_dir}/ellint_rd
${tool} ${text_dir}/ellint_rf/*          ${ext_dir}/ellint_rf
${tool} ${text_dir}/ellint_rg/*          ${ext_dir}/ellint_rg
${tool} ${text_dir}/ellint_rj/*          ${ext_dir}/ellint_rj
${tool} ${text_dir}/ellnome/*            ${ext_dir}/ellnome
${tool} ${text_dir}/euler/*              ${ext_dir}/euler
${tool} ${text_dir}/eulerian_1/*         ${ext_dir}/eulerian_1
${tool} ${text_dir}/eulerian_2/*         ${ext_dir}/eulerian_2
${tool} ${text_dir}/expint/*             ${ext_dir}/expint
${tool} ${text_dir}/factorial/*          ${ext_dir}/factorial
${tool} ${text_dir}/falling_factorial/*  ${ext_dir}/falling_factorial
${tool} ${text_dir}/fresnel_c/*          ${ext_dir}/fresnel_c
${tool} ${text_dir}/fresnel_s/*          ${ext_dir}/fresnel_s
${tool} ${text_dir}/gamma_reciprocal/*   ${ext_dir}/gamma_reciprocal
${tool} ${text_dir}/gegenbauer/*         ${ext_dir}/gegenbauer
${tool} ${text_dir}/heuman_lambda/*      ${ext_dir}/heuman_lambda
${tool} ${text_dir}/hurwitz_zeta/*       ${ext_dir}/hurwitz_zeta
${tool} ${text_dir}/hyperg/*             ${ext_dir}/hyperg
${tool} ${text_dir}/ibeta/*              ${ext_dir}/ibeta
${tool} ${text_dir}/ibetac/*             ${ext_dir}/ibetac
${tool} ${text_dir}/jacobi_sn/*          ${ext_dir}/jacobi_sn
${tool} ${text_dir}/jacobi_cn/*          ${ext_dir}/jacobi_cn
${tool} ${text_dir}/jacobi_dn/*          ${ext_dir}/jacobi_dn
${tool} ${text_dir}/lbinomial/*          ${ext_dir}/lbinomial
${tool} ${text_dir}/ldouble_factorial/*  ${ext_dir}/ldouble_factorial
${tool} ${text_dir}/legendre_q/*         ${ext_dir}/legendre_q
${tool} ${text_dir}/lfactorial/*         ${ext_dir}/lfactorial
${tool} ${text_dir}/lfalling_factorial/* ${ext_dir}/lfalling_factorial
${tool} ${text_dir}/lgamma/*             ${ext_dir}/lgamma
${tool} ${text_dir}/lrising_factorial/*  ${ext_dir}/lrising_factorial
${tool} ${text_dir}/owens_t/*            ${ext_dir}/owens_t
${tool} ${text_dir}/gamma_p/*            ${ext_dir}/gamma_p
${tool} ${text_dir}/polygamma/*          ${ext_dir}/polygamma
${tool} ${text_dir}/gamma_q/*            ${ext_dir}/gamma_q
${tool} ${text_dir}/radpoly/*            ${ext_dir}/radpoly
${tool} ${text_dir}/rising_factorial/*   ${ext_dir}/rising_factorial
${tool} ${text_dir}/sinc/*               ${ext_dir}/sinc
${tool} ${text_dir}/sinc_pi/*            ${ext_dir}/sinc_pi
${tool} ${text_dir}/sinhint/*            ${ext_dir}/sinhint
${tool} ${text_dir}/sinint/*             ${ext_dir}/sinint
${tool} ${text_dir}/sin_pi/*             ${ext_dir}/sin_pi
${tool} ${text_dir}/sph_bessel_i/*       ${ext_dir}/sph_bessel_i
${tool} ${text_dir}/sph_bessel_k/*       ${ext_dir}/sph_bessel_k
${tool} ${text_dir}/sph_hankel_1/*       ${ext_dir}/sph_hankel_1
${tool} ${text_dir}/sph_hankel_2/*       ${ext_dir}/sph_hankel_2
${tool} ${text_dir}/sph_harmonic/*       ${ext_dir}/sph_harmonic
${tool} ${text_dir}/stirling_1/*         ${ext_dir}/stirling_1
${tool} ${text_dir}/stirling_2/*         ${ext_dir}/stirling_2
${tool} ${text_dir}/tgamma/*             ${ext_dir}/tgamma
${tool} ${text_dir}/tgamma_lower/*       ${ext_dir}/tgamma_lower
${tool} ${text_dir}/theta_1/*            ${ext_dir}/theta_1
${tool} ${text_dir}/theta_2/*            ${ext_dir}/theta_2
${tool} ${text_dir}/theta_3/*            ${ext_dir}/theta_3
${tool} ${text_dir}/theta_4/*            ${ext_dir}/theta_4
${tool} ${text_dir}/zernike/*            ${ext_dir}/zernike
