// xllsvi.cpp - Stochastic Inspired Volatility
#include "../xll8/xll/xll.h"

#ifndef CATEGORY
#define CATEGORY _T("XLL")
#endif

using namespace xll;

static AddInX xai_gatheral_svi(
	FunctionX(XLL_DOUBLEX, _T("?xll_gatheral_svi"), _T("GATHERAL.SVI"))
	.Num(_T("a"), _T("is a."), 0.04)
	.Num(_T("b"), _T("is b."), 0.4)
	.Num(_T("sigma"), _T("is sigma."), 0.1)
	.Num(_T("rho"), _T("is rho."), -0.4)
	.Num(_T("m"), _T("is m."), 0)
	.Num(_T("k"), _T("is k. "), 0)
	.Category(CATEGORY)
	.FunctionHelp(_T("Gatheral's stochastic volatility inspired formula for the square of implied volatility."))
	.Documentation("")
);
double WINAPI
xll_gatheral_svi(double a, double b, double sigma, double rho, double m, double k)
{
#pragma XLLEXPORT

	return a + b*(rho*(k - m) + sqrt((k - m)*(k - m) + sigma*sigma));
}

static AddInX xai_kalx_svi(
	FunctionX(XLL_DOUBLEX, _T("?xll_kalx_svi"), _T("KALX.SVI"))
	.Num(_T("z"), _T("is moneyness, log k/f."))
	.Num(_T("sigma"), _T("is at-the-money Black-Scholes volatility."), 0.20)
	.Num(_T("m"), _T("is the slope at 0."), 0.01)
	.Num(_T("dm"), _T("is the slope inrcrement: m - dm as x tends to -infinity, m + dm as x tends to infinity."), -0.005)
	.Num(_T("d"), _T("is a rounding parameter."), 2)
	.Category(CATEGORY)
	.FunctionHelp(_T("Stochastic Volatility Inspired formula for the square of implied volatility."))
	.Documentation("")
);
double WINAPI
xll_kalx_svi(double z, double sigma, double m, double dm, double d)
{
#pragma XLLEXPORT

	return sigma*sigma + m*z + dm*(sqrt(z*z + d*d) - d);
}
