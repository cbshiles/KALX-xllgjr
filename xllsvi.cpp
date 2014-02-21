// xllsvi.cpp - Stochastic Inspired Volatility
#include "../xll8/xll/xll.h"

#ifndef CATEGORY
#define CATEGORY _T("XLL")
#endif

using namespace xll;

typedef traits<XLOPERX>::xfp xfp;

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
/*
#include <mkl_lapack.h>
static AddInX xai_kalx_svi_fit(
	FunctionX(XLL_FPX, _T("?xll_kalx_svi_fit"), _T("KALX.SVI.FIT"))
	.Num(_T("d"), _T("is the roundness parameter"))
	.Num(_T("z1"), _T("is the moneyness"))
	.Num(_T("s1"), _T("is the implied volatility"))
	.Num(_T("z2"), _T("is the moneyness"))
	.Num(_T("s2"), _T("is the implied volatility"))
	.Num(_T("z3"), _T("is the moneyness"))
	.Num(_T("s3"), _T("is the implied volatility"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Fit KALX.SVI using three option prices."))
	.Documentation("")
);
xfp* WINAPI
xll_kalx_svi_fit(double d, double z1, double s1, double z2, double s2, double z3, double s3)
{
#pragma XLLEXPORT
	static FPX smd(1, 3);

	try {
		// sj*sj = sigma*sigma + m*zj + dm*(sqrt(zj*zj + d*d) - d);
		FPX m(3,3);
		m(0,0) = 1; m(0, 1) = z1; m(0, 2) = sqrt(z1*z1 + d*d) - d;
		m(1,0) = 1; m(1, 1) = z2; m(1, 2) = sqrt(z2*z2 + d*d) - d;
		m(2,0) = 1; m(0, 2) = z3; m(2, 2) = sqrt(z3*z3 + d*d) - d;
		FPX x(3,1);
		x[0] = s1*s1; x[1] = s2*s2; x[2]= s3*s3;

		char t = 't';
		int n = 3, one = 1;
		//DGETRS(
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return smd.get();
}
*/