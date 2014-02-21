// black.cpp - Fischer Black model that uses forwards and no rates.
// Copyright (c)2006 KALX, LLC. All rights reserved. No warranty is made.
#include "../xll8/xll/xll.h"
#include "../fmsgjr/black.h"

#define CATEGORY _T("XLL")
#define PREFIX //CATEGORY _T(".")

#define IS_FORWARD _T("is the forward value of the underlying.")
#define IS_VOLATILITY _T("is the volatility of the underlying.")
#define IS_STRIKE _T("is the strike of the underlying option.")
#define IS_EXPIRATION _T("is the time in years to option expiration.")
#define IS_VALUE _T("is the option value.")

using namespace fms;
using namespace xll;

static AddInX xai_corrado_miller_implied_volatility(
	FunctionX(XLL_DOUBLEX, _T("?xll_corrado_miller_implied_volatility"), PREFIX _T("CM.IMPLIED.VOLATILITY"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Value"), IS_VALUE, 4)
	.Num(_T("Strike"), IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the Corrado-Miller implied volatility of a Black call or put option"))
	.Documentation(
		_T("The implied volatilty is that which returns <codeInline>value</codeInline> ")
		_T("from <codeInline>BLACK.VALUE</codeInline>. ")
/*		,
		xml::xlink(_T("BLACK.VALUE"))
*/	)
);
double WINAPI
xll_corrado_miller_implied_volatility(double f, double p, double k, double t)
{
#pragma XLLEXPORT
	double vol(std::numeric_limits<double>::quiet_NaN());

	try {
		vol = black::corrado_miller_implied_volatility(f, p, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return vol;
}

static AddInX xai_black_implied_volatility(
	FunctionX(XLL_DOUBLEX, _T("?xll_black_implied_volatility"), PREFIX _T("BLACK.IMPLIED.VOLATILITY"))
	.Num(_T("Forward"), IS_FORWARD, 100)
	.Num(_T("Value"), IS_VALUE, 4)
	.Num(_T("Strike"), IS_STRIKE, 100)
	.Num(_T("Expiration"), IS_EXPIRATION, .25)
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns the implied volatility of a Black call or put option"))
	.Documentation(
		_T("The implied volatilty is that which returns <codeInline>value</codeInline> ")
		_T("from <codeInline>BLACK.VALUE</codeInline>. ")
/*		,
		xml::xlink(_T("BLACK.VALUE"))
*/	)
);
double WINAPI
xll_black_implied_volatility(double f, double p, double k, double t)
{
#pragma XLLEXPORT
	double vol(std::numeric_limits<double>::quiet_NaN());

	try {
		vol = black::implied_volatility(f, p, k, t);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return vol;
}

