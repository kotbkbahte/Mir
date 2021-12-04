#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED




#ifdef __linux__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#elif _WIN32
    #include <SDL.h>
    #include "../extern/glad.h"

#endif


#include <stdio.h>
#include <stdlib.h>


#define True 1
#define False 0

typedef union
{
    struct {
        float r, g, b;
    };
    struct {
        float x, y, z;
    };
} TPoint3_f;

typedef union
{
    struct {
        int x,y;
    };
    struct {
        int width, height;
    };
} TPoint2_i;


typedef union
{
    struct {
        float x,y;
    };
} TPoint2_f;

typedef struct
{
    SDL_Window* m_Window;
    SDL_GLContext m_Context;
    TPoint2_i m_WindowSize;
} TCore;

typedef struct
{
    int m_SubTileTexture;
    int m_Unit;
    int m_Building;
    int m_Landscape;
} TSubTile;

typedef struct
{
    TSubTile m_SubTile[4];
} TTile;

typedef struct
{
    TTile* m_Tiles;
    int m_Size;
    int m_SelectedTile;
} TMap;

typedef struct
{
    TPoint3_f m_BgColor;
    GLuint m_Background_image;
    TPoint2_i m_BackgroundSize;

    int m_PlayerID;
    TMap m_GameMap;
} TGameState;

enum States {MAIN_MENU, START_MENU, SETTINGS_MENU, QUIT, TEST_MENU, GAME, GAME_MENU, RESEARCH_TREE, STATES_COUNT};
enum Textures {BUTTON_PLAYGAME, BUTTON_SETTINGS, BUTTON_QUIT,
               BUTTON_BACK, BUTTON_WAR1, BUTTON_WAR2,
               BUTTON_WAR3, BUTTON_CHANGE_BG_DARK, BUTTON_CHANGE_BG,
               BUTTON_PRINT_LOG_DARK, BUTTON_PRINT_LOG,
               BUTTON_TEST_1_DARK, BUTTON_TEST_1,
               BACKGROUND_IMAGE, BACKGROUND_IMAGE_SPACE,
               TEXTURES_COUNT};

// Texture game
#define tg(a) TG_ ## a
enum GameTextures {tg(OCEAN), tg(BLUE), tg(SEA),
                   tg(GRASS_DARK), tg(GRASS_LIGHT),
                   tg(ROCK), tg(TOWER), tg(WARRIOR),
                   tg(SELECTED),
                   tg(COUNT)};
#undef tg

// Need?
enum ButtonsDrawFunc {BUTTON_DRAW_DEFAULT, BUTTON_DRAW_STROKE, BUTTON_DRAW_ANOTHER_TEXTURED};
enum ButtonEventFunc {TO_MAIN_MENU, TO_START_MENU, TO_SETTINGS_MENU, GO_BACK_MENU, TO_QUIT, PASS};


typedef void (*TDrawState)(void);

typedef void (*TButtonEventFunc)(void);
typedef void (*TButtonEventFunc_str)(char* str);

typedef void (*TButtonDrawFunc)(int);
typedef void (*TButtonDraw_txyFunc)(int, float, float);
typedef void (*TMouseMoveEventFunc)(int, int);
typedef void (*TMouseClickEventFunc)(int, int);
typedef void (*TToState)(void);

typedef struct
{
    int m_StateIndex;
    int m_HoveredButton;
    TDrawState f_StateDraw;
    TMouseMoveEventFunc f_MouseMoveEvent;
    TMouseClickEventFunc f_MouseClickEvent;
} TState;





typedef const Uint8* TKeyboard;



typedef struct
{
    GLuint ID;

    GLuint projectionLocation;
    GLuint viewLocation;
    GLuint modelLocation;
    GLuint vertexLocation;
    GLuint textureCoordsLocation;
    GLuint textureLocation;
} TOpenGLProgram_base;

typedef struct
{
    GLuint ID;

    GLuint projectionLocation;
    GLuint modelLocation;

    GLuint vertexLocation;
    GLuint textureCoordsLocation;
    GLuint textureLocation;
    GLuint textColorLocation;
    GLuint outlineColorLocation;



} TOpenGLProgram_text;

typedef struct
{
    GLuint ID;

    GLuint projectionLocation;
    GLuint viewLocation;
    GLuint modelLocation;

    GLuint vertexLocation;
    GLuint colorLocation;
} TOpenGLProgram_color;

typedef struct
{
    GLuint ID;

    GLuint projectionLocation;
    GLuint modelLocation;

    GLuint vertexLocation;
    GLuint textureCoordsLocation;
    GLuint textureLocation;
    GLuint colorLightnessLocation;
    GLuint isHoveredLocation;
    GLuint strokeColorLocation;
} TOpenGLProgram_button;

typedef struct
{
    unsigned int m_TextureID;
    TPoint2_i m_Size;
    TPoint2_i m_Bearing;
    unsigned int m_Advance;
} TCharTexture;


typedef struct
{
    TPoint2_f m_Size;
    TPoint2_f m_Pos;
    TPoint3_f m_Color;
    unsigned int m_ID;

    unsigned int m_TextureID;


    int m_IsHovered;
    char m_Text[20];


        TButtonDrawFunc m_Draw;
        TButtonDraw_txyFunc m_Draw_txy;

    TButtonEventFunc m_Event;

} TSimpleButton;



#endif // TYPES_H_INCLUDED
