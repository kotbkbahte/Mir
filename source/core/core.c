#include "../handlers/event_handler.h"
#include "../handlers/keyboard_handler.h"

#include "game_types.h"


TCore *Core;


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
    //SDL_QuitSubSystem()
    SDL_Quit();
    free((void*)Core);
}

void UpdateState()
{


}
