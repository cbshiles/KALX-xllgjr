// xllmodel.cpp
#include "xllgjr.h"

using namespace fms;
using namespace xll;

static AddInX xai_fms_model_black(
	FunctionX(XLL_HANDLEX, _T("?xll_fms_model_black"), _T("MODEL.BLACK"))
	.Arg(XLL_DOUBLEX, _T("Forward"), _T("is the forward."))
	.Arg(XLL_DOUBLEX, _T("Volatility"), _T("is the volatility."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a Black model."))
);
HANDLEX xll_fms_model_black(double f, double s)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<model::black<>> b(new model::black<>(f, s));

		h = b.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_fms_model_black_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_fms_model_black_value"), _T("MODEL.BLACK.VALUE"))
	.Arg(XLL_DOUBLEX, _T("Forward"), _T("is the forward value of the underlying."))
	.Arg(XLL_DOUBLEX, _T("Volatility"), _T("is the Black-Scholes volatility of the underlying."))
	.Arg(XLL_DOUBLEX, _T("Strike"), _T("is the strike of the option."))
	.Arg(XLL_DOUBLEX, _T("Expiration"), _T("is the time in years to option expiration."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Values a call (Strike > 0) or put (Strike < 0) using the Fischer Black model."))
	.Documentation(R"(
		This can also be called with two arguments, a model and an instrument.
		E.g., <codeInline>BLACK.VALUE(100, 0.2, 90, 0.25) = BLACK.VALUE(BLACK(100, 0.2), OPTION(90, 0.25)</codeInline>
	)")
);
double WINAPI xll_fms_model_black_value(double f, double s, double k, double t)
{
#pragma XLLEXPORT
	double v(std::numeric_limits<double>::quiet_NaN());

	try {
		if (k == 0 && t == 0) {
			handle<model::black<>> m(f);
			handle<instrument::option<>> o(s);

			v = value<>(*m, *o);
		}
		else {
			v = value<>(model::black<>(f,s), instrument::option<>(k,t));
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	
	return v;
}

static AddInX xai_fms_model_gjr(
	FunctionX(XLL_HANDLEX, _T("?xll_fms_model_gjr"), _T("MODEL.GJR"))
	.Arg(XLL_DOUBLEX, _T("Forward"), _T("is the forward."))
	.Arg(XLL_DOUBLEX, _T("Volatility"), _T("is the volatility."))
	.Arg(XLL_FPX, _T("kappa"), _T("is an array of cumulants."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a generalized Jarrow-Rudd model."))
);
HANDLEX xll_fms_model_gjr(double f, double s, const _FP* pk)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<model::gjr<>> gjr(new model::gjr<>(f, s, pk->rows*pk->columns, pk->array));

		h = gjr.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
static AddInX xai_fms_model_gjr_value(
	FunctionX(XLL_DOUBLEX, _T("?xll_fms_model_gjr_value"), _T("MODEL.GJR.VALUE"))
	.Arg(XLL_DOUBLEX, _T("Forward"), _T("is the forward value of the underlying."), 100)
	.Arg(XLL_DOUBLEX, _T("Volatility"), _T("is the Black-Scholes volatility of the underlying."), 0.2)
	.Arg(XLL_FPX, _T("Kappa"),  _T("is optional array of cumulant perturbations."), _T("{0,0,0,0}"))
	.Arg(XLL_DOUBLEX, _T("Strike"), _T("is the strike of the option."), 100)
	.Arg(XLL_DOUBLEX, _T("Expiration"), _T("is the time in years to option expiration."), 0.25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Values a call (Strike > 0) or put (Strike < 0) using the generalized Jarrow-Rudd model."))
	.Documentation(R"xyz(
		This can also be called with two arguments, a model and an instrument.
		E.g., <codeInline>BLACK.VALUE(100, 0.2, 90, 0.25) = BLACK.VALUE(BLACK(100, 0.2), OPTION(90, 0.25))</codeInline>
	)xyz")
);
double WINAPI xll_fms_model_gjr_value(double f, double s, const xfp* pkappa, double k, double t)
{
#pragma XLLEXPORT
	double v(std::numeric_limits<double>::quiet_NaN());

	try {
		if (size(*pkappa) == 1 && pkappa->array[0] == 0) {
			handle<model::gjr<>> m(f);
			handle<instrument::option<>> o(s);

			v = value<>(*m, *o);
		}
		else {
			v = value<>(model::gjr<>(f, s, size(*pkappa), pkappa->array), instrument::option<>(k, t));
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	
	return v;
}

