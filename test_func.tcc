#ifndef TEST_FUNC_TCC
#define TEST_FUNC_TCC 1

#include <fstream>
#include <complex>

/**
 * A class to reach into compound numeric types to extract the
 * value or element type.  This will be specialized for complex
 * and other types as appropriate.
 */
template<typename _Tp>
  struct num_traits
  {
    using value_type = _Tp;
  };

template<typename _Tp>
  using num_traits_t = typename num_traits<_Tp>::value_type;

/**
 * A class to reach into compound numeric types to extract the
 * value or element type - specialized for complex.
 */
template<>
  template<typename _Tp>
    struct num_traits<std::complex<_Tp>>
    {
      using value_type = typename std::complex<_Tp>::value_type;
    };

  /**
   * Type introspection for complex.
   */
  template<typename _Tp>
    struct is_complex : public std::false_type
    { };

  /**
   * Type introspection for complex.
   */
  template<>
    template<typename _Tp>
      struct is_complex<std::complex<_Tp>> : public std::true_type
      { };

  /**
   * Type introspection for complex.
   */
  template<typename _Tp>
    using is_complex_t = typename is_complex<_Tp>::type;

  /**
   * Type introspection for complex.
   */
  template<typename _Tp>
    constexpr bool is_complex_v = is_complex<_Tp>::value;


const std::string diffdirname = "diff/";
const std::string testdirname = "test/";

template<typename Tp>
  class filename_end
  {
  public:
    static const std::string
    suffix()
    { return std::string(".txt"); }
  };

template<>
  class filename_end<float>
  {
  public:
    static const std::string
    suffix()
    { return std::string("_f.txt"); }
  };

template<>
  class filename_end<double>
  {
  public:
    static const std::string
    suffix()
    { return std::string("_d.txt"); }
  };

template<>
  class filename_end<long double>
  {
  public:
    static const std::string
    suffix()
    { return std::string("_l.txt"); }
  };

#if !defined(__STRICT_ANSI__) && defined(_GLIBCXX_USE_FLOAT128)
template<>
  class filename_end<__float128>
  {
  public:
    static const std::string suffix() { return std::string("_q.txt"); }
};
#endif // __STRICT_ANSI__ && _GLIBCXX_USE_FLOAT128


///
/// @brief Fill a vector with evenly spaced values between two limits.
///
template<typename Tp>
  std::vector<Tp>
  fill_argument(const std::pair<Tp, Tp> & range,
                const std::pair<bool,bool> & inclusive,
                const unsigned int num_steps = 101)
  {
    std::vector<Tp> argument;

    for (unsigned int i = 0; i < num_steps; ++i)
      {
	if (i == 0 && ! inclusive.first)
          continue;
	if (i == num_steps - 1 && ! inclusive.second)
          continue;

	auto x = range.first;
	if (num_steps > 1)
	  x += Tp(i) * (range.second - range.first) / Tp(num_steps - 1);

	argument.push_back(x);
      }

    return argument;
  }

///
/// @brief Merge two test vectors.
///
template<typename Tp>
  std::vector<Tp>
  fill_argument(std::vector<Tp>&& test1, const std::vector<Tp>& test2)
  {
    std::vector<Tp> ret(std::move(test1));
    const auto ret_size = ret.size(); // test1 get clobbered by move!
    ret.resize(ret_size + test2.size());
    std::copy(test2.begin(), test2.end(), ret.begin() + ret_size);
    return ret;
  }


///
///  @brief  Run a function that takes one (1) argument.
///
template<typename Tp, typename Tp1>
  void
  runtest(Tp function(Tp1),
          const std::string & basename,
          const std::vector<Tp1> & argument1,
          bool verbose = false)
  {
    using Val = num_traits_t<Tp>;

    std::string filename = testdirname + basename + filename_end<Tp>::suffix();

    std::ofstream output(filename);
    output.precision(std::numeric_limits<Val>::digits10);
    output.flags(std::ios::showpoint);
    const auto w_real = 8 + output.precision();
    const auto w_cmplx = 2 + 2 * w_real;
    const auto w_arg1 = (is_complex_v<Tp1> ? w_cmplx : w_real);
    const auto w_ret = (is_complex_v<Tp> ? w_cmplx : w_real);

    for (unsigned int i = 0; i < argument1.size(); ++i)
      {
	auto x = argument1[i];

	output << ' ' << std::setw(w_arg1) << x;

	try
          {
            auto f = function(x);
            output << ' ' << std::setw(w_ret) << f;
          }
	catch (std::domain_error & err)
          {
            if (verbose)
              output << '\n' << err.what() << '\n';
            continue;
          }
	catch (std::runtime_error & err)
          {
            if (verbose)
              output << '\n' << err.what() << '\n';
            continue;
          }
        catch (...)
          {
            if (verbose)
              output << "\nOther error\n";
            continue;
          }
	output << '\n';
      }

    return;
  }


///
/// @brief  Run a function that takes two arguments.
///
template<typename Tp, typename Tp1, typename Tp2>
  void
  runtest(Tp function(Tp1, Tp2),
          const std::string & basename,
          const std::vector<Tp1> & argument1,
          const std::vector<Tp2> & argument2,
          bool verbose = false)
  {
    using Val = num_traits_t<Tp>;

    std::string filename = testdirname + basename + filename_end<Tp>::suffix();

    std::ofstream output(filename);
    output.precision(std::numeric_limits<Val>::digits10);
    output.flags(std::ios::showpoint);
    const auto w_real = 8 + output.precision();
    const auto w_cmplx = 2 + 2 * w_real;
    const auto w_arg1 = (is_complex_v<Tp1> ? w_cmplx : w_real);
    const auto w_arg2 = (is_complex_v<Tp2> ? w_cmplx : w_real);
    const auto w_ret = (is_complex_v<Tp> ? w_cmplx : w_real);

    for (unsigned int j = 0; j < argument2.size(); ++j)
      {
	auto y = argument2[j];

	output << "  arg2 = " << std::setw(w_arg2) << y << '\n';

	output << ' ' << std::setw(w_arg1) << "arg1 = ";
	for (unsigned int i = 0; i < argument1.size(); ++i)
          {
            auto x = argument1[i];

            output << ' ' << std::setw(w_arg1) << x;
          }
	output << '\n';

	for (unsigned int i = 0; i < argument1.size(); ++i)
          {
            auto x = argument1[i];

            try
              {
		auto f = function(x, y);
		output << ' ' << std::setw(w_ret) << f;
              }
            catch (std::domain_error & err)
              {
        	if (verbose)
                  output << '\n' << err.what() << '\n';
        	continue;
              }
            catch (std::runtime_error & err)
              {
        	if (verbose)
                  output << '\n' << err.what() << '\n';
        	continue;
              }
            catch (...)
              {
        	if (verbose)
                  output << "\nOther error\n";
        	continue;
              }
          }
	output << '\n';
      }

    return;
  }


///
///  @brief  Run a function that takes three arguments.
///
template<typename Tp, typename Tp1, typename Tp2, typename Tp3>
  void
  runtest(Tp function(Tp1, Tp2, Tp3),
          const std::string & basename,
          const std::vector<Tp1> & argument1,
          const std::vector<Tp2> & argument2,
          const std::vector<Tp3> & argument3,
          bool verbose = false)
  {
    using Val = num_traits_t<Tp>;

    std::string filename = testdirname + basename + filename_end<Tp>::suffix();

    std::ofstream output(filename);
    output.precision(std::numeric_limits<Val>::digits10);
    output.flags(std::ios::showpoint);
    const auto w_real = 8 + output.precision();
    const auto w_cmplx = 2 + 2 * w_real;
    const auto w_arg1 = (is_complex_v<Tp1> ? w_cmplx : w_real);
    const auto w_arg2 = (is_complex_v<Tp2> ? w_cmplx : w_real);
    const auto w_arg3 = (is_complex_v<Tp3> ? w_cmplx : w_real);
    const auto w_ret = (is_complex_v<Tp> ? w_cmplx : w_real);

    for (unsigned int k = 0; k < argument3.size(); ++k)
      {
	auto z = argument3[k];
	output << "  arg3 = " << std::setw(w_arg3) << z << '\n';

	for (unsigned int j = 0; j < argument2.size(); ++j)
          {
            auto y = argument2[j];
            output << "  arg2 = " << std::setw(w_arg2) << y << '\n';

            output << ' ' << std::setw(w_arg1) << "arg1 = ";
            for (unsigned int i = 0; i < argument1.size(); ++i)
              {
        	auto x = argument1[i];

        	output << ' ' << std::setw(w_arg1) << x;
              }
            output << '\n';

            for (unsigned int i = 0; i < argument1.size(); ++i)
              {
        	auto x = argument1[i];

        	try
                  {
                    auto f = function(x, y, z);
                    output << ' ' << std::setw(w_ret) << f;
                  }
        	catch (std::domain_error & err)
                  {
                    if (verbose)
                      output << '\n' << err.what() << '\n';
                    continue;
                  }
        	catch (std::runtime_error & err)
                  {
                    if (verbose)
                      output << '\n' << err.what() << '\n';
                    continue;
                  }
        	catch (...)
        	  {
        	    if (verbose)
        	      output << "\nOther error\n";
        	    continue;
        	  }
              }
            output << '\n';
          }
	output << '\n';
      }

    return;
  }


///
///
///
template<typename Tp, typename Tp1, typename Tp2, typename Tp3, typename Tp4>
  void
  runtest(Tp function(Tp1, Tp2, Tp3, Tp4),
          const std::string & basename,
          const std::vector<Tp1> & argument1,
          const std::vector<Tp2> & argument2,
          const std::vector<Tp3> & argument3,
          const std::vector<Tp4> & argument4,
          bool verbose = false)
  {
    using Val = num_traits_t<Tp>;

    std::string filename = testdirname + basename + filename_end<Tp>::suffix();

    std::ofstream output(filename);
    output.precision(std::numeric_limits<Val>::digits10);
    output.flags(std::ios::showpoint);
    const auto w_real = 8 + output.precision();
    const auto w_cmplx = 2 + 2 * w_real;
    const auto w_arg1 = (is_complex_v<Tp1> ? w_cmplx : w_real);
    const auto w_arg2 = (is_complex_v<Tp2> ? w_cmplx : w_real);
    const auto w_arg3 = (is_complex_v<Tp3> ? w_cmplx : w_real);
    const auto w_arg4 = (is_complex_v<Tp4> ? w_cmplx : w_real);
    const auto w_ret = (is_complex_v<Tp> ? w_cmplx : w_real);

    for (unsigned int l = 0; l < argument4.size(); ++l)
      {
	auto w = argument4[l];
	output << "  arg4 = " << std::setw(w_arg4) << w << '\n';

	for (unsigned int k = 0; k < argument3.size(); ++k)
          {
            auto z = argument3[k];
            output << "  arg3 = " << std::setw(w_arg3) << z << '\n';

            for (unsigned int j = 0; j < argument2.size(); ++j)
              {
        	auto y = argument2[j];
        	output << "  arg2 = " << std::setw(w_arg2) << y << '\n';

        	output << ' ' << std::setw(w_arg1) << "arg1 = ";
        	for (unsigned int i = 0; i < argument1.size(); ++i)
                  {
                    auto x = argument1[i];

                    output << ' ' << std::setw(w_arg1) << x;
                  }
        	output << '\n';

        	for (unsigned int i = 0; i < argument1.size(); ++i)
                  {
                    auto x = argument1[i];

                    try
                      {
			auto f = function(x, y, z, w);
			output << ' ' << std::setw(w_ret) << f;
                      }
                    catch (std::domain_error & err)
                      {
                	if (verbose)
                          output << '\n' << err.what() << '\n';
                	continue;
                      }
                    catch (std::runtime_error & err)
                      {
                	if (verbose)
                          output << '\n' << err.what() << '\n';
                	continue;
                      }
        	    catch (...)
        	      {
        		if (verbose)
        		  output << "\nOther error\n";
        		continue;
        	      }
                  }
        	output << '\n';
              }
            output << '\n';
          }
	output << '\n';
      }

    return;
  }


///
///  @brief  Difference two one-argument functions.
///
template<typename Tp, typename Tp1>
  void
  rundiff(Tp function1(Tp1),
          Tp function2(Tp1),
          const std::string & basename, const std::string & arg1,
          const std::vector<Tp1> & argument1,
          bool verbose = false)
  {
    using Val = num_traits_t<Tp>;

    std::string filename = diffdirname + basename + filename_end<Tp>::suffix();

    std::ofstream output(filename);
    output.precision(std::numeric_limits<Val>::digits10);
    output.flags(std::ios::showpoint);
    const auto w_real = 8 + output.precision();
    const auto w_cmplx = 2 + 2 * w_real;
    const auto w_arg1 = (is_complex_v<Tp1> ? w_cmplx : w_real);
    const auto w_ret = (is_complex_v<Tp> ? w_cmplx : w_real);

    output << std::setw(w_arg1) << arg1;
    output << std::setw(w_ret) << "f1";
    output << std::setw(w_ret) << "f2";
    output << std::setw(w_ret) << "delta";
    output << std::setw(w_ret) << "frac";
    output << '\n';

    auto max_abs_diff = Val{-1};
    auto max_abs_frac = Val{-1};
    for (unsigned int i = 0; i < argument1.size(); ++i)
      {
	auto x = argument1[i];

	try
          {
            auto f1 = function1(x);
            auto f2 = function2(x);
            auto diff = f1 - f2;
            if (std::abs(diff) > max_abs_diff)
              max_abs_diff = std::abs(diff);
            output << std::setw(w_arg1) << x;
            output << std::setw(w_ret) << f1;
            output << std::setw(w_ret) << f2;
            output << std::setw(w_ret) << diff;
            if (std::abs(f2) > 0)
              {
        	auto frac = diff / f2;
        	output << std::setw(w_ret) << frac;
        	if (std::abs(frac) > max_abs_frac)
                  max_abs_frac = std::abs(frac);
              }
            else
              output << std::setw(w_ret) << '-';
            output << '\n';
          }
	catch (std::domain_error & err)
          {
            if (verbose)
              output << '\n' << err.what() << '\n';
            continue;
          }
	catch (std::runtime_error & err)
          {
            if (verbose)
              output << '\n' << err.what() << '\n';
            continue;
          }
	catch (...)
          {
            output << "\n*Unknown Error*\n";
            continue;
          }
      }
    if (max_abs_diff >= Val(0))
      output << "max(abs(diff)) = " << std::setw(w_real) << max_abs_diff << '\n';
    else
      output << "max(abs(diff)) = " << std::setw(w_real) << '-' << '\n';
    if (max_abs_frac >= Val(0))
      output << "max(abs(frac)) = " << std::setw(w_real) << max_abs_frac << '\n';
    else
      output << "max(abs(frac)) = " << std::setw(w_real) << '-' << '\n';

    return;
  }


///
///  @brief  Difference two two-argument functions.
///
template<typename Tp, typename Tp1, typename Tp2>
  void
  rundiff(Tp function1(Tp1, Tp2),
          Tp function2(Tp1, Tp2),
          const std::string & basename,
          const std::string & arg1, const std::vector<Tp1> & argument1,
          const std::string & arg2, const std::vector<Tp2> & argument2,
          bool verbose = false)
  {
    using Val = num_traits_t<Tp>;

    std::string filename = diffdirname + basename + filename_end<Tp>::suffix();
std::cerr << filename << '\n';

    std::ofstream output(filename);
    output.precision(std::numeric_limits<Val>::digits10);
    output.flags(std::ios::showpoint);
    const auto w_real = 8 + output.precision();
    const auto w_cmplx = 2 + 2 * w_real;
    const auto w_arg1 = (is_complex_v<Tp1> ? w_cmplx : w_real);
    const auto w_arg2 = (is_complex_v<Tp2> ? w_cmplx : w_real);
    const auto w_ret = (is_complex_v<Tp> ? w_cmplx : w_real);

    for (unsigned int i = 0; i < argument1.size(); ++i)
      {
	auto x = argument1[i];
	output << "  " << arg1 << " = " << std::setw(w_arg1) << x << '\n';

	output << std::setw(w_arg2) << arg2;
	output << std::setw(w_ret) << "f1";
	output << std::setw(w_ret) << "f2";
	output << std::setw(w_ret) << "delta";
	output << std::setw(w_ret) << "frac";
	output << '\n';

	auto max_abs_diff = Val{-1};
	auto max_abs_frac = Val{-1};
	for (unsigned int j = 0; j < argument2.size(); ++j)
          {
            auto y = argument2[j];

            try
              {
        	auto f1 = function1(x, y);
        	auto f2 = function2(x, y);
        	auto diff = f1 - f2;
        	if (std::abs(diff) > max_abs_diff)
                  max_abs_diff = std::abs(diff);
        	output << std::setw(w_arg2) << y;
        	output << std::setw(w_ret) << f1;
        	output << std::setw(w_ret) << f2;
        	output << std::setw(w_ret) << diff;
        	if (std::abs(f2) > 0)
                  {
                    auto frac = diff / f2;
                    output << std::setw(w_ret) << frac;
                    if (std::abs(frac) > max_abs_frac)
                      max_abs_frac = std::abs(frac);
                  }
        	else
                  output << std::setw(w_ret) << '-';
        	output << '\n';
              }
            catch (std::domain_error & err)
              {
        	if (verbose)
                  output << '\n' << err.what() << '\n';
        	continue;
              }
            catch (std::runtime_error & err)
              {
        	if (verbose)
                  output << '\n' << err.what() << '\n';
        	continue;
              }
	    catch (...)
              {
        	output << "\n*Unknown Error*\n";
        	continue;
              }
          }
	if (max_abs_diff >= Val(0))
          output << "max(abs(diff)) = " << std::setw(w_real) << max_abs_diff << '\n';
	else
          output << "max(abs(diff)) = " << std::setw(w_real) << '-' << '\n';
	if (max_abs_frac >= Val(0))
          output << "max(abs(frac)) = " << std::setw(w_real) << max_abs_frac << '\n';
	else
          output << "max(abs(frac)) = " << std::setw(w_real) << '-' << '\n';
	output << '\n';
      }

    return;
  }


///
///  @brief  Difference two three-argument functions.
///
template<typename Tp, typename Tp1, typename Tp2, typename Tp3>
  void
  rundiff(Tp function1(Tp1, Tp2, Tp3),
          Tp function2(Tp1, Tp2, Tp3),
          const std::string & basename,
          const std::string & arg1, const std::vector<Tp1> & argument1,
          const std::string & arg2, const std::vector<Tp2> & argument2,
          const std::string & arg3, const std::vector<Tp3> & argument3,
          bool verbose = false)
  {
    using Val = num_traits_t<Tp>;

    std::string filename = diffdirname + basename + filename_end<Tp>::suffix();

    std::ofstream output(filename);
    output.precision(std::numeric_limits<Val>::digits10);
    output.flags(std::ios::showpoint);
    const auto w_real = 8 + output.precision();
    const auto w_cmplx = 2 + 2 * w_real;
    const auto w_arg1 = (is_complex_v<Tp1> ? w_cmplx : w_real);
    const auto w_arg2 = (is_complex_v<Tp2> ? w_cmplx : w_real);
    const auto w_arg3 = (is_complex_v<Tp3> ? w_cmplx : w_real);
    const auto w_ret = (is_complex_v<Tp> ? w_cmplx : w_real);

    for (unsigned int i = 0; i < argument1.size(); ++i)
      {
	auto x = argument1[i];
	output << "  " << arg1 << " = " << std::setw(w_arg1) << x << '\n';

	for (unsigned int j = 0; j < argument2.size(); ++j)
          {
            auto y = argument2[j];
            output << "  " << arg2 << " = " << std::setw(w_arg2) << y << '\n';

            output << std::setw(w_arg3) << arg3;
            output << std::setw(w_ret) << "f1";
            output << std::setw(w_ret) << "f2";
            output << std::setw(w_ret) << "delta";
            output << std::setw(w_ret) << "frac";
            output << '\n';

	    auto max_abs_diff = Val{-1};
	    auto max_abs_frac = Val{-1};
            for (unsigned int k = 0; k < argument3.size(); ++k)
              {
        	auto z = argument3[k];

        	try
                  {
                    auto f1 = function1(x, y, z);
                    auto f2 = function2(x, y, z);
                    auto diff = f1 - f2;
                    if (std::abs(diff) > max_abs_diff)
                      max_abs_diff = std::abs(diff);
                    output << std::setw(w_arg3) << z;
                    output << std::setw(w_ret) << f1;
                    output << std::setw(w_ret) << f2;
                    output << std::setw(w_ret) << diff;
                    if (std::abs(f2) > 0)
                      {
                	auto frac = diff / f2;
                	output << std::setw(w_ret) << frac;
                	if (std::abs(frac) > max_abs_frac)
                          max_abs_frac = std::abs(frac);
                      }
                    else
                      output << std::setw(w_ret) << '-';
                    output << '\n';
                  }
        	catch (std::domain_error & err)
                  {
                    if (verbose)
                      output << '\n' << err.what() << '\n';
                    continue;
                  }
        	catch (std::runtime_error & err)
                  {
                    if (verbose)
                      output << '\n' << err.what() << '\n';
                    continue;
                  }
		catch (...)
        	  {
        	    output << "\n*Unknown Error*\n";
        	    continue;
        	  }
              }
            if (max_abs_diff >= Val(0))
              output << "max(abs(diff)) = " << std::setw(w_real) << max_abs_diff << '\n';
            else
              output << "max(abs(diff)) = " << std::setw(w_real) << '-' << '\n';
            if (max_abs_frac >= Val(0))
              output << "max(abs(frac)) = " << std::setw(w_real) << max_abs_frac << '\n';
            else
              output << "max(abs(frac)) = " << std::setw(w_real) << '-' << '\n';
            output << '\n';
          }
	output << '\n';
      }

    return;
  }


///
///  @brief  Difference two four-argument functions.
///
template<typename Tp, typename Tp1, typename Tp2, typename Tp3, typename Tp4>
  void
  rundiff(Tp function1(Tp1, Tp2, Tp3, Tp4),
          Tp function2(Tp1, Tp2, Tp3, Tp4),
          const std::string & basename,
          const std::string & arg1, const std::vector<Tp1> & argument1,
          const std::string & arg2, const std::vector<Tp2> & argument2,
          const std::string & arg3, const std::vector<Tp3> & argument3,
          const std::string & arg4, const std::vector<Tp4> & argument4,
          bool verbose = false)
  {
    using Val = num_traits_t<Tp>;

    std::string filename = diffdirname + basename + filename_end<Tp>::suffix();

    std::ofstream output(filename);
    output.precision(std::numeric_limits<Val>::digits10);
    output.flags(std::ios::showpoint);
    const auto w_real = 8 + output.precision();
    const auto w_cmplx = 2 + 2 * w_real;
    const auto w_arg1 = (is_complex_v<Tp1> ? w_cmplx : w_real);
    const auto w_arg2 = (is_complex_v<Tp2> ? w_cmplx : w_real);
    const auto w_arg3 = (is_complex_v<Tp3> ? w_cmplx : w_real);
    const auto w_arg4 = (is_complex_v<Tp4> ? w_cmplx : w_real);
    const auto w_ret = (is_complex_v<Tp> ? w_cmplx : w_real);

    for (unsigned int i = 0; i < argument1.size(); ++i)
      {
	auto w = argument1[i];
	output << "  " << arg1 << " = " << std::setw(w_arg1) << w << '\n';

	for (unsigned int j = 0; j < argument2.size(); ++j)
          {
            auto x = argument2[j];
            output << "  " << arg2 << " = " << std::setw(w_arg2) << x << '\n';

            for (unsigned int k = 0; k < argument3.size(); ++k)
              {
        	auto y = argument3[k];
        	output << "  " << arg3 << " = " << std::setw(w_arg3) << y << '\n';

        	output << std::setw(w_arg3) << arg4;
        	output << std::setw(w_ret) << "f1";
        	output << std::setw(w_ret) << "f2";
        	output << std::setw(w_ret) << "delta";
        	output << std::setw(w_ret) << "frac";
        	output << '\n';

		auto max_abs_diff = Val{-1};
		auto max_abs_frac = Val{-1};
        	for (unsigned int l = 0; l < argument4.size(); ++l)
                  {
                    auto z = argument4[l];

                    try
                      {
                	auto f1 = function1(w, x, y, z);
                	auto f2 = function2(w, x, y, z);
                	auto diff = f1 - f2;
                	if (std::abs(diff) > max_abs_diff)
                          max_abs_diff = std::abs(diff);
                	output << std::setw(w_arg4) << z;
                	output << std::setw(w_ret) << f1;
                	output << std::setw(w_ret) << f2;
                	output << std::setw(w_ret) << diff;
                	if (std::abs(f2) > 0)
                          {
                            auto frac = diff / f2;
                            output << std::setw(w_ret) << frac;
                            if (std::abs(frac) > max_abs_frac)
                              max_abs_frac = std::abs(frac);
                          }
                	else
                          output << std::setw(w_ret) << '-';
                	output << '\n';
                      }
                    catch (std::domain_error & err)
                      {
                	if (verbose)
                          output << '\n' << err.what() << '\n';
                	continue;
                      }
                    catch (std::runtime_error & err)
                      {
                	if (verbose)
                          output << '\n' << err.what() << '\n';
                	continue;
                      }
		    catch (...)
        	      {
        		output << "\n*Unknown Error*\n";
        		continue;
        	      }
                  }
        	if (max_abs_diff >= Val(0))
                  output << "max(abs(diff)) = " << std::setw(w_real) << max_abs_diff << '\n';
        	else
                  output << "max(abs(diff)) = " << std::setw(w_real) << '-' << '\n';
        	if (max_abs_frac >= Val(0))
                  output << "max(abs(frac)) = " << std::setw(w_real) << max_abs_frac << '\n';
        	else
                  output << "max(abs(frac)) = " << std::setw(w_real) << '-' << '\n';
        	output << '\n';
              }
            output << '\n';
          }
	output << '\n';
      }

    return;
  }

#endif // TEST_FUNC_TCC
