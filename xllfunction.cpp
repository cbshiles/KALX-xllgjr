// xllfunction.cpp - std::function<OPERX(const OPERX&)>
#include "xllfunction.h"

using namespace xll;

#ifdef _DEBUG

int xll_test_function(void)
{
	try {
		function f([](OPERX x) { x.val.num += 1; return x; });
		function g([](OPERX x) { x.val.num *= 2; return x; });
		function h = f.compose(g);

		OPERX y;
		y = h(OPERX(1));
		ensure (y == 3);

		h = f + g;
		y = h(OPER(1));
		ensure (y == 4);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<OpenAfterX> xao_test_function(xll_test_function);

#endif // _DEBUG