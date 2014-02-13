
#include <Patterns/Observer/Observer.h>
#include <Patterns/Observer/Subject.h>

#include <algorithm>

Subject::~Subject( )
{
	Notify( OBSERVE_INSTANCE_DELETE );

	//	TODO: Observer has literally the same code in its destructor, should
	//		do something about the duplicate code
	while( m_Mediators.size( ) )
		delete m_Mediators.front( );
}

void Subject::Subscribe( int message, Observer * newObserver )
{
	ObservationMediatorCollection::iterator searchResult = m_Mediators.end( );

	for( auto & iterator = m_Mediators.begin( ) ; iterator != m_Mediators.end( ); iterator++ )
	{
		ObservationMediator * currentMediator = *iterator;
		if(	currentMediator->GetObserver( ) == newObserver &&
			currentMediator->m_SubscribedMessage == message )
		{
			searchResult = iterator;
			break;
		}
	}

	if( searchResult == m_Mediators.end( ) )
	{
		ObservationMediator::BuildMediator( this, message, newObserver );
	}
	else
		throw "Message subscription list already contains an entry for the current observer.";
}

void Subject::Unsubscribe( int message, Observer * observer )
{
	for( auto mediator : m_Mediators )
	{
		if( mediator->GetObserver( ) == observer &&
			mediator->GetSubscribedMessage( ) == message )
		{
			delete mediator;
			return;
		}
	}
 }

void Subject::Notify( int message )
{
	Notify( message, nullptr );
}

void Subject::Notify( int message, ObservedNote * notifyInfo )
{
	for( auto link : m_Mediators )
		link->ReceiveNotify( message, notifyInfo );
}