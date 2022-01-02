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
extern float m_ModelMatrix[16];

extern int Running;

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
    glUseProgram(m_GlProgram.ID);

// TODO (kotbkbahte#1#): Fix matrises, to avoid scaling background
    float m[16];
    float n[16];
    loadIdentity(m);
    loadIdentity(n);
    float k = 720.0f / 1280.0f;
    matrixScale(m,  GameState.m_BackgroundSize.width / 1280.0f / k, GameState.m_BackgroundSize.height / 720.0f , 1.0f);

    glUniformMatrix4fv(m_GlProgram.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(m_GlProgram.modelLocation, 1, GL_FALSE,  m);
    glUniformMatrix4fv(m_GlProgram.viewLocation, 1, GL_FALSE, n);


    glVertexAttribPointer(m_GlProgram.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram.vertexLocation);

    glVertexAttribPointer(m_GlProgram.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates_flipped);
    glEnableVertexAttribArray(m_GlProgram.textureCoordsLocation);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);

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


void gui_MouseDown(int x, int y, int button)
{
    if(button == SDL_BUTTON_LEFT)
    {
        if(State.m_HoveredButton != -1)
        {
            Simple_Buttons[State.m_HoveredButton].m_IsPressed = True;
            State.m_PressedButton = State.m_HoveredButton;
        }
    }
}

void gui_MouseUp(int x, int y, int button)
{
    if(button == SDL_BUTTON_LEFT)
    {
        if( (State.m_PressedButton == gui_GetHoveredButtonID(x, y)) && (State.m_PressedButton != -1)  )
        {
            Simple_Buttons[State.m_PressedButton].m_Event();
        }
//        print_i(State.m_PressedButton);
//        printf("%s\n", Simple_Buttons[State.m_PressedButton].m_Text );
        Simple_Buttons[State.m_PressedButton].m_IsPressed = False;
        State.m_PressedButton = -1;
    }


}

void gui_MouseClick(int x, int y)
{
    if(State.m_HoveredButton != -1)
    {
        Simple_Buttons[State.m_HoveredButton].m_Event();
    }
}

int gui_GetHoveredButtonID(int x, int y)
{
    GLuint index;
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    glReadPixels(x, vp[3] - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
    return index-1;
}

void gui_MouseMove(int x, int y)
{

    if(State.m_HoveredButton != -1)
    {
        Simple_Buttons[State.m_HoveredButton].m_IsHovered = False;
    }

    int t = gui_GetHoveredButtonID(x, y);
    if(t == State.m_PressedButton)
    {
        State.m_HoveredButton = t;
        Simple_Buttons[State.m_HoveredButton].m_IsHovered = True;
    }
    else
    {
        Simple_Buttons[State.m_HoveredButton].m_IsHovered = False;
        State.m_HoveredButton = -1;
    }

    if(State.m_PressedButton == -1)
    {
        State.m_HoveredButton = gui_GetHoveredButtonID(x, y);
        Simple_Buttons[State.m_HoveredButton].m_IsHovered = True;
    }

//    if (State.m_StateIndex == GAME)
//    {
        //print_2i(x, y);
//    }

//    double ox, oy, oz;
//    ClientToOpenGL(x, y, &ox, &oy,&oz);
}



void gui_KeyboardPress(SDL_Keycode code)
{
    switch(code)
    {
    case SDLK_ESCAPE:
        Running = 0;
        break;
    case SDLK_1:
        ToMainMenu();
        break;
    case SDLK_2:
        ToStartMenu();
        break;
    case SDLK_3:
        ToSettingsMenu();
        break;
    case SDLK_b:
        GoBackMenu();
        break;

    default:
        break;
    }
    return;
}
