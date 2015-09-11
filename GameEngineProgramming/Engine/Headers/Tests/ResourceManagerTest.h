
#pragma once

#include <Tests/TDK/TDK.h>
#include <ResourceManager/ResourceManager.h>

Test( ResourceManager_GetSetBudgets )
{
	std::size_t requestSize = 100;

	auto rm = ResourceManager::Instance( );

	rm->SetMemoryBudget( MemType::System, requestSize );
	rm->SetMemoryBudget( MemType::Video, requestSize );

	TestAssertIsTrue( requestSize == rm->GetMemoryBudget( MemType::System ) );
	TestAssertIsTrue( requestSize == rm->GetMemoryBudget( MemType::Video ) );
}

Test( ResourceManager_ResourceIsLoaded )
{
	const std::string resourceName = "dummyResource";

	ResourceManager * rm = ResourceManager::Instance( );

	TestAssertIsTrue( rm->ResourceIsLoaded( resourceName ) );
}
