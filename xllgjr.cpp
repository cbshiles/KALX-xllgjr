// xllvalue.cpp
#include "xllgjr.h"

using namespace fms;
using namespace xll;

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


#ifdef _DEBUG

#include <random>
#include "../xll8/xll/utility/timer.h"
#include "../fmsgjr/combinatorial.h"

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

	size_t n = 10;
	auto u = [n](void) { return n/2; };
	elapsed = timef<size_t>([](size_t k) { return choose(10,k); }, u);
	elapsed = timef<size_t>([](size_t k) { return choose(10,k); }, u);

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
	const char* fs;
	fs = __FUNCSIG__;
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