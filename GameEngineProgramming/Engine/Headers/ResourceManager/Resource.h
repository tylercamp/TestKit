
#pragma once

#include <Patterns/Observer.h>
#include <Utility/Guid.h>

class Resource :
	public Subject
{
public:
	virtual ~Resource( )
	{
	}




	virtual void GetMemUsage( std::size_t & dynamicUsage, std::size_t & videoUsage ) = 0;
};



class MetaResource
{
public:
	Guid Identity;
	Resource * Resource;
	std::string Path;
};