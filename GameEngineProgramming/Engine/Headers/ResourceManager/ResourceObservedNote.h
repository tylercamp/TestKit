
#pragma once

#include <Patterns/Observer.h>
#include <Tests/TDK/InterfaceAPI.h>
#include "Resource.h"

#define OBSERVE_RESOURCE_SIZE_CHANGED 3001

class ResourceObservedNote :
	public ObservedNote
{
public:
	Resource * Resource;

	std::size_t VideoSizeChange, DynamicSizeChange;
};