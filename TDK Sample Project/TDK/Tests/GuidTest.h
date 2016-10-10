
#include "../SampleSystems/Guid.h"
#include "../TDK/TDK.h"

#include <unordered_map>

Test( Guid_InitUnique )
{
	Guid a, b, c, d;

	TestAssertNoneMatch(4, Guid, a, b, c, d);

	//TestFail( );
}

Test( Guid_OpEquals )
{
	Guid a, b;

	a.m_Data = 0;
	b.m_Data = 0;
	TestAssertIsTrue( a == b );

	a.m_Data = 0;
	b.m_Data = 1;
	TestAssertIsFalse( a == b );
}

Test( Guid_OpNotEqual )
{
	Guid a, b;

	a.m_Data = 0;
	b.m_Data = 1;
	TestAssertIsTrue( a != b );

	a.m_Data = 0;
	b.m_Data = 0;
	TestAssertIsFalse( a != b );
}

Test( Guid_OpGreaterThan )
{
	Guid a, b;

	a.m_Data = 1;
	b.m_Data = 0;
	TestAssertIsTrue( a > b );

	a.m_Data = 0;
	b.m_Data = 0;
	TestAssertIsFalse( a > b );

	a.m_Data = 0;
	b.m_Data = 1;
	TestAssertIsFalse( a > b );
}

Test( Guid_OpLessThan )
{
	Guid a, b;

	a.m_Data = 0;
	b.m_Data = 1;
	TestAssertIsTrue( a < b );

	a.m_Data = 0;
	b.m_Data = 0;
	TestAssertIsFalse( a < b );

	a.m_Data = 1;
	b.m_Data = 0;
	TestAssertIsFalse( a < b );

}

TestRepeating( Guid_OpToString, 300 )
{
	std::string expected = "0xfeedfeed";
	Guid guid;
	guid.m_Data = 0xfeedfeed;

	std::string toStringResult = guid.ToString();
	TestAssertIsTrue( toStringResult == expected );
}
