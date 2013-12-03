// xllroot.cpp - find roots of functions
#include "../xll8/xll/xll.h"
#include "../fmsgjr/root1d.h"

using namespace xll;
using namespace fms;

typedef traits<XLOPERX>::xfp xfp;
typedef traits<XLOPERX>::xword xword;

static AddInX xai_root1d_state(
	FunctionX(XLL_HANDLEX, _T("?xll_root1d_state"), _T("XLL.ROOT1D"))
	.Arg(XLL_DOUBLEX, _T("Abs"), _T("is the absolute error."))
	.Arg(XLL_DOUBLEX, _T("Rel"), _T("is the relative error."))
	.Arg(XLL_USHORT, _T("Iter"), _T("is the maximum number of iterations."))
	.Uncalced()
	.Category(_T("XLL"))
	.FunctionHelp(_T("Return a handle to a one dimensional root finder state."))
);
HANDLEX WINAPI xll_root1d_state(double abs, double rel, USHORT iter)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<root1d::state<>> h_(new root1d::state<>(abs, rel, iter));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_root1d_state_x(
	FunctionX(XLL_FPX, _T("?xll_root1d_state_x"), _T("XLL.ROOT1D.X"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is a handle returned by XLL.ROOT1D"))
	.Category(_T("XLL"))
	.FunctionHelp(_T("Return root guesses."))
);
xfp* WINAPI xll_root1d_state_x(HANDLEX h)
{
#pragma XLLEXPORT
	static FPX x;

	try {
		handle<root1d::state<>> h_(h);

		x.resize(static_cast<xword>(h_->x.size()), 1);
		std::copy(h_->x.begin(), h_->x.end(), x.begin());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return x.get();
}
static AddInX xai_root1d_state_y(
	FunctionX(XLL_FPX, _T("?xll_root1d_state_y"), _T("XLL.ROOT1D.Y"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is a handle returned by XLL.ROOT1D"))
	.Category(_T("XLL"))
	.FunctionHelp(_T("Return residuals."))
);
xfp* WINAPI xll_root1d_state_y(HANDLEX h)
{
#pragma XLLEXPORT
	static FPX y;

	try {
		handle<root1d::state<>> h_(h);

		y.resize(static_cast<xword>(h_->x.size()), 1);
		std::copy(h_->y.begin(), h_->y.end(), y.begin());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return y.get();
}

static AddInX xai_root1d_state_test_interval(
	FunctionX(XLL_BOOLX, _T("?xll_root1d_state_test_interval"), _T("XLL.ROOT1D.TEST.INTERVAL"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is a handle returned by XLL.ROOT1D"))
	.Category(_T("XLL"))
	.FunctionHelp(_T("Test if root is in tolerance interval."))
);
BOOL WINAPI xll_root1d_state_test_interval(HANDLEX h)
{
#pragma XLLEXPORT
	BOOL b(false);

	try {
		handle<root1d::state<>> h_(h);

		b = h_->test_inverval();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return b;
}

	inline std::function<double(double)> wrap(const std::function<LOPERX(const LPOPERX*)>& f)
	{
		return [f](double x) { OPERX x_(x); LPOPERX px(&x_); LOPERX y = f(&px); return y.val.num; };
	}

static AddInX xai_root1d_state_bracket(
	FunctionX(XLL_DOUBLEX, _T("?xll_root1d_state_bracket"), _T("XLL.ROOT1D.BRACKET"))
	.Arg(XLL_HANDLEX, _T("state"), _T("is a handle returned by XLL.ROOT1D"))
	.Arg(XLL_HANDLEX, _T("f"), _T("is a handle to a function."))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is the initial value to use."))
	.Uncalced()
	.Category(_T("XLL"))
	.FunctionHelp(_T("Bracket the root of a monotonic function with argument _1."))
);
HANDLEX WINAPI xll_root1d_state_bracket(HANDLEX h, HANDLEX f, double x0)
{
#pragma XLLEXPORT
	try {
		handle<root1d::state<>> h_(h);
		handle<std::function<LOPERX(const LPOPERX*)>> f_(f);

		auto F = wrap(*f_);
		h_->bracket(F, x0);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		h = handlex();
	}

	return h;
}
