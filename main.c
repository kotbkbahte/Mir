#include <stdio.h>
#include <stdlib.h>

#include "source/core/core.h"




#ifdef __linux__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#elif _WIN32
    #include <SDL.h>
#endif


int main(int argc, char *argv[])
{
    InitCore();

    SDL_Event windowEvent;

    while ( 1 )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            {
                break;
            }
        }
    }



    return EXIT_SUCCESS;
    return 0;
}
