#include "gui.h"

extern TState State;
extern TGameState GameState;
extern TSimpleButton* Simple_Buttons;
extern GLuint m_Textures[];
extern TOpenGLProgram_button m_GlProgram_button;
extern TOpenGLProgram_base m_GlProgram;
extern float m_ProjectionMatrix[16];
extern float m_ViewMatrix[16];
extern float m_IdentityMatrix[16];


const TButtonEventFunc ButtonEventFuncs[] = {ToMainMenu, ToStartMenu, ToSettingsMenu, GoBackMenu, ToQuit, PassButtonEvent, ToGame };// , ToQuit};//, DrawTextMenu, DrawGame, DrawGameMenu, DrawResearchTree};
const TButtonDrawFunc ButtonDrawFuncs[] = {draw_simple_button_t, draw_simple_button_t_stroke, draw_simple_button_t1};

static const GLfloat textureCoordinates[] =
{
    1.0f, 1.0f,
    0, 1.0f,
    0, 0,
    1.0f, 0
};

static const GLfloat textureCoordinates_flipped[] =
{
    1.0f, 0,
    0, 0,
    0, 1.0f,
    1.0f, 1.0f,
};

static const GLfloat squareVertices[] = {
    0.5f, 0.5f, 2.0f,
    -0.5f, 0.5f, 2.0f,
    -0.5f, -0.5f, 2.0f,
    0.5f, -0.5f, 2.0f,
};



// States {MAIN_MENU, START_MENU, SETTINGS_MENU, QUIT, TEST_MENU, GAME, GAME_MENU, RESEARCH_TREE, STATES_COUNT};

const int BackStates[]   = {-1, MAIN_MENU, MAIN_MENU, -1, SETTINGS_MENU, START_MENU };
const TToState ToState[] = {ToMainMenu, ToStartMenu, ToSettingsMenu, ToGame};

int ids[10];

int id_queue = 0;

void SetupGUI()
{
    SetupMainMenu();
    SetupSettingsMenu();
    SetupStartMenu();
    SetupGameMenu();

    SetBgImage(m_Textures[BACKGROUND_IMAGE_SPACE]);

}

void CloseGUI()
{
    CloseMainMenu();
}

void DrawGuiColor()
{

}

void SetBgImage(int texture_id)
{
    GameState.m_Background_image = texture_id;

    int w , h;
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);


    GameState.m_BackgroundSize.x = w;
    GameState.m_BackgroundSize.y = h;
}


void DrawBackground()
{
    glBindTexture(GL_TEXTURE_2D, GameState.m_Background_image);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_GlProgram.ID);
    float k = 720.0f / 1280.0f;
    loadIdentity(m_ViewMatrix);
    matrixScale(m_ViewMatrix,  2 * GameState.m_BackgroundSize.x / 1280.0f / k, 2 * GameState.m_BackgroundSize.y / 720.0f , 1.0f);

    glUniformMatrix4fv(m_GlProgram.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);

    // Remove shit down below
    glUniformMatrix4fv(m_GlProgram.modelLocation, 1, GL_FALSE, m_IdentityMatrix );
    glUniformMatrix4fv(m_GlProgram.viewLocation, 1, GL_FALSE, m_ViewMatrix );


    glVertexAttribPointer(m_GlProgram_button.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram_button.vertexLocation);

    glVertexAttribPointer(m_GlProgram_button.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates_flipped);
    glEnableVertexAttribArray(m_GlProgram_button.textureCoordsLocation);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}



void GoBackMenu()
{
    SetState(BackStates[State.m_StateIndex]);
}

void ChangeBgColor()
{
    GameState.m_BgColor.r = (float)rand() / (float)RAND_MAX;
    GameState.m_BgColor.g = (float)rand() / (float)RAND_MAX;
    GameState.m_BgColor.b = (float)rand() / (float)RAND_MAX;
}


void gui_MouseClick(int x, int y)
{
    if(State.m_HoveredButton != -1)
    {
        Simple_Buttons[State.m_HoveredButton].m_Event();
    }
}

void gui_MouseMove(int x ,int y)
{
    GLuint index;
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);

    glReadPixels(x, vp[3] - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    index-=1;

    if(State.m_HoveredButton != -1)
        Simple_Buttons[State.m_HoveredButton].m_IsHovered = False;
    State.m_HoveredButton = index;
    Simple_Buttons[State.m_HoveredButton].m_IsHovered = True;
}

