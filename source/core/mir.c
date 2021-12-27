#include "mir.h"

extern TState State;
extern TGameState GameState;
extern const TDrawState DrawStates[];
extern TToState ToState[];

extern TOpenGLProgram_base m_GlProgram;
extern TOpenGLProgram_color m_GlProgram_color;

extern GLuint m_Textures[TEXTURES_COUNT];
extern GLuint m_GameTextures[TG_COUNT];
extern GLuint m_FieldTextures[FT_COUNT];
extern GLuint m_BuildingTextures[BT_COUNT];
extern GLuint m_LandscapeTextures[LT_COUNT];

extern float m_ProjectionMatrix[16];
extern float m_IdentityMatrix[16];
extern float m_ModelMatrix[16];
extern float m_ViewMatrix[16];
extern float m_TestMatrix[16];

// What is the best way? Both sucks
#if 1
    #define def void
    #define _ToGame(i) ToGame ## i()       \
    {                                      \
        ToGame();                          \
        GameState.m_PlayerID = i;          \
    }
def _ToGame(1)
def _ToGame(2)
def _ToGame(3)
#undef def

#else

void ToGame1() { ToGame(); GameState.m_PlayerID = 1; }
void ToGame2() { ToGame(); GameState.m_PlayerID = 2; }
void ToGame3() { ToGame(); GameState.m_PlayerID = 3; }

#endif



const GLfloat textureCoordinates[] =
{
    1.0f, 1.0f,
    1.0f, 0,
    0, 0,
    0, 1.0f,
};
const GLfloat squareVertices[] = {
    1.0f, 1.0f, 2.0f,
    -1.0f, 1.0f, 2.0f,
    -1.0f, -1.0f, 2.0f,
    1.0f, -1.0f, 2.0f,
};

const GLfloat square1x1[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
};


void InitGame()
{
    SetState(MAIN_MENU);

}

#define GAME_MAP_SIZE 10
#define BUILDINGS_COUNT 10
#define LANDSCAPE_COUNT 10
#define TILE_SIZE 17
void InitGameMap()
{
    GameState.m_GameMap.m_Size  = GAME_MAP_SIZE;
    GameState.m_GameMap.m_Tiles = malloc(GAME_MAP_SIZE * GAME_MAP_SIZE * sizeof(TTile));

    GameState.m_GameMap.m_IsTileSelected = True;
    GameState.m_GameMap.m_SelectedTile.i = 0;
    GameState.m_GameMap.m_SelectedTile.j = 0;

    GenerateRandomMap();
    //

    GameState.m_MirMap.m_Size = GAME_MAP_SIZE;
    GameState.m_MirMap.m_Tiles = malloc(GAME_MAP_SIZE * GAME_MAP_SIZE * sizeof(TTile));

    GameState.m_MirMap.m_IsTileSelected = True;
    GameState.m_MirMap.m_SelectedTile.i = 0;
    GameState.m_MirMap.m_SelectedTile.j = 0;
    GenerateRandomNoiseMirMap();


    GameState.m_Landscape = malloc(LANDSCAPE_COUNT * sizeof(TLandscape));
    GameState.m_LandscapeCount = LANDSCAPE_COUNT;
    GenerateRandomLandscape();

    GameState.m_Buildings = malloc(BUILDINGS_COUNT * sizeof(TBuilding));
    GameState.m_BuildingsCount = BUILDINGS_COUNT;
    GenerateRandomBuildings();


}

void PrintBuildingsMap()
{
    printf("## BUILDINGS ##\n");
    for(int i = 0; i < GAME_MAP_SIZE; i++)
    {
        for(int j = 0; j < GAME_MAP_SIZE; j++)
        {
            printf("%d", (GameState.m_MirMap.m_Tiles[i + j * GAME_MAP_SIZE].m_Building >= 0) ? 1 : 0 );
        }
        printf("\n");
    }
    printf("## ##\n");
}

void PrintLandscapeMap()
{
    printf("## LANDSCAPE ##\n");
    for(int i = 0; i < GAME_MAP_SIZE; i++)
    {
        for(int j = 0; j < GAME_MAP_SIZE; j++)
        {
            printf("%d", (GameState.m_MirMap.m_Tiles[i + j * GAME_MAP_SIZE].m_Landscape >= 0) ? 1 : 0 );
        }
        printf("\n");
    }
    printf("## ##\n");
}

void GenerateRandomLandscape()
{
    for(int i = 0; i < GameState.m_LandscapeCount; i++ )
    {
        int x = -1;
        int y = -1;

        do
        {
            x = random_range(0, GAME_MAP_SIZE);
            y = random_range(0, GAME_MAP_SIZE);
        } while(GameState.m_MirMap.m_Tiles[x + y * GAME_MAP_SIZE].m_Landscape != -1);

#define land GameState.m_Landscape[i]
        int t = random_range(0, LT_COUNT);

        GameState.m_MirMap.m_Tiles[x + y * GAME_MAP_SIZE].m_Landscape = i;
        land.m_Pos.x = x;
        land.m_Pos.y = y;
        land.m_Texture = m_LandscapeTextures[t];

    }
#undef land
}

void GenerateRandomBuildings()
{
    for(int i = 0; i < GameState.m_BuildingsCount; i++ )
    {
        int x = -1;
        int y = -1;
        TMirTile* tile = NULL;
        do
        {
            x = random_range(0, GAME_MAP_SIZE);
            y = random_range(0, GAME_MAP_SIZE);
            tile = GameState.m_MirMap.m_Tiles + x + y * GAME_MAP_SIZE;
        } while( (tile->m_Building  != -1) &&
                 (tile->m_Landscape == -1));

#define b GameState.m_Buildings[i]
        int t = random_range(0, BT_COUNT);

        tile->m_Building = i;
        b.m_Pos.x = x;
        b.m_Pos.y = y;
        b.m_Offset.x = 0;
        b.m_Offset.y = 0;
        b.m_Texture = m_BuildingTextures[t];

        switch (t)
        {
        case BT_TOWER:
            {
                b.m_Offset.x = random_range(0, 5);
            } break;
        }
    }
#undef b
}

void GenerateRandomNoiseMirMap()
{
    int size = GameState.m_MirMap.m_Size;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            TMirTile* tile = GameState.m_MirMap.m_Tiles + i + j * GAME_MAP_SIZE;
            int t = random_range(0, FT_COUNT);
            tile->m_Texture = m_FieldTextures[t];
            tile->m_Landscape = -1;
            tile->m_Building  = -1;
            tile->m_Unit      = 0;
        }
    }
}

void GenerateRandomMap()
{
    int size = GameState.m_GameMap.m_Size;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            FillTileRandom(GameState.m_GameMap.m_Tiles + i + j * size);

        }
    }
}

void FillTileRandom(TTile* tile)
{
    int arr[3] = {TG_GRASS_DARK, TG_GRASS_LIGHT, TG_BLUE};
    tile->m_SubTile[0].m_SubTileTexture = m_GameTextures[choice_i_arr(3, arr)];
    tile->m_SubTile[1].m_SubTileTexture = m_GameTextures[choice_i_arr(3, arr)];
    tile->m_SubTile[2].m_SubTileTexture = m_GameTextures[choice_i_arr(3, arr)];
    tile->m_SubTile[3].m_SubTileTexture = m_GameTextures[choice_i_arr(3, arr)];
}


void ToGame()
{
    State.m_StateIndex = GAME;
    State.f_MouseClickEvent = gui_MouseClick;
    State.f_MouseMoveEvent  = gui_MouseMove;

    State.f_StateDraw       = DrawGame; //DrawGame;

    State.f_KeyboardPress   = game_PressKeyboard;

    InitGameMap();
}


static void start_draw_tiles()
{
    glUseProgram(m_GlProgram.ID);

    loadIdentity(m_ViewMatrix);
    matrixTranslate(m_ViewMatrix, 1.0f, 1.0f, 0.0);
    matrixScale(m_ViewMatrix, 0.1f, 0.1f, 1.0f);
    glUniformMatrix4fv(m_GlProgram.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(m_GlProgram.viewLocation, 1, GL_FALSE, m_ViewMatrix);
}

static void end_draw_tiles()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

static void _start_draw_tiles()
{
    glUseProgram(m_GlProgram.ID);

    loadIdentity(m_ViewMatrix);
    float offset = (float)(-GameState.m_MirMap.m_Size / 2);
    matrixTranslate(m_ViewMatrix, offset, offset, 0.0);
    glUniformMatrix4fv(m_GlProgram.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(m_GlProgram.viewLocation, 1, GL_FALSE, m_ViewMatrix);

}

static void _end_draw_tiles()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawGame()
{
    //DrawMap();

    _start_draw_tiles();
        DrawMirMap();
        DrawMirLandscape();
        DrawMirBuildings();
        DrawMirSelectedTile();
    _end_draw_tiles();


    DrawGameGUI();

}


void DrawMirMap()
{

    int size = GameState.m_MirMap.m_Size;


    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            DrawMirTile(GameState.m_MirMap.m_Tiles[i + j * size].m_Texture, i, j, 3);
        }
    }

}

void DrawMirSelectedTile()
{
    int x = GameState.m_MirMap.m_SelectedTile.i;
    int y = GameState.m_MirMap.m_SelectedTile.j;

    DrawMirTile(m_GameTextures[TG_SELECTED_1], x, y, 5);
}


void DrawMirTile(int texture, int i, int j, int layer)
{
#define program m_GlProgram
    glBindTexture(GL_TEXTURE_2D, texture);

    loadIdentity(m_ModelMatrix);

    matrixTranslate(m_ModelMatrix, (float)i, (float)j, (float)layer);
    glUniformMatrix4fv(program.modelLocation, 1, GL_FALSE, m_ModelMatrix);


    glVertexAttribPointer(program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , square1x1);
    glEnableVertexAttribArray(program.vertexLocation);

    glVertexAttribPointer(program.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(program.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
#undef program
}

void DrawMirBuildingOffset(TBuilding* b)
{
#define program m_GlProgram
    glBindTexture(GL_TEXTURE_2D, b->m_Texture);

    loadIdentity(m_ModelMatrix);

    matrixTranslate(m_ModelMatrix,
                    (float)(b->m_Pos.x) + (float)(b->m_Offset.x) / TILE_SIZE,
                    (float)(b->m_Pos.y) + (float)(b->m_Offset.y) / TILE_SIZE,
                    4.0);

    glUniformMatrix4fv(program.modelLocation, 1, GL_FALSE, m_ModelMatrix);


    glVertexAttribPointer(program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , square1x1);
    glEnableVertexAttribArray(program.vertexLocation);

    glVertexAttribPointer(program.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(program.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
#undef program
}



void DrawMirTileSelected(int texture, int i, int j, int layer)
{
#define program m_GlProgram
    glBindTexture(GL_TEXTURE_2D, texture);

    loadIdentity(m_ModelMatrix);

    matrixTranslate(m_ModelMatrix, (float)i, (float)j, 3.0);
    glUniformMatrix4fv(program.modelLocation, 1, GL_FALSE, m_ModelMatrix);

    glVertexAttribPointer(program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , square1x1);
    glEnableVertexAttribArray(program.vertexLocation);

    glVertexAttribPointer(program.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(program.textureCoordsLocation);

//    glBindTexture(GL_TEXTURE_2D, tile->m_Landscape);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

#undef program
}

void DrawMirBuildings()
{
    for(int i = 0; i < GameState.m_BuildingsCount; i++)
    {
        TBuilding* b = GameState.m_Buildings + i;
        DrawMirBuildingOffset(b);
    }
}

void DrawMirLandscape()
{
    for(int i = 0; i < GameState.m_LandscapeCount; i++)
    {
        TLandscape* land = GameState.m_Landscape + i;
        DrawMirTile(land->m_Texture, land->m_Pos.x, land->m_Pos.y, 4);

    }
}



void DrawMap()
{
    float fsize = (float)GameState.m_GameMap.m_Size;
    float tmp  = fsize / 2;
    float ntmp = -tmp;
    int size = GameState.m_GameMap.m_Size;

    start_draw_tiles();


        int i = 0, j = 0;
        for(float fi = ntmp; fi < tmp; fi += 1.0f)
        {
            j=0;
            for(float fj = ntmp; fj < tmp; fj += 1.0f)
            {
                DrawTile(GameState.m_GameMap.m_Tiles + i + j * size, fi * 4 , fj * 4);
                j++;
            }
            i++;
        }




    float a = ntmp + 1.0f * (float)GameState.m_GameMap.m_SelectedTile.i;
    float b = ntmp + 1.0f * (float)GameState.m_GameMap.m_SelectedTile.j;
//    print_f(a);
//    print_f(b);
    DrawSelectedTile(GameState.m_GameMap.m_Tiles + GameState.m_GameMap.m_SelectedTile.i + GameState.m_GameMap.m_SelectedTile.j * size,
                     a * 4.0f,
                     b * 4.0f);


    end_draw_tiles();
}



void DrawTile(TTile* tile, float x, float y)
{

    DrawSubTile(tile->m_SubTile[0].m_SubTileTexture, x,       y);
    DrawSubTile(tile->m_SubTile[1].m_SubTileTexture, x + 2.0, y);
    DrawSubTile(tile->m_SubTile[2].m_SubTileTexture, x + 2.0, y + 2.0);
    DrawSubTile(tile->m_SubTile[3].m_SubTileTexture, x,       y + 2.0);
}

void DrawSelectedTile(TTile* tile, float x, float y)
{
    DrawSubTile_xyz(tile->m_SubTile[0].m_SubTileTexture, x,       y, 5.0f);
    DrawSubTile_xyz(tile->m_SubTile[1].m_SubTileTexture, x + 2.0, y, 5.0f);
    DrawSubTile_xyz(tile->m_SubTile[2].m_SubTileTexture, x + 2.0, y + 2.0, 5.0f);
    DrawSubTile_xyz(tile->m_SubTile[3].m_SubTileTexture, x,       y + 2.0, 5.0f);
    DrawSquare_xyz_rgb(x, y, 4.0f, 0.5f, 0.1f, 0.5f);
}


void DrawSquare_xyz_rgb(float x, float y, float z, float r, float g, float b)
{
#define program
    glUseProgram(m_GlProgram.ID);

    loadIdentity(m_ViewMatrix);
//    matrixTranslate(m_ViewMatrix, 0.5f, 0.5f, 0.0);
    matrixScale(m_ViewMatrix, 0.1f, 0.1f, 1.0f);
    glUniformMatrix4fv(m_GlProgram.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(m_GlProgram.viewLocation, 1, GL_FALSE, m_ViewMatrix);


    glBindTexture(GL_TEXTURE_2D, m_GameTextures[TG_SELECTED]);

    loadIdentity(m_ModelMatrix);

    matrixScale(m_ModelMatrix, 2.25f, 2.25f, 1.0f);
    matrixTranslate(m_ModelMatrix, x + 2.0f, y + 2.0f, z);
    glUniformMatrix4fv(m_GlProgram.modelLocation, 1, GL_FALSE, m_ModelMatrix);


    glVertexAttribPointer(m_GlProgram.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram.vertexLocation);

    glVertexAttribPointer(m_GlProgram.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(m_GlProgram.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
#undef program
}


void DrawSubTile(int i, float x, float y)
{
    glBindTexture(GL_TEXTURE_2D, i);

    loadIdentity(m_ModelMatrix);

    matrixTranslate(m_ModelMatrix, x, y, 0.0);
    glUniformMatrix4fv(m_GlProgram.modelLocation, 1, GL_FALSE, m_ModelMatrix);


    glVertexAttribPointer(m_GlProgram.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram.vertexLocation);

    glVertexAttribPointer(m_GlProgram.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(m_GlProgram.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void DrawSubTile_xyz(int i, float x, float y, float z)
{
    glBindTexture(GL_TEXTURE_2D, i);

    loadIdentity(m_ModelMatrix);

    matrixTranslate(m_ModelMatrix, x, y, z);
    glUniformMatrix4fv(m_GlProgram.modelLocation, 1, GL_FALSE, m_ModelMatrix);


    glVertexAttribPointer(m_GlProgram.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram.vertexLocation);

    glVertexAttribPointer(m_GlProgram.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(m_GlProgram.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}


void UpdateState(float dt)
{
    //gui_MouseMove();

}


void SetState(int i)
{
    if(i < 0)
        return;
    ToState[i]();
}

void game_PressKeyboard(SDL_Keycode code)
{
    switch(code)
    {
    case SDLK_p:
        PrintBuildingsMap();
        PrintLandscapeMap();
        break;
    default:
        break;
    }

    int i = (code == SDLK_d) - (code == SDLK_a);
    int j = (code == SDLK_w) - (code == SDLK_s);

    GameState.m_GameMap.m_SelectedTile.i =
        ( (GameState.m_GameMap.m_SelectedTile.i + i) < GameState.m_GameMap.m_Size )
        ?  GameState.m_GameMap.m_SelectedTile.i + i : GameState.m_GameMap.m_SelectedTile.i;
    GameState.m_GameMap.m_SelectedTile.j =
        ( (GameState.m_GameMap.m_SelectedTile.j + j) < GameState.m_GameMap.m_Size )
        ?  GameState.m_GameMap.m_SelectedTile.j + j : GameState.m_GameMap.m_SelectedTile.j;

    GameState.m_MirMap.m_SelectedTile.i = GameState.m_GameMap.m_SelectedTile.i;
    GameState.m_MirMap.m_SelectedTile.j = GameState.m_GameMap.m_SelectedTile.j;



}

