
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <string>

#include "Resource.h"

class Image :
	public Resource
{
public:

	Image( ) :
		m_Surface( nullptr )
	{
	}

	Image( int width, int height )
	{
	}

	~Image( )
	{
		if( m_Surface )
			SDL_FreeSurface( m_Surface );

		m_Surface = nullptr;
	}

	void LoadFromFile( const std::string & file )
	{
		m_Surface = IMG_Load( file.c_str( ) );
		if( m_Surface == nullptr )
			throw "Unable to find " + file;
	}

	const SDL_Surface * GetSurface( )
	{
		return m_Surface;
	}

	virtual void GetMemUsage( std::size_t & dynamicUsage, std::size_t & videoUsage ) override
	{
		dynamicUsage =
			sizeof( Image ) + sizeof( SDL_Surface ) +
			m_Surface->format->BitsPerPixel * m_Surface->w * m_Surface->h;
	}

private:
	SDL_Surface * m_Surface;
};