#include "game_types.h"

#include "../handlers/event_handler.h"
#include "../handlers/keyboard_handler.h"
#include "../graphics/graphics.h"

#include <ft2build.h>
#include FT_FREETYPE_H


TCore *Core;
TState State;

TField _grass_fields[] =
{
    [0] = {.i = 0, .j = 0},
    [1] = {.i = 0, .j = 1},
    [2] = {.i = 0, .j = 2},
    [3] = {.i = 0, .j = 3},
    [4] = {.i = 0, .j = 4},
    [5] = {.i = 0, .j = 5},
    [6] = {.i = 0, .j = 6},
    [7] = {.i = 0, .j = 7},
};

TField _sea_fields[] =
{
    [0] = {.i = 1, .j = 0},
    [1] = {.i = 1, .j = 1},
};

TField _ocean_fields[] =
{
    [0] = {.i = 1, .j = 2},
};

TPoint2_c _mountain_landscape[] =
{
    [0] = {.i = 2, .j = 0},
    [1] = {.i = 2, .j = 1},
    [2] = {.i = 2, .j = 2},
};
TPoint2_c _forest_landscape[] =
{
    [0] = {.i = 4, .j = 0},
    [1] = {.i = 4, .j = 1},
};
TPoint2_c _wheat_landscape[] =
{
    [0] = {.i = 4, .j = 2},
};


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
    .m_AnimatedTexturesCount = AT_COUNT,

    .m_TextureMap = {
        .m_Path = "assets/texture_map_.png",
        .m_TextureMapSize = 8,
    },

    .m_Fields = {
        [TT_PLAINS] = _grass_fields,
        [TT_SEA]    = _sea_fields,
        [TT_OCEAN]  = _ocean_fields,
    },
    .m_FieldsSize = {
        [TT_PLAINS] = sizeof(_grass_fields) / sizeof(TField),
        [TT_SEA]    = sizeof(  _sea_fields) / sizeof(TField),
        [TT_OCEAN]  = sizeof(_ocean_fields) / sizeof(TField),
    },

    .m_Landscapes = {
        [LT_ROCK]   = _mountain_landscape,
        [LT_FOREST] = _forest_landscape,
        [LT_WHEAT] = _wheat_landscape,
    },
    .m_LandscapesSize = {
        [LT_ROCK]   = sizeof(_mountain_landscape) / sizeof(TPoint2_c),
        [LT_FOREST] = sizeof(_forest_landscape) / sizeof(TPoint2_c),
        [LT_WHEAT] = sizeof(_wheat_landscape) / sizeof(TPoint2_c),
    },


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

