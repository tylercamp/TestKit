
#include <Patterns/Observer/ObservationMediator.h>
#include <Patterns/Observer/Subject.h>
#include <Patterns/Observer/Observer.h>


ObservationMediator::ObservationMediator( Subject * subject, int message, Observer * observer ) :
	m_Subject( subject ),
	m_SubscribedMessage( message ),
	m_Observer( observer )
{
	if( !subject )
		throw "Subject cannot be null";
	if( !observer )
		throw "Observer cannot be null";
}

ObservationMediator::~ObservationMediator( )
{
	m_Subject->m_Mediators.erase( m_ObserverLocation );
	m_Observer->m_Mediators.erase( m_SubjectLocation );
}

const Subject * ObservationMediator::GetSubject()
{
	return m_Subject;
}

const Observer * ObservationMediator::GetObserver()
{
	return m_Observer;
}

int ObservationMediator::GetSubscribedMessage()
{
	return m_SubscribedMessage;
}

void ObservationMediator::ReceiveNotify( int message, ObservedNote * note )
{
	m_Observer->ReceiveNotify( m_Subject, message, note );
}

void ObservationMediator::BuildMediator( Subject * subject, int message, Observer * observer )
{
	ObservationMediator * newMediator = new ObservationMediator( subject, message, observer );

	subject->m_Mediators.push_back( newMediator );
	observer->m_Mediators.push_back( newMediator );

	newMediator->m_ObserverLocation = --subject->m_Mediators.end( );
	newMediator->m_SubjectLocation = --observer->m_Mediators.end( );
}
