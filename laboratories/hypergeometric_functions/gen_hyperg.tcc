
template<typename _Tp>
  _Pochhammer
  {
  public:
    _Pochhammer();
    _Pochhammer(_Tp __a);
  private:
    static constexpr _Tp _S_max = std::numeric_limits<_Tp>::max();
    _Tp _M_term;
    _Tp _M_max_term = _S_max;
    _Tp _M_product = _Tp{1};
    _Tp _M_abs_log_product = _Tp{0};
    _Tp _M_sign_log_product = _Tp{1};
  };

template<typename _Tp, unsigned int _P, unsigned int _Q>
  Tp
  hyperg(std::array<_Tp, _P> __a, std::array<_Tp, _Q> __c, _Tp __z)
  {
    cancel_params(__a, __c);
    if (__z == _Tp{0})
      return _Tp{1};
    else if (neg_integer_nearest_0(__a) < 0)
      {}
    else if (__a.size() <= __c.size())
      {
	std::array<_Pochhammer<_Tp>, _P> __a_n;
	for (unsigned int __k = 0; __k < __P; ++__k)
	  __a_n = __a[__k];

	std::array<_Pochhammer<_Tp>, _Q> __c_n;
	for (unsigned int __k = 0; __k < _Q; ++__k)
	  __c_n = __c[__k];
      }
  }
