#include "game_types.h"

#include "../handlers/event_handler.h"
#include "../handlers/keyboard_handler.h"
#include "../graphics/graphics.h"



TCore *Core;
TState State;
TOpenGLProgram_base m_GlProgram;
GLuint m_Textures[10];
Uint8* m_Keyboard;


const int WIDTH = 800, HEIGHT = 600;


void InitCore()
{
    Core = malloc(sizeof(TCore));

    InitGraphics();

    InitKeyboard();
}

void CloseCore()
{
    SDL_GL_DeleteContext(Core->m_Context);
    SDL_DestroyWindow(Core->m_Window);
    SDL_Quit();
    free((void*)Core);
}

void UpdateState()
{


}
