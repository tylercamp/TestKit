
#pragma once

/* Note: Internal */

class Subject;
class Observer;
class ObservedNote;

#include <list>
#include <Tests/TDK/InterfaceAPI.h>

class ObservationMediator;

typedef std::list<ObservationMediator *> ObservationMediatorCollection;

/* Note: Not really being used as a mediator, this is more of a ModelView
	situation (bridge?)
*/

/* Guarantee: If you delete a mediator, all other references to the mediator
	within the Observable library will be removed as well. All mediator
	references within Observable support classes should be valid, there
	shouldn't be any dangling pointers.
*/
class ObservationMediator
{
public:
	ObservationMediator( Subject * subject, int message, Observer * observer );
	~ObservationMediator( );

	friend class Subject;

	const Subject * GetSubject( );
	const Observer * GetObserver( );
	int GetSubscribedMessage( );

	static void BuildMediator( Subject * subject, int message, Observer * observer );

protected:
	void ReceiveNotify( int message, ObservedNote * note );


TestsIgnore(
private:
	);

	Subject * m_Subject;
	Observer * m_Observer;

	ObservationMediatorCollection::iterator m_SubjectLocation, m_ObserverLocation;

	int m_SubscribedMessage;
};