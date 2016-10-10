
//
//  TDK.cpp
//  GameEngineProgramming
//
//  Created by Tyler Camp on 00/00/00.
//  Copyright 2012 Tyler Camp. All rights reserved.
//

#include "TDK.h"
#include "../Console.h"
#include <sstream>
#include <string>

#include <chrono>

static const std::string SeparatorText = "==========================================";

using namespace std;

typedef std::chrono::high_resolution_clock
	Clock;
typedef std::chrono::high_resolution_clock::time_point
	TimePoint;

void TestManager::AddInjector(TestInjector * newInjector)
{
	CheckInjectorList( );
	m_Injectors->push_back( newInjector );
}

void TestManager::RunTests( )
{
#ifndef _DEBUG
	std::ostringstream directStream;
	std::ostream & outputStream = directStream;
#else
	std::ostream & outputStream = std::cout;
#endif
	CheckInjectorList( );

	outputStream << "Starting testing..." << std::endl << SeparatorText << std::endl;

	int successCount = 0;

	TimePoint startTime = Clock::now( );

	for (TestInjector * currentInjector : *m_Injectors)
	{
		TestResult result = currentInjector->RunTest( m_AutoCatchExceptions );


		if (result.TestPassed)
			Console::SetBackgroundColor( Console::Green );
		else
			Console::SetBackgroundColor( Console::Red );

		outputStream << " ";

		Console::SetBackgroundColor( Console::Black );
		Console::SetFontColor( Console::White );

		outputStream << " ";

		outputStream.precision( 3 );

		outputStream
			<< currentInjector->TestName() << " | "
			<< ( result.TestPassed ? "Passed" : "Failed" ) << " | "
			<< "Time: " << result.TimeMS << "ms";

		if( result.Iterations > 1 )
			outputStream
			<< " | Iterations: " << result.Iterations
			<< " | Avg Time: " << result.AverageTimeMS << "ms";

		outputStream << std::endl;

		if (result.TestPassed)
			successCount++;
		else
		{
			outputStream << "Failure Message: ";
			outputStream.flush();

			Console::SetFontColor( Console::Yellow );
			outputStream << result.ErrorMessage;
			outputStream.flush();

			Console::SetFontColor( Console::White );
			outputStream << std::endl;
		}
	}

	Console::SetFontColor( Console::White );
	outputStream << SeparatorText << std::endl;

	Console::SetFontColor( Console::Cyan );
	auto duration = chrono::duration_cast< chrono::duration< double > >( Clock::now( ) - startTime );

	outputStream
		<< "Testing complete, summary:" << std::endl
		<< "\t Successful: " << successCount << std::endl
		<< "\t     Failed: " << m_Injectors->size() - successCount << std::endl
		<< "\tTotal Tests: " << m_Injectors->size() << std::endl
		<< "\t Total Time: " << duration.count() << "s" << std::endl << std::endl;

	Console::SetFontColor( Console::White );

#ifdef _DEBUG
	std::cin.ignore( );
#else
	OutputDebugStringA( directStream.str().c_str() );
#endif
}

bool TestManager::AutoCatchExceptions( )
{
	return m_AutoCatchExceptions;
}

void TestManager::AutoCatchExceptions( bool autoCatchExceptions )
{
	m_AutoCatchExceptions = autoCatchExceptions;
}

bool TestManager::UseSmartDebugOnAssert( )
{
	return m_UseSmartDebugOnAssert;
}

void TestManager::UseSmartDebugOnAssert( bool smartDebug )
{
	m_UseSmartDebugOnAssert = smartDebug;
}

void TestManager::CheckInjectorList( )
{
	if( !m_Injectors )
		m_Injectors = new std::list< TestInjector * >( );
}

//	Made a pointer so that it can be initialized as necessary
std::list<TestInjector *> * TestManager::m_Injectors = nullptr;

bool TestManager::m_AutoCatchExceptions = true;
#ifdef _MSC_VER
bool TestManager::m_UseSmartDebugOnAssert = true;
#endif






TestInjector::TestInjector( TestFunc function, std::string testName )
{
	m_TestFunc = function;
	m_TestName = testName;
	m_TestPassed = false;
	m_Iterations = 1;

	TestManager::AddInjector( this );
}

TestInjector::TestInjector( TestFunc function, std::string testName, std::size_t iterations ) {
	m_TestFunc = function;
	m_TestName = testName;
	m_TestPassed = false;
	m_Iterations = iterations;

	TestManager::AddInjector( this );
}

TestResult TestInjector::RunTest( bool autoCatchExceptions )
{
	TestResult result;
	m_TestPassed = true;
	result.ErrorMessage = "";

	TimePoint startTime = Clock::now( );

	for( std::size_t iteration = 0; iteration < m_Iterations; iteration++ )
	{
		result.ErrorMessage = _RunSingleTest( autoCatchExceptions );

		if( !m_TestPassed )
			break;
	}

	auto testTimeSpan = chrono::duration_cast< chrono::milliseconds >( Clock::now( ) - startTime );

	result.TestPassed = m_TestPassed;
	result.TimeMS = ( int )testTimeSpan.count();
	result.AverageTimeMS = ( int )testTimeSpan.count( ) / ( float )m_Iterations;
	result.Iterations = m_Iterations;

	return result;
}

std::string TestInjector::_RunSingleTest( bool autoCatchExceptions )
{
	std::string error = "";

	if( autoCatchExceptions ) {
		try {
			m_TestFunc( );
		}
		catch( std::exception e ) {
			m_TestPassed = false;
			error = std::string( e.what( ) );

			if( !autoCatchExceptions )
				throw;
		}
		catch( const std::string & e ) {
			m_TestPassed = false;
			error = e;

			if( !autoCatchExceptions )
				throw;
		}
		catch( const char * e ) {
			m_TestPassed = false;
			error = e;

			if( !autoCatchExceptions )
				throw;
		}
		catch( ... ) {
			m_TestPassed = false;
			error = "Unknown error.";

			if( !autoCatchExceptions )
				throw;
		}
	} else {
		m_TestFunc( );
		error = "Exceptions are unhandled, no error information available.";
	}

	return error;
}

bool TestInjector::TestPassed( ) const
{
	return m_TestPassed;
}

const std::string & TestInjector::TestName( ) const
{
	return m_TestName;
}