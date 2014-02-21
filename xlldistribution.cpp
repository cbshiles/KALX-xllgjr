// xlldistribution.cpp
#include "xllgjr.h"

using namespace fms;
using namespace xll;

#pragma region distribution

static AddInX xai_fms_distribution_standard_normal(	
	FunctionX(XLL_FPX, _T("?xll_fms_distribution_standard_normal"), _T("DISTRIBUTION.G"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."))
	.Arg(XLL_FPX, _T("_kappa"), _T("is an optional array of perturbations to the cumulants."))
	.Arg(XLL_LONGX, _T("_n"), _T("is the optional n-th derivative."))
	.Arg(XLL_LONGX, _T("_N"), _T("is the optional number of series terms to return."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns derivatives of a normal distribution perturbed by cumulants."))
	.Documentation(
	)
);
xfp* WINAPI xll_fms_distribution_standard_normal(double x, xfp* kappa, LONG n, LONG N)
{
#pragma XLLEXPORT
	static FPX G;

	try {
		G.resize(1 + N, 1);
		G = 0;
		G[0] = std::numeric_limits<double>::quiet_NaN();

		G[0] = distribution::standard_normal<>::G(x, n, size(*kappa), kappa->array, N, G.array() + 1);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return G.get();
}

static AddInX xai_fms_distribution_esscher(
	FunctionX(XLL_FPX, _T("?xll_fms_distribution_esscher"), _T("DISTRIBUTION.ESSCHER"))
	.Arg(XLL_FPX, _T("cumulants"), _T("are the cumulants."))
	.Arg(XLL_DOUBLEX, _T("gamma"), _T("is the Esscher parameter."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the cumulants of the Esscher transform."))
	.Documentation(R"(
		Returns <math>
			kappa<sub>k</sub><sup>*</sup> = sum<sub>n=0</sub><sup>infty</sup> kappa<sub>k + n</sub> gamma<sup>n</sup>/n!
		</math>.
	)")
);
xfp* WINAPI xll_fms_distribution_esscher(xfp* kappa, double gamma)
{
#pragma XLLEXPORT
	static FPX kappa_;

	try {
		kappa_.resize(kappa->rows, kappa->columns);
		kappa_[0] = std::numeric_limits<double>::quiet_NaN();

		distribution::esscher(size(*kappa), kappa->array, gamma, kappa_.array());
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return kappa_.get();
}

#pragma endregion distribution
