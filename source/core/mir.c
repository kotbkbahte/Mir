#include "mir.h"

extern TState State;
extern TGameState GameState;
extern const TDrawState DrawStates[];
extern TToState ToState[];
extern TGameState GameState;

extern TOpenGLProgram_base m_GlProgram;
extern GLuint m_Textures[TEXTURES_COUNT];
extern GLuint m_GameTextures[TG_COUNT];

extern float m_ProjectionMatrix[16];
extern float m_ModelMatrix[16];
extern float m_ViewMatrix[16];
extern float m_TestMatrix[16];

void ToGame1() { ToGame(); GameState.m_PlayerID = 1; }
void ToGame2() { ToGame(); GameState.m_PlayerID = 2; }
void ToGame3() { ToGame(); GameState.m_PlayerID = 3; }


void InitGame()
{
    SetState(MAIN_MENU);

}

#define GAME_MAP_SIZE 10
void InitGameMap()
{
    GameState.m_GameMap.m_Size  = GAME_MAP_SIZE ;
    GameState.m_GameMap.m_Tiles = malloc(GAME_MAP_SIZE * GAME_MAP_SIZE * sizeof(TTile));
    GameState.m_GameMap.m_SelectedTile = -1;

    GenerateRandomMap();
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
    State.f_StateDraw       = DrawGame;

    InitGameMap();
}

void DrawGame()
{
    DrawMap();
    DrawGameGUI();

}

static void start_draw_tiles()
{
    glUseProgram(m_GlProgram.ID);

    float m[16];
    loadIdentity(m_ViewMatrix);
    matrixTranslate(m_ViewMatrix, -(float)GameState.m_GameMap.m_Size / 2.0f, -(float)GameState.m_GameMap.m_Size / 2.0f, 0.0);
    matrixScale(m_ViewMatrix, 0.05f, 0.05f, 1.0f);
    glUniformMatrix4fv(m_GlProgram.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(m_GlProgram.viewLocation, 1, GL_FALSE, m_ViewMatrix);

}

static void end_draw_tiles()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawMap()
{
    start_draw_tiles();

    int size = GameState.m_GameMap.m_Size;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            DrawTile(GameState.m_GameMap.m_Tiles + i + j * size, i, j);
        }
    }

    end_draw_tiles();

}

void DrawTile(TTile* tile, int x, int y)
{
    DrawSubTile(tile->m_SubTile[0].m_SubTileTexture, x,     y);
    DrawSubTile(tile->m_SubTile[1].m_SubTileTexture, x + 1, y);
    DrawSubTile(tile->m_SubTile[2].m_SubTileTexture, x + 1, y + 1);
    DrawSubTile(tile->m_SubTile[3].m_SubTileTexture, x,     y + 1);
}


const GLfloat textureCoordinates[] =
{
    1.0f, 1.0f,
    0, 1.0f,
    0, 0,
    1.0f, 0,
    -1, -1,
    -1,  1,
     1,  1,
     1, -1,
};
const GLfloat squareVertices[] = {
    1.0f, 1.0f, 2.0f,
    -1.0f, 1.0f, 2.0f,
    -1.0f, -1.0f, 2.0f,
    1.0f, -1.0f, 2.0f,
};


void DrawSubTile(int i, int x, int y)
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



void UpdateState(float dt)
{


}


void SetState(int i)
{
    if(i < 0)
        return;
    ToState[i]();
}
