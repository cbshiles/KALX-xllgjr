// xllinstrument.cpp
#include "xllgjr.h"

using namespace fms;
using namespace xll;

static AddInX xai_fms_instrument_option(
	FunctionX(XLL_HANDLEX, _T("?xll_fms_instrument_option"), _T("INSTRUMENT.OPTION"))
	.Arg(XLL_DOUBLEX, _T("Strike"), _T("is the strike price of the call or put option."))
	.Arg(XLL_DOUBLEX, _T("Expiration"), _T("is the time in years to option expiration."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a call (Strike > 0) or put (Strike < 0) option."))
);
HANDLEX xll_fms_instrument_option(double k, double t)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<instrument::option<>> h_(new instrument::option<>(k, t));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
static AddInX xai_fms_instrument_call(
	FunctionX(XLL_HANDLEX, _T("?xll_fms_instrument_call"), _T("INSTRUMENT.CALL"))
	.Arg(XLL_DOUBLEX, _T("Strike"), _T("is the strike price of the call."))
	.Arg(XLL_DOUBLEX, _T("Expiration"), _T("is the time in years to call expiration."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a call option."))
);
HANDLEX xll_fms_instrument_call(double k, double t)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<instrument::option<>> h_(new instrument::call<>(k, t));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
static AddInX xai_fms_instrument_put(
	FunctionX(XLL_HANDLEX, _T("?xll_fms_instrument_put"), _T("INSTRUMENT.PUT"))
	.Arg(XLL_DOUBLEX, _T("Strike"), _T("is the strike price of the put."))
	.Arg(XLL_DOUBLEX, _T("Expiration"), _T("is the time in years to put expiration."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a put option."))
);
HANDLEX xll_fms_instrument_put(double k, double t)
{
#pragma XLLEXPORT
	handlex h;

	try {
		handle<instrument::option<>> h_(new instrument::put<>(k, t));

		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
