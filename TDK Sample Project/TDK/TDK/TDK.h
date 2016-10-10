
#pragma once

#include <list>

class TestInjector;

class TestManager
{
public:
	static void RunTests( );
	static bool AutoCatchExceptions( );
	static void AutoCatchExceptions( bool autoCatchExceptions );

#ifdef _MSC_VER
	static bool UseSmartDebugOnAssert( );
	static void UseSmartDebugOnAssert( bool smartDebug );
#endif

protected:
	static void AddInjector(TestInjector * newInjector);
	friend class TestInjector;

private:
	static void CheckInjectorList( );
	static std::list<TestInjector *> * m_Injectors;
	static bool m_AutoCatchExceptions;

#ifdef _MSC_VER
	static bool m_UseSmartDebugOnAssert;
#endif
};

struct TestResult
{
	float AverageTimeMS;
	int TimeMS;
	bool TestPassed;
	std::size_t Iterations;

	/* Empty if TestPassed == true */
	std::string ErrorMessage;
};

typedef void (* TestFunc) ( );


class TestInjector
{
public:
	TestInjector( TestFunc function, std::string testName );
	TestInjector( TestFunc function, std::string testName, std::size_t iterations );

	TestResult RunTest( bool autoCatchExceptions );
	bool TestPassed() const;
	const std::string & TestName() const;

protected:
	bool m_TestPassed;

private:
	std::string _RunSingleTest( bool autoCatchExceptions );

	TestFunc	m_TestFunc;
	std::string	m_TestName;
	std::size_t m_Iterations;
};

#define Test(TestName)												\
	void _##TestName( );											\
	TestInjector _##TestName##_Injector( _##TestName, #TestName );	\
	inline void _##TestName( )

#define TestRepeating(TestName, Iterations)											\
	void _##TestName( );														\
	TestInjector _##TestName##_Injector( _##TestName, #TestName, Iterations );	\
	inline void _##TestName( )


#include "Assert.h"