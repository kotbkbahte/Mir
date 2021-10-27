#include "simple_button.h"



    extern TOpenGLProgram_color m_GlProgram_color;
    extern float m_ProjectionMatrix[16];

const TButtonFunc ButtonFuncs[] = {ToMainMenu, ToStartMenu};// ToSettingsMenu, ToQuit};//, DrawTextMenu, DrawGame, DrawGameMenu, DrawResearchTree};

int Buttons_Count;
int Draw_Buttons_Count;
int Handle_Buttons_Count;

TSimpleButton* Simple_Buttons;
int Draw_Buttons[] = {};
int Handle_Buttons[] = {};

void create_simple_button(char* button_name, float x, float y, float h, float w)
{
    //h_log_msg("Creating button...\n");
    Buttons_Count += 1;
    Simple_Buttons = realloc(Simple_Buttons, Buttons_Count * sizeof(TSimpleButton));

    Simple_Buttons[Buttons_Count-1].m_ID = gui_get_next_id();
    Simple_Buttons[Buttons_Count-1].m_Color = (TPoint3_f){ .r = rand(), .g = rand(), .b = rand() };
    Simple_Buttons[Buttons_Count-1].m_Pos = (TPoint2_f){.x = x, .y = y};
    Simple_Buttons[Buttons_Count-1].m_Size = (TPoint2_f){h, w};
    strcpy( Simple_Buttons[Buttons_Count-1].m_Text, button_name );

}

void init_simple_button()
{
    //handle_simple_button();
    //draw_simple_button();
}

static const GLfloat squareVertices[] = {
    1.0f, 1.0f, 2.0f,
    -1.0f, 1.0f, 2.0f,
    -1.0f, -1.0f, 2.0f,
    1.0f, -1.0f, 2.0f,
};

void draw_simple_button(int id)
{
    TSimpleButton b = Simple_Buttons[id];

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glUseProgram(m_GlProgram_color.ID);
    float m[16];
    float view[16];
    loadIdentity(view);
    loadIdentity(m);
    matrixTranslate(m, b.m_Pos.x, b.m_Pos.y, -2.0f);
    matrixScale(m, b.m_Size.x, b.m_Size.y, 1.0f);

    glUniformMatrix4fv(m_GlProgram_color.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(m_GlProgram_color.viewLocation, 1, GL_FALSE, view);
    glUniformMatrix4fv(m_GlProgram_color.modelLocation, 1, GL_FALSE, m);


    glVertexAttribPointer(m_GlProgram_color.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, squareVertices);
    glEnableVertexAttribArray(m_GlProgram_color.vertexLocation);

    glUniform3f(m_GlProgram_color.colorLocation, b.m_Color.r, b.m_Color.g, b.m_Color.b);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    RenderText(b.m_Text, b.m_Pos.x - b.m_Size.x / 2.0f, b.m_Pos.y - b.m_Size.y / 2.0f, 1.0f);


}

void handle_simple_button()
{

}

void destroy_button()
{

}
