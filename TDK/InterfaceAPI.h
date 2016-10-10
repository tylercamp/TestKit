
#pragma once

#ifdef TESTS_ENABLED
#define TestsIgnore(x)
#else
#define TestsIgnore(x) x
#endif