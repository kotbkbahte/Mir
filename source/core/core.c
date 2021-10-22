#include "game_types.h"

#include "../handlers/event_handler.h"
#include "../handlers/keyboard_handler.h"
#include "../graphics/graphics.h"

#include <ft2build.h>
#include FT_FREETYPE_H


TCore *Core;
TState State;
TGameState GameState;
TOpenGLProgram_base m_GlProgram;
GLuint m_Textures[10];
const Uint8* m_Keyboard;
float m_ProjectionMatrix[16];
float m_TestMatrix[16];


unsigned int VAO, VBO;

    FT_Library ft2_lib;
    FT_Face ft2_face;
    TCharTexture m_Characters[128];



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
