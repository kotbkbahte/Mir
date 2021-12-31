#include "game_types.h"

#include "../handlers/event_handler.h"
#include "../handlers/keyboard_handler.h"
#include "../graphics/graphics.h"

#include <ft2build.h>
#include FT_FREETYPE_H


TCore *Core;
TState State;
TGameState GameState;

TAnimations m_MirAnimations;

TMirTile* m_AnimatedTiles;


TOpenGLProgram_base m_GlProgram;
TOpenGLProgram_text m_GlProgram_text;
TOpenGLProgram_color m_GlProgram_color;
TOpenGLProgram_button m_GlProgram_button;
TOGLP_tile_anim m_OGLP_anim;

TTextures m_MirTextures =
{
    .m_AnimatedTextures = {

        [AT_WATER] = {
            .m_Path = "assets/animated/water/water.png",
            .m_Count = 8,
        },

        [AT_WARRIOR] =
        {
            .m_Path = "/pass.png",
            .m_Count = 8,
        }
    },

    .m_AnimatedTexturesCount = AT_COUNT
};
GLuint m_Textures[TEXTURES_COUNT];
GLuint m_GameTextures[TG_COUNT];
GLuint m_FieldTextures[FT_COUNT];
GLuint m_BuildingTextures[BT_COUNT];
GLuint m_LandscapeTextures[LT_COUNT];

const Uint8* m_Keyboard;
float m_ProjectionMatrix[16];
float m_ViewMatrix[16];
float m_IdentityMatrix[16];
float m_ModelMatrix[16];
float m_TestMatrix[16];




unsigned int VAO, VBO;

    FT_Library ft2_lib;
    FT_Face ft2_face;
    TCharTexture m_Characters[128];


void InitCore()
{
    Core = malloc(sizeof(TCore));

    InitGraphics();
// TODO (kotbkbahte#1#): InitKeyboard to InitGraphics ...
//

    InitKeyboard();
}

void CloseCore()
{
    SDL_GL_DeleteContext(Core->m_Context);
    SDL_DestroyWindow(Core->m_Window);
    SDL_Quit();
    free((void*)Core);
}

