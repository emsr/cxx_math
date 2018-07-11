/*
$HOME/bin_tr29124/bin/g++ -std=gnu++17 -g -Wall -Wextra -Wno-psabi -I. -o test_summation test_summation.cpp -lquadmath
./test_summation > test_summation.txt

$HOME/bin/bin/g++ -std=gnu++17 -I. -o test_summation test_summation.cpp -lquadmath
./test_summation > test_summation.txt
*/

#include <cmath>
#include <cstdlib>
#include <vector>
#include <limits>

#include <iostream>
#include <iomanip>

#include <bits/float128_io.h>
#include <bits/summation.h>

template<typename Tp>
  void
  test(Tp proto = Tp{})
  {
    const auto _S_max_log = __gnu_cxx::__log_max(proto);

    using ABS_t = __gnu_cxx::_AitkenDeltaSquaredSum<__gnu_cxx::_BasicSum<Tp>>;
    using ShankS_t = __gnu_cxx::_AitkenDeltaSquaredSum<ABS_t>;

    std::cout.precision(__gnu_cxx::__digits10(proto));
    auto w = 8 + std::cout.precision();
    __gnu_cxx::_BasicSum<Tp> BS;
    __gnu_cxx::_AitkenDeltaSquaredSum<__gnu_cxx::_BasicSum<Tp>> ABS;
    __gnu_cxx::_AitkenDeltaSquaredSum<__gnu_cxx::_KahanSum<Tp>> AKS;
    ShankS_t ShankS;
    __gnu_cxx::_WinnEpsilonSum<__gnu_cxx::_BasicSum<Tp>> WBS;
    __gnu_cxx::_WinnEpsilonSum<__gnu_cxx::_KahanSum<Tp>> WKS;
    __gnu_cxx::_BrezinskiThetaSum<__gnu_cxx::_BasicSum<Tp>> BTS;

    //__gnu_cxx::_LevinUSum<__gnu_cxx::_BasicSum<Tp>> LUS;
    __gnu_cxx::_LevinTSum<__gnu_cxx::_BasicSum<Tp>> LTS;
    __gnu_cxx::_LevinDSum<__gnu_cxx::_BasicSum<Tp>> LDS;
    __gnu_cxx::_LevinVSum<__gnu_cxx::_BasicSum<Tp>> LVS;

    __gnu_cxx::_WenigerTauSum<__gnu_cxx::_BasicSum<Tp>> WTS;
    __gnu_cxx::_WenigerDeltaSum<__gnu_cxx::_BasicSum<Tp>> WDS;
    __gnu_cxx::_WenigerPhiSum<__gnu_cxx::_BasicSum<Tp>> WPS;
    __gnu_cxx::_WenigerDeltaSum<__gnu_cxx::_VanWijngaardenSum<Tp>> WDvW; // Start terma: (8)

    auto s = Tp{1.2};
    auto zetaterm = [s, _S_max_log](std::size_t k)
		    -> Tp
		    { return (s * std::log(Tp(k + 1)) < _S_max_log ? std::pow(Tp(k + 1), -s) : Tp{0}); };

    auto VwT = __gnu_cxx::_VanWijngaardenCompressor<decltype(zetaterm)>(zetaterm);

    auto zeta = Tp{5.591582441177750776536563193423143277642L};
    std::cout << "\n\nzeta(1.2) = " << std::setw(w) << zeta << '\n';
    std::cout << std::setw(w) << "k"
	      << std::setw(w) << "Basic"
	      << std::setw(w) << "Aitken-Basic"
	      << std::setw(w) << "Aitken-Kahan"
	      << std::setw(w) << "Winn-Basic"
	      << std::setw(w) << "Winn-Kahan"
	      << std::setw(w) << "BrezinskiT-Basic"
	      << std::setw(w) << "LevinT-Basic"
	      << std::setw(w) << "LevinD-Basic"
	      << std::setw(w) << "LevinV-Basic"
	      << std::setw(w) << "WenigerTau-Basic"
	      << std::setw(w) << "WenigerDelta-Basic"
	      << std::setw(w) << "WenigerPhi-Basic"
	      << std::setw(w) << "WenigerD-vW"
	      << std::setw(w) << "Shanks"
	      << '\n';
    std::cout << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << '\n';
    for (auto k = 0; k < 100; ++k)
      {
	auto term = std::pow(Tp(k + 1), -s);
	BS += term;
	ABS += term;
	AKS += term;
	WBS += term;
	WKS += term;
	BTS += term;
	LTS += term;
	LDS += term;
	LVS += term;
	WTS += term;
	WDS += term;
	WPS += term;
	WDvW += VwT[k];
	ShankS += term;
	std::cout << std::setw(w) << k
		  << std::setw(w) << BS()
		  << std::setw(w) << ABS()
		  << std::setw(w) << AKS()
		  << std::setw(w) << WBS()
		  << std::setw(w) << WKS()
		  << std::setw(w) << BTS()
	  	  << std::setw(w) << LTS()
	  	  << std::setw(w) << LDS()
	  	  << std::setw(w) << LVS()
	  	  << std::setw(w) << WTS()
	  	  << std::setw(w) << WDS()
	  	  << std::setw(w) << WPS()
	  	  << std::setw(w) << WDvW()
		  << std::setw(w) << ShankS()
		  << '\n';
      }

    // 2F0(1,1;;-1/3)
    std::cout << "\n\n2F0(1,1;;-1/3) = 0.78625122076596\n";
    auto a = Tp{1};
    auto b = Tp{1};
    auto z = Tp{-1} / Tp{3};
    auto term = Tp{1};
    BS.reset(term);
    ABS.reset(term);
    AKS.reset(term);
    WBS.reset(term);
    WKS.reset(term);
    BTS.reset(term);
    LTS.reset(term);
    LDS.reset(term);
    LVS.reset(term);
    WTS.reset(term);
    WDS.reset(term);
    WPS.reset(term);
    ShankS.reset(term);
    std::cout << std::setw(w) << "k"
	      << std::setw(w) << "Basic"
	      << std::setw(w) << "Aitken-Basic"
	      << std::setw(w) << "Aitken-Kahan"
	      << std::setw(w) << "Winn-Basic"
	      << std::setw(w) << "Winn-Kahan"
	      << std::setw(w) << "BrezinskiT-Basic"
	      << std::setw(w) << "LevinT-Basic"
	      << std::setw(w) << "LevinD-Basic"
	      << std::setw(w) << "LevinV-Basic"
	      << std::setw(w) << "WenigerTau-Basic"
	      << std::setw(w) << "WenigerDelta-Basic"
	      << std::setw(w) << "WenigerPhi-Basic"
	      << std::setw(w) << "Shanks"
	      << '\n';
    std::cout << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << std::setw(w) << "------------------"
	      << '\n';
    for (auto k = 1; k < 100; ++k)
      {
	std::cout << std::setw(w) << (k - 1)
		  << std::setw(w) << BS()
		  << std::setw(w) << ABS()
		  << std::setw(w) << AKS()
		  << std::setw(w) << WBS()
		  << std::setw(w) << WKS()
		  << std::setw(w) << BTS()
		  << std::setw(w) << LTS()
		  << std::setw(w) << LDS()
		  << std::setw(w) << LVS()
		  << std::setw(w) << WTS()
		  << std::setw(w) << WDS()
		  << std::setw(w) << WPS()
		  << std::setw(w) << ShankS()
		  << '\n';
	term *= (a + k - 1) * (b + k - 1) * z / k;
	BS += term;
	ABS += term;
	AKS += term;
	WBS += term;
	WKS += term;
	BTS += term;
	LTS += term;
	LDS += term;
	LVS += term;
	WTS += term;
	WDS += term;
	WPS += term;
	ShankS += term;
      }
  }


int
main()
{
  //std::cout << "\nfloat\n=====\n\n";
  //test<float>();

  std::cout << "\ndouble\n======\n";
  test<double>();

  std::cout << "\nlong double\n===========\n";
  test<long double>();

  std::cout << "\n__float128\n===========\n";
  test<__float128>();
}
