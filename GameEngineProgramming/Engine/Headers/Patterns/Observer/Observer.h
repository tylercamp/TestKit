
#pragma once

#include <Tests/TDK/InterfaceAPI.h>
#include <list>

//	TODO: Should we do class declarations or always include the header?
#include "ObservationMediator.h"


class ObservedNote;

class Observer
{
public:
	virtual ~Observer( );

	TestsIgnore(
protected:
	);

	friend class ObservationMediator;

	virtual void ReceiveNotify( Subject * source, int message, ObservedNote * notifyInfo ) = 0;

	//	Mapping of all subscribed subjects and the list of messages subscribed to it
	//		(will need to refactor, bad name)
	ObservationMediatorCollection m_Mediators;
};