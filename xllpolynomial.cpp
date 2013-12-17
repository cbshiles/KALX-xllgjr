// xllpolynomial.cpp
#include "xllgjr.h"

using namespace fms;
using namespace xll;

static AddInX xai_fms_polynomial_bell(
	FunctionX(XLL_DOUBLEX, _T("?xll_fms_polynomial_bell"), _T("POLYNOMIAL.BELL"))
	.Arg(XLL_LONGX, _T("Order"), _T("is the order of the polynomial."))
	.Arg(XLL_FPX, _T("Args"), _T("is an array of numerical arguments."))
	.Arg(XLL_BOOLX, _T("_Reduced"), _T("is a optional argument indicating the result is reduced."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Computes the complete Bell polynomials where Reduced means divided by factorial Order."))
	.Documentation(R"(
		Bell polynomials satisfy the recursion
		<math>B<sub>n+1</sub>(x<sub>1</sub>, ..., x<sub>n</sub>) =
		)" ENT_sum R"(<sub>k = 0</sub><sup>n</sup> C(n,k) B<sub>n - k</sub>(x<sub>1</sub>, ..., x<sub>n - k</sub>)
		x<sub>k + 1</sub></math>. Where <math>C(n,k) = n!/(n - k)!k!</math>.
		)"
	)
);
double WINAPI xll_fms_polynomial_bell(LONG n, const xfp* px, BOOL reduced)
{
#pragma XLLEXPORT
	double y(std::numeric_limits<double>::quiet_NaN());

	try {
		y = polynomial::Bell(n, size(*px), px->array, !!reduced);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return y;
}

static AddInX xai_fms_polynomial_hermite(
	FunctionX(XLL_DOUBLEX, _T("?xll_fms_polynomial_hermite"), _T("POLYNOMIAL.HERMITE"))
	.Arg(XLL_LONGX, _T("Order"), _T("is the order of the polynomial."))
	.Arg(XLL_DOUBLEX, _T("Arg"), _T("is the argument"))
	.Category(CATEGORY)
	.FunctionHelp(_T("Computes Hermite polynomials."))
	.Documentation()
);
double WINAPI xll_fms_polynomial_hermite(LONG n, double x)
{
#pragma XLLEXPORT
	double y(std::numeric_limits<double>::quiet_NaN());

	try {
		y = polynomial::Hermite(n, x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return y;
}
