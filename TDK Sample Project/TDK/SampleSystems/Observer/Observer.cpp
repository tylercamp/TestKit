
#include "Observer.h"
#include "Subject.h"

Observer::~Observer( )
{
	while( m_Mediators.size( ) )
		delete m_Mediators.front( );
}