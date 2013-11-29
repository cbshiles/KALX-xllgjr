// function.h - std::function<OPERX(OPERX)>
#pragma once
#include <functional>
#include "../xll8/xll/xll.h"

namespace xll {

	class function {
		std::function<OPERX(const OPERX&)> f_;
	public:
		function()
		{ }
		function(const std::function<OPERX(const OPERX&)>& f)
			: f_(f)
		{ }
		function(const function& f)
			: f_(f.f_)
		{ }
		function& operator=(const function& f)
		{
			if (this != &f)
				f_ = f.f_;

			return *this;
		}
		~function()
		{ }

		OPERX operator()(const OPERX& x) const
		{
			return f_(x);
		}
		function compose(const function& g) const
		{
			return function([this,&g](const OPERX& x) { return this->f_(g(x)); });
		}
	};

} // xll

namespace detail {
	template<class Op>
	inline xll::function operator_op(Op op, const xll::function& f, const xll::function& g)
	{
		return xll::function([&op, &f,&g](const OPERX& x) { return OPERX(op(f(x).val.num, g(x).val.num)); });
	}
}

#define OPERATOR_OP(op,fun) \
inline xll::function operator op (const xll::function& f, const xll::function& g) \
	{ return detail::operator_op(fun<double>(), f, g); }

OPERATOR_OP(+, std::plus)
OPERATOR_OP(-, std::minus)
OPERATOR_OP(*, std::multiplies)
OPERATOR_OP(/, std::divides)

#undef OPERATOR_OP

