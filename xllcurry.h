// curry.h - curry Excel functions
#pragma once
#include "../xll8/xll/xll.h"

namespace xll {
	
	class Curry {
		typedef traits<XLOPERX>::xfp xfp;
		typedef traits<XLOPERX>::xword xword;

		OPERX arg;
	public:
		Curry()
		{ }
		Curry(double regid, LPOPERX* ppa)
		{
			const XAddIn<XLOPERX>* pai = XAddIn<XLOPERX>::Find(regid);
			ensure (pai);
			arg.resize(pai->Args().Arity() + 1, 1);
			arg[0] = regid;
			for (xword i = 1; i < arg.size(); ++i, ++ppa) {
				arg[i] = *(*ppa); // peel args of the call stack
			}
		}
		Curry(const Curry& c) = default;
		Curry& operator=(const Curry&c ) = default;
		~Curry()
		{ }

		OPERX operator()(const LPOPERX* ppa)
		{
			OPERX a_(arg);

			// fill in missing args
			for (xword j = 1; j < arg.size(); ++j) {
				if (a_[j].xltype == xltypeMissing) {
					a_[j] = *(*ppa);
					++ppa;
				}
			}
			std::vector<LPXLOPER> parg(a_.size());
			for (xword i = 0; i < parg.size(); ++i)
				parg[i] = &a_[i];

			LOPERX ret;
			ensure (xlretSuccess == xll::traits<XLOPERX>::Excelv(xlUDF, &ret, parg.size(), &parg[0]));

			return ret;
		}
	};

} // xll