// xllvalue.h - header file for project
// Uncomment the following line to use features for Excel2007 and above.
//#define EXCEL12
#include "../xll8/xll/xll.h"
#include "../fmsgjr/fmsgjr.h"

#ifndef CATEGORY
#define CATEGORY _T("GJR")
#endif

typedef xll::traits<XLOPERX>::xcstr xcstr; // pointer to const string
typedef xll::traits<XLOPERX>::xword xword; // use for OPER and FP indices
typedef xll::traits<XLOPERX>::xfp xfp; // pointer to const string
