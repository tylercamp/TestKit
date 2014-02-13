
#pragma once

/*
 * todo: Caching
 *
 */

#include <unordered_map>
#include <Utility/Hash/STL.h>
#include <Patterns/Observer.h>
#include "Resource.h"


enum MemType
{
	System,	//	Regular memory
	Video	//	Video memory
};

typedef std::unordered_map<std::string, Resource *> StringMap;


class ResourceManager
	: public Observer
{
public:
	static ResourceManager * Instance( );



	bool		ResourceIsLoaded( const std::string & resource );
	void		LoadResource( const std::string & resource );

	void		SetMemoryBudget( MemType memoryType, std::size_t byteCount );
	std::size_t	GetMemoryBudget( MemType memoryType );

	std::size_t	GetMemoryUsage( MemType memoryType );

	void		ReceiveNotify( Subject * source, int message, ObservedNote * notifyInfo );



	//	If the resource isn't loaded, it will be loaded automatically
	template <typename T>
	T *	GetResource( const std::string & resourceTag );


TestsIgnore(
private:
)

	ResourceManager( );
	~ResourceManager( );

	std::size_t m_VideoBudget, m_SystemBudget;
	std::size_t m_VideoUsage, m_SystemUsage;

	StringMap m_Resources;
};

#include "ResourceManager.inl"
