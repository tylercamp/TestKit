
#pragma once

#include <string>
#include <cstdint>

#include <Tests/TDK/InterfaceAPI.h>

class Guid
{
public:
	Guid( );

	bool operator==( const Guid & o ) const;
	bool operator!=( const Guid & o ) const;
	bool operator<( const Guid & o ) const;
	bool operator>( const Guid & o ) const;

	std::string ToString( ) const;

TestsIgnore(
private:
)

	typedef std::uint64_t LargeInt;
	LargeInt m_Data;
	static LargeInt TotalGuidCount;
};