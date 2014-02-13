
#include "Resource.h"

class ResourceFactory
{
public:
	static ResourceFactory * Instance( );

	Resource * LoadResource( const std::string & resourceFile );

private:
	ResourceFactory( );
	~ResourceFactory( );
};