
#pragma once

#include <string>
#include <sstream>


#define CurrentErrorRecord (_test::GenerateErrorRecord( __FILE__, __LINE__ ))

#ifdef _MSC_VER
#define InvokeDebugPoint() __debugbreak( )
#else
#define InvokeDebugPoint()
#endif

#define TrySmartAssert(context)							\
	if( (!context->AssertPassed()) ) {					\
		InvokeFailure(context->AssertFailureMessage);	\
	}

#ifdef _MSC_VER
#define InvokeFailure(failMessage)					\
	if( TestManager::UseSmartDebugOnAssert( ) )	 {	\
		InvokeDebugPoint( );						\
		return;										\
	}												\
	throw std::logic_error( failMessage );			\
	return;
#else
#define InvokeFailure(failMessage)				\
	throw std::logic_error( failMessage ) ;
#endif



/* Use dual-definitions to hide implementation details from users on intellisense */

/* Force the currently-running test to fail. */
#define TestFail() TestFailImplementation()
#define TestFailImplementation() { \
		_test::AssertContext context( CurrentErrorRecord );	\
		TrySmartAssert(_test::Fail( &context ))			\
	}

/* Force the currently-running test to fail with the specified error string. */
#define TestFailMessage(message) TestFailMessageImplementation(message)
#define TestFailMessageImplementation(message) { \
		_test::AssertContext context( CurrentErrorRecord );	\
		TrySmartAssert(_test::Fail( message,  &context ))		\
	}

/* Assert whether 'value' is truthy. */
#define TestAssertIsTrue(value) TestAssertIsTrueImplementation(value)
#define TestAssertIsTrueImplementation(value) { \
		_test::AssertContext context( CurrentErrorRecord );	\
		TrySmartAssert(_test::AssertIsTrue( value, #value,  &context ))	\
	}

/* Assert whether 'value' is falsy. */
#define TestAssertIsFalse(value) TestAssertIsFalseImplementation(value)
#define TestAssertIsFalseImplementation(value) { \
		_test::AssertContext context( CurrentErrorRecord );	\
		TrySmartAssert(_test::AssertIsFalse( value, #value,  &context ))	\
	}

/* Assert whether none of the elements of type 'varsType' match */
#define TestAssertNoneMatch(count, varsType, ...) TestAssertNoneMatchImplementation( count, varsType, __VA_ARGS__ )
#define TestAssertNoneMatchImplementation(count, varsType, ...) { \
		_test::AssertContext context( CurrentErrorRecord ); \
		TrySmartAssert(_test::AssertNoneMatch<varsType>( count, #varsType, &context, __VA_ARGS__ )) \
	}

#define TestFailNotImplemented() TestFailMessage( "Test not implemented." )


namespace _test
{
	class AssertContext
	{
	public:
		AssertContext( const AssertContext & o ) :
			ErrorRecord( o.ErrorRecord ),
			AssertFailureMessage( o.AssertFailureMessage ),
			m_State( o.m_State )
		{
		}

		AssertContext( const std::string & errorRecord ) :
			ErrorRecord( errorRecord ),
			m_State( Incomplete )
		{
		}
		
		void SetAssertResult( bool passed ) {
			m_State = passed ? Succeeded : Failed;
		}

		bool AssertPassed() {
			if (m_State == Incomplete)
				throw std::exception("AssertContext state is incomplete. Assertion must be completed.");

			return m_State == Succeeded ? true : false;
		}

		std::string AssertFailureMessage;
		const std::string ErrorRecord;

	private:
		enum ContextState {
			Incomplete,
			Succeeded,
			Failed
		} m_State;
	};
}


namespace _test
{
	AssertContext * Fail( AssertContext * context );
	AssertContext * Fail( const std::string & message, AssertContext * context );

	template <typename A>
	AssertContext * AssertIsTrue( const A & value, const std::string & valueName, AssertContext * context);

	template <typename A>
	AssertContext * AssertIsFalse( const A & value, const std::string & valueName, AssertContext * context );

	template <typename A>
	AssertContext * AssertNoneMatch( std::size_t count, const std::string & typeName, AssertContext * context, ... );

	std::string GenerateErrorRecord( const std::string & fileName, int line );
}


#include "Assert.inl"