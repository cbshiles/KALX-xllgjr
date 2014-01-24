// xllcumulant.cpp - cumulants of standard distributions
#include "xllgjr.h"

using namespace fms;
using namespace xll;

static AddInX xai_fms_cumulant_scale(
	FunctionX(XLL_FPX, _T("?xll_fms_cumulant_scale"), _T("CUMULANT.SCALE"))
	.Num(_T("Scale"), _T("multiply the random variable by Scale."))
	.Array(_T("Kappa"), _T("is an array of cumulants."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the cumulants of the scaled random variable."))
);
xfp* WINAPI xll_fms_cumulant_scale(double c, xfp* pkappa)
{
#pragma XLLEXPORT
	cumulant::scale(c, size(*pkappa), pkappa->array);

	return pkappa;
}

static AddInX xai_fms_cumulant_poisson(
	FunctionX(XLL_FPX, _T("?xll_fms_cumulant_poisson"), _T("CUMULANT.POISSON"))
	.UShort(_T("count"), _T("is the number of cumulants to return."))
	.Num(_T("mean"), _T("is the mean of the Poisson distribution."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the cumulants of a scaled Poisson distribution."))
);
xfp* WINAPI xll_fms_cumulant_poisson(USHORT n, double mu)
{
#pragma XLLEXPORT
	static FPX kappa;

	try {
		kappa.resize(n, 1);

		cumulant::poisson<>(mu, n, kappa.begin());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		kappa = std::numeric_limits<double>::quiet_NaN();
	}
	catch (...) {
		XLL_ERROR("unknown exception");
	}

	return kappa.get();
}

static AddInX xai_fms_cumulant_gamma(
	FunctionX(XLL_FPX, _T("?xll_fms_cumulant_gamma"), _T("CUMULANT.GAMMA"))
	.UShort(_T("count"), _T("is the number of cumulants to return."))
	.Num(_T("mean"), _T("is the mean of the gamma distribution."))
	.Num(_T("variance"), _T("is the variance of the gamma distribution."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the cumulants of a scaled gamma distribution."))
);
xfp* WINAPI xll_fms_cumulant_gamma(USHORT n, double mu, double s2)
{
#pragma XLLEXPORT
	static FPX kappa;

	try {
		kappa.resize(n, 1);

		cumulant::gamma<>(mu, s2, n, kappa.begin());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		kappa = std::numeric_limits<double>::quiet_NaN();
	}
	catch (...) {
		XLL_ERROR("unknown exception");
	}

	return kappa.get();
}