
#pragma once

#include <Tests/TDK/InterfaceAPI.h>
#include "ObservationMediator.h"

#include <list>
#include <map>

#define OBSERVE_INSTANCE_DELETE	1

#define OBSERVE_CHANGED		2

#define OBSERVE_REMOVED		3
#define OBSERVE_INSERTED	4

class Observer;
class ObservedNote;
class ObservationMediator;

class Subject
{
public:

	virtual ~Subject( );

	void Subscribe( int message, Observer * newObserver );
	void Unsubscribe( int message, Observer * observer );

TestsIgnore(
protected:
)
	friend class ObservationMediator;

	void Notify( int message );
	void Notify( int message, ObservedNote * notifyInfo );

	//	TODO: Rename
	ObservationMediatorCollection m_Mediators;
};