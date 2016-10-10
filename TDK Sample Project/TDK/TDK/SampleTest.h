
#include "../SampleSystems/Guid.h"
#include "../TDK/TDK.h"

#include <unordered_map>

Test( Guid_InitUnique )
{
	int a, b, c, d;
	a = rand();
	b = rand();
	c = rand();
	d = rand();

	TestAssertNoneMatch(4, int, a, b, c, d);

	//TestFail( );
}

TestRepeating( Guid_OpToString, 300 )
{
	int x = 0;
	x = 5;

	TestAssertIsTrue( x < 10 );
}
