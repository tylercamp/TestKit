
#include "Tests/Tests.h"

void RunTests( )
{
#ifdef TESTS_ENABLED
	TestManager::AutoCatchExceptions( true );
	TestManager::UseSmartDebugOnAssert( true );
	TestManager::RunTests( );
#endif
}

#ifdef main
#undef  main
#endif
int main( )
{
	RunTests( );


	return 0;
}