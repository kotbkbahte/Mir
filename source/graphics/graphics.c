#include "graphics.h"

extern TCore *Core;

void InitGraphics()
{
    InitSDL2();

    InitOpenGL();
}

void InitSDL2()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        h_error_msg("failed init sdl2", SDL_ERROR);
    }

    Core->m_WindowSize.width= 1280;
    Core->m_WindowSize.height = 720;

    // Set SDL Attributes
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    //SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 1 );

    Core->m_Window = SDL_CreateWindow("Mir",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      Core->m_WindowSize.width, Core->m_WindowSize.height,
                                      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN  );
    if ( Core->m_Window == NULL )
    {
        h_error_msg("Failed to create window", SDL_ERROR);
    }

    Core->m_Context = SDL_GL_CreateContext(Core->m_Window);
    if(Core->m_Context == NULL)
    {
        h_error_msg("Failed to create gl context", SDL_ERROR);
    }

}

void InitOpenGL()
{

}

void RenderFrame()
{
    glClearColor(0.0f, 0.01f, 0.05f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT);

    //glEnable(GL_MULTISAMPLE);
    //glEnable(GL_STENCIL_TEST);
    //glEnable(GL_DEPTH_TEST);

    glFinish();
    SDL_GL_SwapWindow(Core->m_Window);
}
