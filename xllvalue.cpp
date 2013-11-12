// xllvalue.cpp
#include "xllvalue.h"
#include "../xll8/xll/utility/timer.h"

using namespace fms;
using namespace xll;

//!!! not working
static AddInX xai_timer( 
	FunctionX(XLL_DOUBLEX, _T("?xll_timer"), _T("TIMER"))
	.Arg(XLL_LPXLOPERX, _T("Ref"), _T("is a cell reference."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Time a call to Ref."))
);
double WINAPI xll_timer(LPXLOPER px)
{
#pragma XLLEXPORT
	utility::timer t;
	t.start();
	OPERX x = XLL_XLF(Evaluate, XLL_XL_(Coerce, *px));
	t.stop();
	
	return t.elapsed();
}
static AddInX xai_sleep(
	FunctionX(XLL_DOUBLEX, _T("?xll_sleep"), _T("SLEEP"))
	.Arg(XLL_DOUBLEX, _T("Seconds"), _T("is the time in seconds to sleep."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Test routine for TIMER"))
	);
double WINAPI xll_sleep(double s)
{
#pragma XLLEXPORT
	Sleep(1000*s);

	return s;
}

#pragma region distribution

static AddInX xai_fms_distribution_standard_normal(
	FunctionX(XLL_FPX, _T("?xll_fms_distribution_standard_normal"), _T("CDF_"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is a number."))
	.Arg(XLL_FPX, _T("_kappa"), _T("is an optional array of perturbations to the cumulants."))
	.Arg(XLL_LONGX, _T("_n"), _T("is the optional n-th derivative."))
	.Arg(XLL_LONGX, _T("_N"), _T("is the optional number of series terms to return."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Returns derivatives of a normal distribution perturbed by cumulants."))
);
xfp* WINAPI xll_fms_distribution_standard_normal(double x, xfp* kappa, LONG n, LONG N)
{
#pragma XLLEXPORT
	static FPX G;

	try {
		G.resize(1 + N, 1);
		G = 0;
		G[0] = std::numeric_limits<double>::quiet_NaN();

		G[0] = distribution::standard_normal<>::F_(x, n, size(*kappa), kappa->array, N, G.array() + 1);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return G.get();
}

static AddInX xai_fms_distribution_esscher(
	FunctionX(XLL_FPX, _T("?xll_fms_distribution_esscher"), _T("ESSCHER"))
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
/*
static AddInX xai_fms_base_forward(
	FunctionX(XLL_DOUBLEX, _T("?xll_fms_base_forward"), _T("MODEL.FORWARD"))
	.Arg(XLL_HANDLEX, _T("Model"), _T("is a handle to a model."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the forward value of a model."))
);
double WINAPI xll_fms_base_forward(HANDLEX h)
{
#pragma XLLEXPORT
	double f(std::numeric_limits<double>::quiet_NaN());

	try {
		handle<model::base<>> h_(h);

		f = h_->forward;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return f;
}
*/
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
/*
static AddInX xai_fms_instrument_option_strike(
	FunctionX(XLL_DOUBLEX, _T("?xll_fms_instrument_option_strike"), _T("INSTRUMENT.OPTION.STRIKE"))
	.Arg(XLL_HANDLEX, _T("Option"), _T("is a handle to a call or put option."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a call (Strike > 0) or put (Strike < 0) option."))
);
double xll_fms_instrument_option_strike(HANDLEX h)
{
#pragma XLLEXPORT
	double k(std::numeric_limits<double>::quiet_NaN());

	try {
		handle<instrument::option<>> h_(h);

		k = h_->strike;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return k;
}

static AddInX xai_fms_base_volatility(
	FunctionX(XLL_DOUBLEX, _T("?xll_fms_base_volatility"), _T("MODEL.VOLATILITY"))
	.Arg(XLL_HANDLEX, _T("Model"), _T("is a handle to a model."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return the volatility value of a model."))
);
double WINAPI xll_fms_base_volatility(HANDLEX h)
{
#pragma XLLEXPORT
	double s(std::numeric_limits<double>::quiet_NaN());

	try {
		handle<model::base<>> h_(h);

		s = h_->volatility;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}
*/

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
	.FunctionHelp(_T("Values an call (Strike > 0) or put (Strike < 0) using the Fischer Black model."))
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
	FunctionX(XLL_DOUBLEX, _T("?xll_fms_model_gjr_value"), _T("MODEL.BLACK.VALUE"))
	.Arg(XLL_DOUBLEX, _T("Forward"), _T("is the forward value of the underlying."))
	.Arg(XLL_DOUBLEX, _T("Volatility"), _T("is the Black-Scholes volatility of the underlying."))
	.Arg(XLL_LPOPERX, _T("Kappa"),  _T("is an optional array of cumulant perturbations."))
	.Arg(XLL_DOUBLEX, _T("Strike"), _T("is the strike of the option."))
	.Arg(XLL_DOUBLEX, _T("Expiration"), _T("is the time in years to option expiration."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Values an call (Strike > 0) or put (Strike < 0) using the Fischer Black model."))
	.Documentation(R"(
		This can also be called with two arguments, a model and an instrument.
		E.g., <codeInline>BLACK.VALUE(100, 0.2, 90, 0.25) = BLACK.VALUE(BLACK(100, 0.2), OPTION(90, 0.25)</codeInline>
	)")
);
double WINAPI xll_fms_model_gjr_value(double f, double s, LPOPERX pkappa, double k, double t)
{
#pragma XLLEXPORT
	double v(std::numeric_limits<double>::quiet_NaN());

	try {
		if (pkappa->xltype == xltypeMissing) {
			handle<model::gjr<>> m(f);
			handle<instrument::option<>> o(s);

			v = 0;//value<>(*m, *o);
		}
		else {
			v = 0; //!!!value<>(model::black<>(f,s), instrument::option<>(k,t));
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	
	return v;
}

#ifdef _DEBUG

#include <random>
#include "../xll8/xll/utility/timer.h"
#include "../fmsvalue/combinatorial.h"

using namespace fms::combinatorial;

static std::random_device rd{};
static std::default_random_engine dre{rd()};
//static std::default_random_engine dre;

template<class T>
inline double timef(const std::function<T(T)>& f, const std::function<T(void)>& u, size_t n = 1)
{
	utility::timer t;

	t.start();
	while (n--) f(u());
	t.stop();

	return t.elapsed();
}

void test_fms_combinatorial()
{
	ensure (120 == factorial(5));
	double elapsed;

	auto u = [](void) { return 50; };
	elapsed = timef<size_t>([](size_t k) { return choose(100,k); }, u);
	elapsed = timef<size_t>([](size_t k) { return choose(100,k); }, u);

	for (int i = 0; i < 100; ++i) {
		size_t n = std::uniform_int_distribution<size_t>(0, 10)(dre);
		size_t k = std::uniform_int_distribution<size_t>(0, n)(dre);

		ensure (choose(n,k) == factorial(n)/(factorial(k)*factorial(n-k)));
	}
	
}

using namespace fms::polynomial;

void test_fms_polynomial()
{
	double n[] = {1, 1, 2, 6, 24,120, 720,5040,40320,362880};
	double B[] = {1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147};
	double x[] = {1, 1, 1, 1,  1,  1,   1,   1,    1,     1};
	size_t size = sizeof(x)/sizeof(*x);
	auto u = std::bind(std::normal_distribution<>(0, 3), dre);

	for (size_t i = 0; i < size; ++i) {
		double b0, b1, db;

		b0 = Bell<double>(i, i, x);
		ensure (B[i] == b0);

		b1 = Bell<double>(i, i, x, true);
		b0 /= n[i];
		db = b0 - b1;
		ensure (1 + db == 1);
	}

	for (size_t i = 0; i < 10; ++i) {
		double x = u();
		ensure (Hermite<double>(0, x) == 1);
		ensure (Hermite<double>(1, x) == x);
		ensure (Hermite<double>(2, x) == x*x - 1);
		ensure (fabs(Hermite<double>(3, x) - (x*x*x - 3*x)) < 1e-11);
	}
}

void test_fms_distribution()
{
	for (int i = 0; i < 100; ++i) {
		double x = std::uniform_real_distribution<>(0,1)(dre);
		double p = distribution::standard_normal<>::cdf(x);
		double y = distribution::standard_normal<>::inv(p);

		ensure (fabs(y - x) < 1e-15);
	}
}

int xll_test_fmsvalue()
{
	DWORD dw;
	try {
		dw = xll_alert_level;
		xll_alert_level = 7;
		test_fms_combinatorial();
		test_fms_polynomial();
		test_fms_distribution();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
		xll_alert_level = dw;

		return 0;
	}
	xll_alert_level = dw;

	return 1;
}
static Auto<OpenX> xao_test_fmsvalue(xll_test_fmsvalue);

#endif // _DEBUG