#!/bin/bash

# This tool 'installs' from a gcc directory to the corresponding bin directory
# to avoid going through the actual install process.

tool="cp -f"

suffix="_tr29124"
if [ $# -ge 1 ]; then
  suffix="$1"
fi

src_dir="$HOME/gcc${suffix}/libstdc++-v3/include"
if [ -d "$1" ]; then 
  src_dir="$1"
fi
src_impl_dir="${src_dir}/bits"
src_ext_dir="${src_dir}/ext"
src_std_dir="${src_dir}/std"

dst_dir="$HOME/bin${suffix}/include/c++/7.0.1"
if [ -d "$2" ]; then 
  dst_dir="$2"
fi
dst_impl_dir="${dst_dir}/bits"
dst_ext_dir="${dst_dir}/ext"
dst_std_dir="${dst_dir}"

${tool} "${src_dir}/c_global/cmath"             "${dst_std_dir}/c_global"
${tool} "${src_std_dir}/limits"                 "${dst_std_dir}"
${tool} "${src_std_dir}/complex"                "${dst_std_dir}"

${tool} "${src_ext_dir}/cmath"                  "${dst_ext_dir}"
${tool} "${src_ext_dir}/math_const.h"           "${dst_ext_dir}"
${tool} "${src_ext_dir}/math_util.h"            "${dst_ext_dir}"
${tool} "${src_ext_dir}/type_traits.h"          "${dst_ext_dir}"

${tool} "${src_impl_dir}/specfun.h"             "${dst_impl_dir}"
${tool} "${src_impl_dir}/specfun_state.h"       "${dst_impl_dir}"
${tool} "${src_impl_dir}/specfun_util.h"        "${dst_impl_dir}"
${tool} "${src_impl_dir}/complex_util.h"        "${dst_impl_dir}"
${tool} "${src_impl_dir}/complex_util.tcc"      "${dst_impl_dir}"
${tool} "${src_impl_dir}/complex128.h"          "${dst_impl_dir}"
${tool} "${src_impl_dir}/complex128_math.h"     "${dst_impl_dir}"
${tool} "${src_impl_dir}/float128_io.h"         "${dst_impl_dir}"
${tool} "${src_impl_dir}/float128_io.tcc"       "${dst_impl_dir}"
${tool} "${src_impl_dir}/float128_limits.h"     "${dst_impl_dir}"
${tool} "${src_impl_dir}/float128_math.h"       "${dst_impl_dir}"
${tool} "${src_impl_dir}/numeric_limits.h"      "${dst_impl_dir}"
${tool} "${src_impl_dir}/numeric_limits_float128.h"  "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_airy.tcc"           "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_bernoulli.tcc"      "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_bessel.tcc"         "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_beta.tcc"           "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_cardinal.tcc"       "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_chebyshev.tcc"      "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_coulomb.tcc"        "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_dawson.tcc"         "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_distributions.tcc"  "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_ellint.tcc"         "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_euler.tcc"          "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_expint.tcc"         "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_fresnel.tcc"        "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_gamma.tcc"          "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_gegenbauer.tcc"     "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_hankel.tcc"         "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_hermite.tcc"        "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_hyperg.tcc"         "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_hypint.tcc"         "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_jacobi.tcc"         "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_laguerre.tcc"       "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_legendre.tcc"       "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_mod_bessel.tcc"     "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_owens_t.tcc"        "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_polylog.tcc"        "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_stirling.tcc"       "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_theta.tcc"          "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_trig.tcc"           "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_trigint.tcc"        "${dst_impl_dir}"
${tool} "${src_impl_dir}/sf_zeta.tcc"           "${dst_impl_dir}"
${tool} "${src_impl_dir}/summation.h"           "${dst_impl_dir}"
${tool} "${src_impl_dir}/summation.tcc"         "${dst_impl_dir}"

