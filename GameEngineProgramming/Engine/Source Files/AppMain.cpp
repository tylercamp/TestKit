
#include <Tests/Tests.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void RunTests( )
{
#ifdef TESTS_ENABLED
	TestManager::AutoCatchExceptions( true );
	TestManager::UseSmartDebugOnAssert( true );
	TestManager::RunTests( );
#endif
}

#ifdef main
#undef  main
#endif
int main( )
{
	SDL_Init( SDL_INIT_EVERYTHING );
	IMG_Init( IMG_INIT_PNG | IMG_INIT_JPG );

	RunTests( );

	IMG_Quit( );
	SDL_Quit( );

	return 0;
}