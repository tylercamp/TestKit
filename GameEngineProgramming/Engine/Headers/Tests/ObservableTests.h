
#include <Tests/TDK/TDK.h>
#include <Patterns/Observer.h>



template <typename T>
class ObservableStack
	: public Subject
{
public:
	void Push( T value )
	{
		m_Stack.push_back( value );

		Notify( OBSERVE_CHANGED );
	}

	T Pop( )
	{
		m_Stack.pop_back( );
	}

	std::size_t Size( );

private:
	std::vector<T> m_Stack;
};

class StackObserver
	: public Observer
{
public:
	StackObserver( )
	{
		m_WasNotified = false;
	}

	bool WasNotified()
	{
		bool wasNotified = m_WasNotified;
		m_WasNotified = false;
		return wasNotified;
	}

protected:
	void ReceiveNotify( Subject * source, int message, ObservedNote * notifyInfo ) override
	{
		m_WasNotified = true;
	}

	bool m_WasNotified;
};

Test( Subject_Add_Remove_Observer )
{
	StackObserver observer;
	ObservableStack<int> stack;

	stack.Subscribe( OBSERVE_CHANGED, &observer );
	stack.Subscribe( OBSERVE_INSERTED, &observer );

	TestAssertIsTrue( observer.m_Mediators.size( ) == 2 );
	TestAssertIsTrue( stack.m_Mediators.size( ) == 2 );

	TestAssertIsTrue( observer.m_Mediators.front( )->GetSubscribedMessage( ) == OBSERVE_CHANGED );
	TestAssertIsTrue( observer.m_Mediators.back( )->GetSubscribedMessage( ) == OBSERVE_INSERTED );

	TestAssertIsTrue( stack.m_Mediators.front( )->GetSubscribedMessage( ) == OBSERVE_CHANGED );
	TestAssertIsTrue( stack.m_Mediators.back( )->GetSubscribedMessage( ) == OBSERVE_INSERTED );

	stack.Unsubscribe( OBSERVE_CHANGED, &observer );
	TestAssertIsTrue( stack.m_Mediators.size( ) == 1 );
	TestAssertIsTrue( observer.m_Mediators.size( ) == 1 );

	stack.Unsubscribe( OBSERVE_INSERTED, &observer );
	TestAssertIsTrue( stack.m_Mediators.size( ) == 0 );
	TestAssertIsTrue( observer.m_Mediators.size( ) == 0 );
}

Test( Subject_General_MessageSend )
{
	StackObserver observer;
	ObservableStack<int> stack;

	stack.Subscribe( OBSERVE_CHANGED, &observer );
	stack.Push( 10 );

	TestAssertIsTrue( observer.WasNotified( ) );
}

Test( Subject_InstanceDestroy_MessageSend )
{
	StackObserver observer;
	ObservableStack<int> * stack = new ObservableStack<int>( );

	stack->Subscribe( OBSERVE_INSTANCE_DELETE, &observer );

	delete stack;
	TestAssertIsTrue( observer.WasNotified( ) );
}

Test( Observer_AutoUnsubscribeFromSubject )
{
	StackObserver * observer = new StackObserver( );
	ObservableStack<int> stack;

	stack.Subscribe( OBSERVE_CHANGED, observer );

	delete observer;

	TestAssertIsTrue( stack.m_Mediators.size( ) == 0 );
}

Test( Subject_AutoUnsubscribeObservers )
{
	StackObserver observer1, observer2;
	ObservableStack<int> * stack = new ObservableStack<int>( );

	TestAssertIsTrue(
		observer1.m_Mediators.size( ) == 0 &&
		observer2.m_Mediators.size( ) == 0);

	stack->Subscribe( OBSERVE_CHANGED, &observer1 );
	stack->Subscribe( OBSERVE_CHANGED, &observer2 );

	TestAssertIsTrue(
		observer1.m_Mediators.size( ) == 1 &&
		observer2.m_Mediators.size( ) == 1);

	delete stack;

	TestAssertIsTrue(
		observer1.m_Mediators.size( ) == 0 &&
		observer2.m_Mediators.size( ) == 0);
}