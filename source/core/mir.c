#include "mir.h"

extern TState State;
extern TGameState GameState;
extern const TDrawState DrawStates[];
extern TToState ToState[];

extern TAnimations m_MirAnimations;
extern TMirTile* m_AnimatedTiles;
extern TTextures m_MirTextures;

extern TOpenGLProgram_base m_GlProgram;
extern TOpenGLProgram_color m_GlProgram_color;
extern TOGLP_tile_anim m_OGLP_anim;

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

void ToGame1()
{
    ToGame();
    GameState.m_PlayerID = 1;
}
void ToGame2()
{
    ToGame();
    GameState.m_PlayerID = 2;
}
void ToGame3()
{
    ToGame();
    GameState.m_PlayerID = 3;
}

#endif

char* _tile_types[] =
{
    [TT_PLAINS] = "Plains",
    [TT_SEA]    = "Sea",
    [TT_OCEAN]  = "Ocean",
};


const GLfloat textureCoordinates[] =
{
    1.0f, 1.0f,
    1.0f, 0,
    0, 0,
    0, 1.0f,
};

const GLfloat _textureCoordinates[] =
{
    1.0f, 1.0f,
    1.0f, 0,
    0, 0,
    0, 1.0f,
};

const GLfloat squareVertices[] =
{
    1.0f, 1.0f, 2.0f,
    -1.0f, 1.0f, 2.0f,
    -1.0f, -1.0f, 2.0f,
    1.0f, -1.0f, 2.0f,
};

const GLfloat square1x1[] =
{
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
};


void InitGame()
{
    SetState(MAIN_MENU);

}

#define GAME_MAP_SIZE 32
#define BUILDINGS_COUNT 10
#define LANDSCAPE_COUNT 100
#define TILE_SIZE 17
void InitGameMap()
{
    //

    GameState.m_MirMap.m_Size = GAME_MAP_SIZE;

    GameState.m_MirMap.m_Tiles  = malloc(GAME_MAP_SIZE * GAME_MAP_SIZE * sizeof(TMirTile));
    GameState.m_MirMap.m_Tiles1 = malloc(GAME_MAP_SIZE * GAME_MAP_SIZE * sizeof(TTile));


    GameState.m_MirMap.m_IsTileSelected = True;
    GameState.m_MirMap.m_SelectedTile.i = 0;
    GameState.m_MirMap.m_SelectedTile.j = 0;

//    GenerateRandomNoiseMirMap();
    GeneratePerlinNoiseMap();

    GameState.m_Landscapes = malloc(LANDSCAPE_COUNT * sizeof(TLandscape));
    GameState.m_LandscapesCount = LANDSCAPE_COUNT;
    GenerateRandomLandscape_();


    GameState.m_Buildings = malloc(BUILDINGS_COUNT * sizeof(TBuilding));
    GameState.m_BuildingsCount = BUILDINGS_COUNT;
//    GenerateRandomBuildings();



}

void InitFields()
{

}

void GenerateRandomNoiseMap()
{
    int size = GameState.m_MirMap.m_Size;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            TTile* tile = GameState.m_MirMap.m_Tiles1 + i + j * GAME_MAP_SIZE;
            int t = random_range(0, TT_COUNT);
            tile->m_TileType = t;


            tile->m_Field.i = t;
            tile->m_Field.j = random_range(0, m_MirTextures.m_FieldsSize[t]);


            tile->m_Landscape = -1;
            tile->m_Building  = -1;
            tile->m_Unit      = -1;
        }
    }
}

void GeneratePerlinNoiseMap()
{
    int seed = time(NULL);
    int size = GameState.m_MirMap.m_Size;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            TTile* tile      = GameState.m_MirMap.m_Tiles1 + i + j * GAME_MAP_SIZE;
            tile->m_TileType = perlin2d(i, j, 0.3, 2, seed);
//            print_i(tile->m_TileType);

            tile->m_Field.i = tile->m_TileType;
            tile->m_Field.j = random_range(0, m_MirTextures.m_FieldsSize[tile->m_TileType]);


            tile->m_Landscape = -1;
            tile->m_Building  = -1;
            tile->m_Unit      = -1;
        }
    }

    char test_map[size][size];
    int t;
    TTile* map = GameState.m_MirMap.m_Tiles1;


    for(int i = 1; i < size - 1; i++)
    {
        for(int j = 1; j < size - 1; j++)
        {
            TTile* tile = map + i + j * size;
            t = tile->m_TileType;
            test_map[i][j] = 0;
            if(t == TT_SEA)
            {
                int d = ( (tile + 1)->m_TileType        == TT_PLAINS ) ||
                        ( (tile - 1)->m_TileType        == TT_PLAINS ) ||
                        ( (tile + 1 * size)->m_TileType == TT_PLAINS ) ||
                        ( (tile - 1 * size)->m_TileType == TT_PLAINS );
                if(d)
                {
                    continue;
                }
                else
                {
                    test_map[i][j] = 1;
                }

            }
        }
    }

    for(int i = 1; i < size - 1; i++)
    {
        for(int j = 1; j < size - 1; j++)
        {
            if(test_map[i][j] == 1)
            {
                TTile* tile = GameState.m_MirMap.m_Tiles1 + i + j * GAME_MAP_SIZE;
                tile->m_TileType = TT_OCEAN;
                tile->m_Field.i = tile->m_TileType;
                tile->m_Field.j = random_range(0, m_MirTextures.m_FieldsSize[tile->m_TileType]);

            }
        }
    }

}



//void GenerateRandomLandscape()
//{
//    for(int i = 0; i < GameState.m_LandscapeCount; i++ )
//    {
//        int x = -1;
//        int y = -1;
//
//        do
//        {
//            x = random_range(0, GAME_MAP_SIZE);
//            y = random_range(0, GAME_MAP_SIZE);
//        } while(GameState.m_MirMap.m_Tiles[x + y * GAME_MAP_SIZE].m_Landscape != -1);
//
//#define land GameState.m_Landscape[i]
//        int t = random_range(0, LT_COUNT);
//
//        GameState.m_MirMap.m_Tiles[x + y * GAME_MAP_SIZE].m_Landscape = i;
//        land.m_Pos.x = x;
//        land.m_Pos.y = y;
//        land.m_Texture = m_LandscapeTextures[t];
//
//    }
//#undef land
//}

void GenerateRandomLandscape_()
{
#define land GameState.m_Landscapes[i]
    int size = GameState.m_MirMap.m_Size;
    for(int i = 0; i < GameState.m_LandscapesCount; i++ )
    {
        int x = -1;
        int y = -1;
        TTile* tile;

        do
        {
            x    = random_range(0, size);
            y    = random_range(0, size);
            tile = GameState.m_MirMap.m_Tiles1 + x + y * size;
        }
        while( (tile->m_Landscape == -1) &&  !(tile->m_TileType  == TT_PLAINS) ) ;

        int t = perlin2d(i, 0, 0.2, 5, size);

        tile->m_Landscape = t;

        land.m_Pos.x = x;
        land.m_Pos.y = y;
        land.m_Texture.i = t;
        land.m_Texture.j = random_range(0, m_MirTextures.m_LandscapesSize[t]);

    }
#undef land



}

//void GenerateRandomBuildings()
//{
//    for(int i = 0; i < GameState.m_BuildingsCount; i++ )
//    {
//        int x = -1;
//        int y = -1;
//        TMirTile* tile = NULL;
//        do
//        {
//            x = random_range(0, GAME_MAP_SIZE);
//            y = random_range(0, GAME_MAP_SIZE);
//            tile = GameState.m_MirMap.m_Tiles + x + y * GAME_MAP_SIZE;
//        } while( (tile->m_Building  != -1) &&
//                 (tile->m_Landscape == -1));
//
//#define b GameState.m_Buildings[i]
//        int t = random_range(0, BT_COUNT);
//
//        tile->m_Building = i;
//        b.m_Pos.x = x;
//        b.m_Pos.y = y;
//        b.m_Offset.x = 0;
//        b.m_Offset.y = 0;
//        b.m_Texture = m_BuildingTextures[t];
//
//        switch (t)
//        {
//        case BT_TOWER:
//            {
//                b.m_Offset.x = random_range(0, 5);
//            } break;
//        }
//    }
//#undef b
//}

//void GenerateRandomNoiseMirMap()
//{
//    int size = GameState.m_MirMap.m_Size;
//    for(int i = 0; i < size; i++)
//    {
//        for(int j = 0; j < size; j++)
//        {
//            TMirTile* tile = GameState.m_MirMap.m_Tiles1 + i + j * GAME_MAP_SIZE;
//            int t = random_range(0, FT_COUNT);
//            if( (t+1) == FT_COUNT)
//                tile->m_Texture = -23;
//            else
//                tile->m_Texture = m_FieldTextures[t];
//
//
//
//            tile->m_Landscape = -1;
//            tile->m_Building  = -1;
//            tile->m_Unit      = -1;
//        }
//    }
//}



void ToGame()
{
    State.m_StateIndex = GAME;
    State.f_StateDraw       = DrawGame;

    State.f_MouseDownEvent  = game_MouseDown;
    State.f_MouseUpEvent    = game_MouseUp;
    State.f_MouseMoveEvent  = game_MouseMove;
    State.f_MouseClickEvent = gui_MouseClick;

    State.f_KeyboardPress   = game_PressKeyboard;

    InitGameMap();
}


static void start_draw_tiles()
{
#define program m_OGLP_anim

    glUseProgram(program.ID);

//    loadIdentity(m_ViewMatrix);
    float offset = (float)(-GameState.m_MirMap.m_Size / 2);
//    matrixTranslate(m_ViewMatrix, offset, offset, 0.0);
//    matrixScale(m_ViewMatrix, 0.1f, 0.1f, 1.0f);
    glUniformMatrix4fv(program.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(program.viewLocation, 1, GL_FALSE, m_ViewMatrix);

    glBindTexture(GL_TEXTURE_2D, m_MirTextures.m_TextureMap.m_Texture);

    glVertexAttribPointer(program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0, square1x1);
    glEnableVertexAttribArray(program.vertexLocation);


#undef program
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

    start_draw_tiles();
        DrawMirMap_();
        DrawMirLandscape_();
    end_draw_tiles();



//    _start_draw_tiles();
//        DrawMirMap();
//        DrawMirLandscape();
//        DrawMirBuildings();
//        DrawMirUnit();
//    _end_draw_tiles();


    DrawMirSelectedTile();

    DrawGameGUI();

}

void DrawMirUnit()
{
    return;
}



void DrawMirMap_()
{
    int size = GameState.m_MirMap.m_Size;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            TPoint2_c texture = GameState.m_MirMap.m_Tiles1[i + j * size].m_Field;
            DrawMirTile_(m_MirTextures.m_Fields[(int)texture.i][(int)texture.j], i, j, 3);
        }
    }
}

void DrawMirLandscape_()
{
    for(int i = 0; i < GameState.m_LandscapesCount; i++)
    {
        TLandscape* land = GameState.m_Landscapes + i;
        TPoint2_c texture = land->m_Texture;
        DrawMirTile_(m_MirTextures.m_Landscapes[(int)texture.i][(int)texture.j], land->m_Pos.x, land->m_Pos.y, 4);
    }
}

void DrawMirTile_(TPoint2_c texture, int i, int j, int layer)
{
#define program m_OGLP_anim

    loadIdentity(m_ModelMatrix);
    matrixTranslate(m_ModelMatrix, (float)i, (float)j, (float)layer);
    glUniformMatrix4fv(program.modelLocation, 1, GL_FALSE, m_ModelMatrix);

    TPoint2_c t = texture;
    int x = t.y;
    int y = t.x;

    GLfloat _1textureCoordinates[] =
    {
        (1.0f + x) / 8.0f,   (1.0f + y) / 8.0f,
        (1.0f + x) / 8.0f,   ((float)y) / 8.0f,
        ((float)x) / 8.0f,   ((float)y) / 8.0f,
        ((float)x) / 8.0f,   (1.0f + y) / 8.0f,
    };

    glVertexAttribPointer(program.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, _1textureCoordinates);
    glEnableVertexAttribArray(program.textureCoordsLocation);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

#undef program
}




void DrawMirMap()
{

    int size = GameState.m_MirMap.m_Size;


    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(GameState.m_MirMap.m_Tiles[i + j * size].m_Texture == -23)
            {
                DrawMirTileAnimated(m_MirAnimations.m_TextureAnimations[ (i+j*size) % 8 ].m_AnimatedTexture->m_Texture,
                                    m_MirAnimations.m_TextureAnimations[ (i+j*size) % 8 ].m_Frame, i, j, 3);
                continue;
            }

            DrawMirTile(GameState.m_MirMap.m_Tiles[i + j * size].m_Texture, i, j, 3);
        }
    }

}

void DrawMirSelectedTile()
{
    if(!GameState.m_MirMap.m_IsTileSelected)
        return;
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


    glVertexAttribPointer(program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0, square1x1);
    glEnableVertexAttribArray(program.vertexLocation);

    glVertexAttribPointer(program.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(program.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
#undef program
}
//
//void DrawMirBuildingOffset(TBuilding* b)
//{
//#define program m_GlProgram
//    glBindTexture(GL_TEXTURE_2D, b->m_Texture);
//
//    loadIdentity(m_ModelMatrix);
//
//    matrixTranslate(m_ModelMatrix,
//                    (float)(b->m_Pos.x) + (float)(b->m_Offset.x) / TILE_SIZE,
//                    (float)(b->m_Pos.y) + (float)(b->m_Offset.y) / TILE_SIZE,
//                    4.0);
//
//    glUniformMatrix4fv(program.modelLocation, 1, GL_FALSE, m_ModelMatrix);
//
//
//    glVertexAttribPointer(program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0 , square1x1);
//    glEnableVertexAttribArray(program.vertexLocation);
//
//    glVertexAttribPointer(program.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
//    glEnableVertexAttribArray(program.textureCoordsLocation);
//
//
//    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//#undef program
//}



void DrawMirTileAnimated(int texture, int frame, int i, int j, int layer)
{
    float tmp[16];
#define program m_OGLP_anim


//    glUseProgram(program.ID);
//
//    loadIdentity(m_ViewMatrix);
//    float offset = (float)(-GameState.m_MirMap.m_Size / 2);
//    matrixTranslate(m_ViewMatrix, offset, offset, 0.0);
//    glUniformMatrix4fv(program.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
//    glUniformMatrix4fv(program.viewLocation, 1, GL_FALSE, m_ViewMatrix);


    glBindTexture(GL_TEXTURE_2D, texture);

    loadIdentity(m_ModelMatrix);

    matrixTranslate(m_ModelMatrix, (float)i, (float)j, (float)layer);
    glUniformMatrix4fv(program.modelLocation, 1, GL_FALSE, m_ModelMatrix);

//    loadIdentity(tmp);
//    matrixScale(tmp, 1/8.0f, 1.0f, 0.0f);

//    if(kb_GetKeyDown(SDL_SCANCODE_0)) { matrixTranslate(tmp, 1.0, 1.0f, 1.0f); }
//    else { glVertexAttribPointer( matrixTranslate(tmp, 0.0, 1.0f, 0.0f); }
    GLfloat _1textureCoordinates[] =
    {
        1.0f / 8.0f + ((float)frame) / 8.0f, 1.0f,
        1.0f / 8.0f + ((float)frame) / 8.0f, 0.0f,
        0.0f + ((float)frame) / 8.0f, 0.0f,
        0.0f + ((float)frame) / 8.0f, 1.0f,
    };


//    glUniform1f(program.frameLocation, (float)frame);

//    glUniformMatrix4fv(program.textureCoordScalePosLocation, 1, GL_FALSE, tmp);

    glVertexAttribPointer(program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0, square1x1);
    glEnableVertexAttribArray(program.vertexLocation);

    if(kb_GetKeyDown(SDL_SCANCODE_0))
    {
        glVertexAttribPointer(program.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, _textureCoordinates);
    }
    else
    {
        glVertexAttribPointer(program.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, _1textureCoordinates);
    }


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

    glVertexAttribPointer(program.vertexLocation, 2, GL_FLOAT, GL_FALSE, 0, square1x1);
    glEnableVertexAttribArray(program.vertexLocation);

    glVertexAttribPointer(program.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(program.textureCoordsLocation);

//    glBindTexture(GL_TEXTURE_2D, tile->m_Landscape);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

#undef program
}

//void DrawMirBuildings()
//{
//    for(int i = 0; i < GameState.m_BuildingsCount; i++)
//    {
//        TBuilding* b = GameState.m_Buildings + i;
//        DrawMirBuildingOffset(b);
//    }
//}

//void DrawMirLandscape()
//{
//    for(int i = 0; i < GameState.m_LandscapeCount; i++)
//    {
//        TLandscape* land = GameState.m_Landscape + i;
//        DrawMirTile(land->m_Texture, land->m_Pos.x, land->m_Pos.y, 4);
//
//    }
//}




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


    glVertexAttribPointer(m_GlProgram.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, squareVertices);
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


    glVertexAttribPointer(m_GlProgram.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, squareVertices);
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


    glVertexAttribPointer(m_GlProgram.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, squareVertices);
    glEnableVertexAttribArray(m_GlProgram.vertexLocation);

    glVertexAttribPointer(m_GlProgram.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(m_GlProgram.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}



void UpdateState(float dt)
{
    static int i = 0;
    i++;
    if(i == 5)
    {
        UpdateAnimations(dt);
        i = 0;
    }

//    printf("%d\n", m_MirAnimations.m_TextureAnimations[0]->m_Frame);

}


void SetState(int i)
{
    if(i < 0)
        return;
    ToState[i]();
}

void game_MouseMove(int x, int y)
{

    if(GameState.m_IsCameraCaptured)
    {
        double ox, oy, oz;
        ClientToOpenGL(x, y, &ox, &oy,&oz);
        float x = ox - GameState.m_CameraCapturedPos.x;
        float y = oy - GameState.m_CameraCapturedPos.y;

        matrixTranslate(m_ViewMatrix, x, y, 0.0f);
    }
}



void game_MouseDown(int x, int y, int button)
{
//    GLuint index;
//    int vp[4];
//    glGetIntegerv(GL_VIEWPORT, vp);
//    glReadPixels(x, vp[3] - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

//    if (State.m_StateIndex == GAME)
//    {
//        print_2i(x, y);
//    }

    double ox, oy, oz;
    ClientToOpenGL(x, y, &ox, &oy,&oz);
//    print_3d(ox, oy, oz);

    if(button == SDL_BUTTON_RIGHT)
    {
        GameState.m_IsCameraCaptured = True;
        GameState.m_CameraCapturedPos = (TPoint2_f){.x = ox, .y = oy};

    }


}

void game_MouseUp(int x, int y, int button)
{
    if(button == SDL_BUTTON_RIGHT)
    {
        GameState.m_IsCameraCaptured = False;
    }
}


void game_PressKeyboard(SDL_Keycode code)
{
    switch(code)
    {
    case SDLK_p:
        PrintBuildingsMap();
        PrintLandscapeMap();
        break;
    case SDLK_SPACE:
        GameState.m_MirMap.m_IsTileSelected = !GameState.m_MirMap.m_IsTileSelected;
        break;
    case SDLK_r:
        GenerateRandomLandscape_();
        break;
    case SDLK_m:
        GeneratePerlinNoiseMap();
        break;
    case SDLK_i:
    {
        int x = GameState.m_MirMap.m_SelectedTile.i;
        int y = GameState.m_MirMap.m_SelectedTile.j;
        printf("%s\n",  _tile_types[GameState.m_MirMap.m_Tiles1[x + y * GameState.m_MirMap.m_Size].m_TileType] );
    }
    break;

    default:
        break;
    }


    int i = (code == SDLK_d) - (code == SDLK_a);
    int j = (code == SDLK_w) - (code == SDLK_s);


    unsigned int t = GameState.m_MirMap.m_SelectedTile.i + i;
    GameState.m_MirMap.m_SelectedTile.i =
        ( (t) < GameState.m_MirMap.m_Size )
        ?  t : GameState.m_MirMap.m_SelectedTile.i;
    t = GameState.m_MirMap.m_SelectedTile.j + j;
    GameState.m_MirMap.m_SelectedTile.j =
        ( (t) < GameState.m_MirMap.m_Size )
        ?  t : GameState.m_MirMap.m_SelectedTile.j;

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

