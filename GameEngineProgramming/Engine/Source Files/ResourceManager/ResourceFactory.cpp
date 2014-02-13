
#include <ResourceManager/ResourceFactory.h>
#include <ResourceManager/Image.h>

ResourceFactory * ResourceFactory::Instance( )
{
	static ResourceFactory * rf = nullptr;
	if( rf == nullptr )
		rf = new ResourceFactory( );

	return rf;
}

Resource * ResourceFactory::LoadResource( const std::string & resourceFile )
{
	/* Assume that all resources are images for now, will abstract this later */
	
	Image * image = new Image();
	image->LoadFromFile( resourceFile );
	return image;
}

ResourceFactory::ResourceFactory()
{
}

ResourceFactory::~ResourceFactory()
{
}

