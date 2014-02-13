
#pragma once

#include <string>
#include "Hash.h"


namespace std
{
	template <>
	class hash <std::string>
	{
	public:
		size_t operator()( const std::string & string ) const
		{
			return HashString( string );
		}
	};
}