
#pragma once

#include <iostream>
#include <string>

#include <Windows.h>

namespace Console
{
	enum Color
	{
		Black	= 0,
		White	= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

		Red		= FOREGROUND_RED,
		Green	= FOREGROUND_GREEN,
		Blue	= FOREGROUND_BLUE,

		Yellow	= FOREGROUND_RED | FOREGROUND_GREEN,
		Magenta	= FOREGROUND_RED | FOREGROUND_BLUE,
		Cyan	= FOREGROUND_GREEN | FOREGROUND_BLUE
	};

	inline std::string ReadLine( )
	{
		std::string result;
		std::getline( std::cin, result );
		return result;
	}

	inline void Pause( )
	{
		ReadLine( );
	}

	inline void SetFontColor( Color color )
	{
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), (WORD)color );
	}

	inline void SetBackgroundColor( Color color )
	{
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), ((WORD)color) << 4 );
	}
}