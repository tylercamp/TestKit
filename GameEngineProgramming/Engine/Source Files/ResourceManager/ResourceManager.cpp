
#include <ResourceManager\ResourceManager.h>
#include <ResourceManager\ResourceObservedNote.h>
#include <ResourceManager\ResourceFactory.h>

ResourceManager * ResourceManager::Instance()
{
	static ResourceManager * rm = nullptr;
	if( rm == nullptr )
		rm = new ResourceManager( );
	return rm;
}

ResourceManager::ResourceManager()
{
	m_SystemBudget = -1;
	m_VideoBudget = -1;

	m_SystemUsage = 0;
	m_VideoUsage = 0;
}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::ResourceIsLoaded( const std::string & resource )
{
	throw nullptr;
}

void ResourceManager::LoadResource( const std::string & resource )
{
	if( ResourceIsLoaded( resource ) )
		return;

	ResourceFactory * rf = ResourceFactory::Instance( );
	m_Resources[resource] = rf->LoadResource( resource );
}

void ResourceManager::SetMemoryBudget( MemType memoryType, std::size_t byteCount )
{
	switch( memoryType )
	{
	case( MemType::System ): m_SystemBudget = byteCount; break;
	case( MemType::Video ): m_VideoBudget = byteCount; break;
	default: throw nullptr;
	}
}

std::size_t ResourceManager::GetMemoryBudget( MemType memoryType )
{
	switch( memoryType )
	{
	case( MemType::System ): return m_SystemBudget;
	case( MemType::Video ): return m_VideoBudget;
	default: throw nullptr;
	}
}

std::size_t ResourceManager::GetMemoryUsage( MemType memoryType )
{
	switch( memoryType )
	{
	case( MemType::System ): return m_SystemUsage;
	case( MemType::Video ): return m_VideoUsage;
	default: throw nullptr;
	}
}

void ResourceManager::ReceiveNotify( Subject * source, int message, ObservedNote * notifyInfo )
{
	switch( message )
	{
	case( OBSERVE_RESOURCE_SIZE_CHANGED ):
		auto note = (ResourceObservedNote *)notifyInfo;
		m_SystemUsage += note->DynamicSizeChange;
		m_VideoUsage += note->VideoSizeChange;
		break;
	}
}
