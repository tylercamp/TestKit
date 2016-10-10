
#include "Guid.h"
#include <sstream>

std::uint64_t Guid::TotalGuidCount = 0;

Guid::Guid( ) :
	m_Data( TotalGuidCount++ )
{
}

bool Guid::operator==( const Guid & o ) const
{
	return m_Data == o.m_Data;
}

bool Guid::operator!=( const Guid & o ) const
{
	return m_Data != o.m_Data;
}

bool Guid::operator<( const Guid & o ) const
{
	return m_Data < o.m_Data;
}

bool Guid::operator>( const Guid & o ) const
{
	return m_Data > o.m_Data;
}

std::string Guid::ToString( ) const
{
	std::ostringstream stream;
	stream << std::hex << m_Data;

	return "0x" + stream.str();
}