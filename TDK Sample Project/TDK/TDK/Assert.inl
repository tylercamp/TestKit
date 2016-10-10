
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cstdarg>

//	Allows the user to define their own; may want to move this API to
//		the test manager.
#ifndef TDK_MAX_PATH_LENGTH
# define TDK_MAX_PATH_LENGTH 50
#endif

namespace _test
{
	//	Really only used in GenerateErrorRecord
	inline std::string ParsePath( std::string path )
	{
		char originalPath[500];
		strcpy_s(originalPath, path.c_str( ));
		int originalPathSize = path.length( );
		for( int i = 0; i < originalPathSize; i++ )
			if( originalPath[i] == '\\' )
				path[i] = '/';

		static std::vector<std::pair<std::string, std::string> > ResultCache;
		auto cacheData = ResultCache.data();
		int cacheSize = ResultCache.size();
		for( int i = 0; i < cacheSize; i++ ) {
			auto & pair = cacheData[i];

			int cacheEntrySize = pair.first.size( );
			if( cacheEntrySize != originalPathSize )
				continue;
			
			const char * cacheEntry = pair.first.c_str( );

			bool succeeded = true;
			for( int i = 0; i < cacheEntrySize; i++ ) {
				if( cacheEntry[i] != originalPath[i] ) {
					succeeded = false;
					break;
				}
			}
			if( succeeded )
				return pair.second;
		}

		/*
		 * Generates a "smart-string" that is a truncated version of the path, but is
		 *	generated to be human-readable by truncating based on how many folders the
		 *	URI is nested in (so you can get full folder names instead of a clipped string
		 *	if the path is too long.) The final result is truncated if the path goes over
		 *	maxLength.
		 *
		 */

		const int maxFolders = 3;
		std::string folderParsedPath;
		if( std::count( path.begin(), path.end(), '/' ) <= maxFolders )
			folderParsedPath = path;
		else
		{
			std::vector<std::string> pathComponents;
			path.reserve( maxFolders );
			for( int i = 0; i < maxFolders; i++ )
			{
				int position = path.rfind( '/' );
				pathComponents.push_back( path.substr( position + 1 ) );
				path = path.substr( 0, position );
			}

			auto pathData = pathComponents.data();
			for( int i = pathComponents.size() - 1; i >= 0; i-- )
			{
				const std::string & entry = pathData[i];
				folderParsedPath += "/" + entry;
			}
		}

		const std::string separator = "...";
		const unsigned int maxLength = TDK_MAX_PATH_LENGTH;

		if( folderParsedPath.length( ) > maxLength - separator.length() )
			folderParsedPath = separator + folderParsedPath.substr( folderParsedPath.length( ) - maxLength - 1 );
		else
			folderParsedPath = separator + folderParsedPath;

		ResultCache.push_back( std::pair<std::string,std::string>( originalPath, folderParsedPath ) );

		return folderParsedPath;
	}

	inline AssertContext * Fail(
		AssertContext * context
		)
	{
		return Fail( "User-forced assertion fail.", context );
	}

	inline AssertContext * Fail(
		const std::string & message,
		AssertContext * context
		)
	{
		context->SetAssertResult( false );
		context->AssertFailureMessage = message + "\n" + context->ErrorRecord;
		return context;
	}



	template <typename A>
	inline AssertContext * AssertIsTrue(
		const A & value,
		const std::string & valueName,
		AssertContext * context
		)
	{
		if( !value )
			return Fail( "AssertIsTrue: Value " + valueName + " was not true.", context );

		context->SetAssertResult(true);
		return context;
	}



	template <typename A>
	inline AssertContext * AssertIsFalse(
		const A & value,
		const std::string & valueName,
		AssertContext * context
		)
	{
		if( value )
			return Fail( "AssertIsFalse: Value " + valueName + " was not false.", context );

		context->SetAssertResult( true );
		return context;
	}



	template <typename A>
	inline AssertContext * AssertNoneMatch(
		std::size_t count,
		const std::string & typeName,
		AssertContext * context,
		...
		)
	{
		if( count == 0 ) {
			context->SetAssertResult( true );
			return context;
		}

		std::vector<A *> parameterList;
		va_list argList;
		va_start( argList, context );

		for( std::size_t i = 0; i < count; i++ )
		{
			parameterList.push_back( &va_arg( argList, A ) );
		}

		va_end( argList );

		bool valueMatched = false;
		int matchIndexA = -1, matchIndexB = -1;

		//	Yes, O(n^2), this could be optimized, don't care right now
		//	TODO: Make this non-O(n^2)
		for( std::size_t i = 0; i < count; i++ )
		{
			for( std::size_t j = 0; j < count; j++ )
			{
				if( i == j )
					continue;

				const Guid & a = *parameterList[i];
				const Guid & b = *parameterList[j];

				if( a == b )
				{
					valueMatched = true;
					matchIndexA = i;
					matchIndexB = j;
				}

				if( valueMatched )
					break;
			}

			if( valueMatched )
				break;
		}

		if( valueMatched ) {
			return Fail( "AssertNoneMatch: Values at indexes " + std::to_string( matchIndexA ) + " and " + std::to_string( matchIndexB ) + " of the " + std::to_string( count ) + " " + typeName + " objects matched.", context );
		}
		else {
			context->SetAssertResult( true );
			return context;
		}
	}



	inline std::string GenerateErrorRecord( const std::string & fileName, int line )
	{
		return "In " + ParsePath( fileName ) + " at line " + std::to_string( line );
	}
}