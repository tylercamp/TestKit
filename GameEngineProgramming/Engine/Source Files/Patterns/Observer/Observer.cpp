
#include <Patterns/Observer/Observer.h>
#include <Patterns/Observer/Subject.h>

Observer::~Observer( )
{
	while( m_Mediators.size( ) )
		delete m_Mediators.front( );
}