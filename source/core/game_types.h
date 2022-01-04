#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED




#ifdef __linux__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#elif _WIN32
    #include <windows.h>
    #include <SDL.h>
    #include "../extern/glad.h"


#endif


#include <stdio.h>
#include <stdlib.h>


#define True 1
#define False 0
#define HERE printf("Here!\n")

typedef void (*TDrawState)(void);

typedef void (*TButtonEventFunc)(void);
typedef void (*TButtonEventFunc_str)(char* str);

typedef void (*TButtonDrawFunc)(int);
typedef void (*TButtonDraw_txyFunc)(int, float, float);

typedef void (*TMouseMoveEventFunc)(int, int);
typedef void (*TMouseClickEventFunc)(int, int);
typedef void (*TMouseButtonDownEvent)(int, int, int);
typedef void (*TMouseButtonUpEvent)(int, int, int);



typedef void (*TKeyboardDownEvent)(SDL_Keycode);
typedef void (*TKeyboardUpEvent)(SDL_Keycode);
typedef void (*TKeyboardPressEvent)(SDL_Keycode);


typedef void (*TToState)(void);


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
        char x, y;
    };
    struct {
        char i, j;
    };
} TPoint2_c;

typedef union
{
    struct {
        unsigned int x, y;
    };
    struct {
        unsigned int i, j;
    };
} TPoint2_ui;

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

//typedef struct
//{
//    int m_SubTileTexture;
//    int m_Unit;
//    int m_Building;
//    int m_Landscape;
//} TSubTile;



//typedef struct
//{
//    TTile* m_Tiles;
//    int m_Size;
//
//    unsigned int m_IsTileSelected;
//    TPoint2_ui m_SelectedTile;
//} TMap;



typedef struct
{
    TPoint2_c;
    int f_EventUpdate;

    TPoint2_i m_Pos;
    TPoint2_i m_Offset;

} TBuilding;

typedef struct
{
    TPoint2_c m_Texture;
    TPoint2_i m_Pos;

} TLandscape;

typedef struct
{
    int m_ID;
    int m_Textures;
    int m_Leader;
    int f_OnAttack;
} TUnit;

typedef TPoint2_c TField;



typedef struct
{
    int m_Texture;
    int m_Unit;
    int m_Building;
    int m_Landscape;

} TMirTile;

typedef struct
{
    int32_t m_TileType;

    TPoint2_c m_Field;
    int m_Landscape;
    int m_Building;
    int m_Unit;
} TTile;



typedef struct
{
    TMirTile* m_Tiles;
    int m_Size;

    TTile* m_Tiles1;


    unsigned int m_IsTileSelected;
    TPoint2_ui m_SelectedTile;
} TMirMap;

#define tt(a) TT_ ## a
enum TileType {tt(PLAINS), tt(SEA), tt(OCEAN),
               tt(COUNT)};

#undef tt

#define lt(a) LT_ ## a
enum LandscapeTextures {lt(ROCK), lt(FOREST), lt(WHEAT),
                        lt(COUNT)};

#undef lt


typedef struct
{
    TPoint3_f m_BgColor;
    GLuint m_Background_image;
    TPoint2_i m_BackgroundSize;

    int m_PlayerID;

    TMirMap m_MirMap;

    TBuilding* m_Buildings;
    int m_BuildingsCount;

    TLandscape* m_Landscapes;
    int m_LandscapesCount;

    TUnit* m_Units;
    int m_UnitsCount;

} TGameState;


typedef void (*TBuildingUpdateFunc)(TGameState*);


enum States {MAIN_MENU, START_MENU, SETTINGS_MENU, QUIT, TEST_MENU, GAME, GAME_MENU, RESEARCH_TREE, STATES_COUNT};
enum Textures {BUTTON_PLAYGAME, BUTTON_SETTINGS, BUTTON_QUIT,
               BUTTON_BACK, BUTTON_WAR1, BUTTON_WAR2,
               BUTTON_WAR3, BUTTON_CHANGE_BG_DARK, BUTTON_CHANGE_BG,
               BUTTON_PRINT_LOG_DARK, BUTTON_PRINT_LOG,
               BUTTON_TEST_1_DARK, BUTTON_TEST_1,
               BACKGROUND_IMAGE, BACKGROUND_IMAGE_SPACE,
               TEXTURES_COUNT};






// Grass = 8
// Sea = 2
// Ocean = 1


// Texture game
#define tg(a) TG_ ## a
enum GameTextures {tg(OCEAN), tg(BLUE), tg(SEA),
                   tg(GRASS_DARK), tg(GRASS_LIGHT),
                   tg(ROCK), tg(TOWER), tg(WARRIOR),
                   tg(SELECTED), tg(SELECTED_1),
                   tg(COUNT)};
#undef tg
// Fields textures
#define ft(a) FT_ ## a
enum FieldTextures {ft(GRASS_1), ft(GRASS_2), ft(GRASS_3),

                    ft(COUNT)};
#undef ft


#define bt(a) BT_ ## a
enum BuildingTextures {bt(HOUSE), bt(FARM),
                       bt(TOWER),
                       bt(COUNT)};

#undef bt



#define at(a) AT_ ## a
enum AnimatedTexures {at(WATER), at(WARRIOR),
                      at(SELECTED),
                      at(COUNT)};
#undef at




// Need?
enum ButtonsDrawFunc {BUTTON_DRAW_DEFAULT, BUTTON_DRAW_STROKE, BUTTON_DRAW_ANOTHER_TEXTURED};
enum ButtonEventFunc {TO_MAIN_MENU, TO_START_MENU, TO_SETTINGS_MENU, GO_BACK_MENU, TO_QUIT, PASS};



typedef struct
{
    int m_StateIndex;
    int m_HoveredButton;
    int m_PressedButton;
    TDrawState f_StateDraw;

// TODO (kotbkbahte#1#): remove "Func" in type name
    TMouseMoveEventFunc f_MouseMoveEvent;
    TMouseClickEventFunc f_MouseClickEvent;
    TMouseButtonDownEvent f_MouseDownEvent;
    TMouseButtonUpEvent f_MouseUpEvent;


    TKeyboardPressEvent f_KeyboardPress;

} TState;

// ANIMATIONS TYPES

#define PATH_LENGTH 30
typedef struct
{
    int id;
    char m_Path[64];
    GLuint m_Texture;
    int m_Count;

} TAnimatedTexture;


typedef struct
{

} TAnimationBase;

typedef struct
{
    int m_Frame;
    TAnimatedTexture* m_AnimatedTexture;

} TTextureAnimation;

typedef void (*TAnimationUpdateFunc)(TTextureAnimation*);

typedef struct
{
    TTextureAnimation* m_TextureAnimations;
    int m_TextureAnimationsCount;

    int* m_ActiveTileTexAnim;
    int m_ActiveTileTexAnimCount;


} TAnimations;

typedef struct
{
    TPoint2_i f;
} TPosAnimation;


//


// TEXTURES

typedef struct
{
    char m_Path[64];
    GLuint m_Texture;
    int m_TextureMapSize;
} TTextureMap;

typedef struct
{
    TAnimatedTexture m_AnimatedTextures[AT_COUNT];
    int m_AnimatedTexturesCount;


    TTextureMap m_TextureMap;
        TField* m_Fields[TT_COUNT];
        int m_FieldsSize[TT_COUNT];

        TPoint2_c* m_Landscapes[LT_COUNT];
        int m_LandscapesSize[LT_COUNT];


} TTextures;

//

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
    GLuint ID;

    GLuint projectionLocation;
    GLuint modelLocation;
    GLuint viewLocation;

    GLuint vertexLocation;
    GLuint textureCoordsLocation;
    GLuint textureLocation;
    GLuint frameLocation;
    GLuint textureCoordScalePosLocation;
//    GLuint colorLightnessLocation;
//    GLuint isHoveredLocation;
//    GLuint strokeColorLocation;
} TOGLP_tile_anim;

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
    int m_IsPressed;
    char m_Text[20];


        TButtonDrawFunc m_Draw;
        TButtonDraw_txyFunc m_Draw_txy;

    TButtonEventFunc m_Event;

} TSimpleButton;



#endif // TYPES_H_INCLUDED
