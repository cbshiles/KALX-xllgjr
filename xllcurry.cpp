// xllcurry.cpp - curry Excel functions
// f = CURRY(FUNCTION, Arg1, , ...)
// CURRY.CALL(f, Arg2, ...) -> FUNCTION(Arg1, Arg2, ...)
#include "xllcurry.h"

using namespace xll;

// curry up to 8 arguments
static AddInX xai_curry(
	FunctionX(XLL_HANDLEX, _T("?xll_curry"), _T("CURRY"))
	.Arg(XLL_DOUBLEX, _T("RegId"), _T("is the register id of a user defined function."))
	.Arg(XLL_LPOPERX, _T("Args"), _T("is an argument to curry if not missing."))
	.Arg(XLL_LPOPERX, _T("Args"), _T("is an argument to curry if not missing."))
	.Arg(XLL_LPOPERX, _T("Args"), _T("is an argument to curry if not missing."))
	.Arg(XLL_LPOPERX, _T("Args"), _T("is an argument to curry if not missing."))
	.Arg(XLL_LPOPERX, _T("Args"), _T("is an argument to curry if not missing."))
	.Arg(XLL_LPOPERX, _T("Args"), _T("is an argument to curry if not missing."))
	.Arg(XLL_LPOPERX, _T("Args"), _T("is an argument to curry if not missing."))
	.Arg(XLL_LPOPERX, _T("Args"), _T("is an argument to curry if not missing."))
	.Uncalced()
	.Category(_T("XLL"))
	.FunctionHelp(_T("Omit arguments values to curry."))
);
HANDLEX WINAPI xll_curry(double regid, LPOPERX pa) // ...
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<Curry> h_(new Curry(regid, &pa));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
static AddInX xai_curry_call(
	FunctionX(XLL_LPOPERX, _T("?xll_curry_call"), _T("CURRY.CALL"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is a handle returned by CURRY."))
	.Arg(XLL_LPOPERX, _T("Arg"), _T("is an argument that was not curried."))
	.Arg(XLL_LPOPERX, _T("Arg"), _T("is an argument that was not curried."))
	.Arg(XLL_LPOPERX, _T("Arg"), _T("is an argument that was not curried."))
	.Arg(XLL_LPOPERX, _T("Arg"), _T("is an argument that was not curried."))
	.Arg(XLL_LPOPERX, _T("Arg"), _T("is an argument that was not curried."))
	.Arg(XLL_LPOPERX, _T("Arg"), _T("is an argument that was not curried."))
	.Arg(XLL_LPOPERX, _T("Arg"), _T("is an argument that was not curried."))
	.Arg(XLL_LPOPERX, _T("Arg"), _T("is an argument that was not curried."))
	.Category(_T("XLL"))
	.FunctionHelp(_T("Supply arguments that have not been curried."))
);
LPOPERX WINAPI xll_curry_call(HANDLEX h, LPOPERX pa) // ...
{
#pragma XLLEXPORT
	static OPERX y;

	try {
		handle<Curry> h_(h);

		y = h_->operator()(&pa);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return &y;
}
