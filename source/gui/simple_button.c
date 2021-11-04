#include "simple_button.h"



    extern TOpenGLProgram_color m_GlProgram_color;
    extern float m_ProjectionMatrix[16];
    extern GLuint m_Textures[10];
    extern TOpenGLProgram_base m_GlProgram;
    extern TOpenGLProgram_text m_GlProgram_text;
    extern TOpenGLProgram_color m_GlProgram_color;
    extern TOpenGLProgram_button m_GlProgram_button;
    extern const TDrawButtonFunc ButtonDrawFuncs[];


int Buttons_Count = 0;
int Draw_Buttons_Count;
int Handle_Buttons_Count;

TSimpleButton* Simple_Buttons;
int Draw_Buttons[] = {};
int Handle_Buttons[] = {};

void create_simple_buttons()
{
    create_simple_button("PlayGame", BUTTON_DRAW_DEFAULT, m_Textures[BUTTON_PLAYGAME], 0, 1.2f);
    create_simple_button("Settings", BUTTON_DRAW_DEFAULT, m_Textures[BUTTON_SETTINGS], 0, 0.0f);
    create_simple_button("Quit",     BUTTON_DRAW_DEFAULT, m_Textures[BUTTON_QUIT], 0, -1.2f);

    create_simple_button("Back", BUTTON_DRAW_DEFAULT, m_Textures[BUTTON_BACK], 0, -1.2f);
    create_simple_button("War1", BUTTON_DRAW_STROKE,  m_Textures[BUTTON_WAR1], 1.2f, 0.4f);
    create_simple_button("War2", BUTTON_DRAW_STROKE,  m_Textures[BUTTON_WAR2], 0.0f, 0.4f);
    create_simple_button("War3", BUTTON_DRAW_STROKE,  m_Textures[BUTTON_WAR3], -1.2f,0.4f);
}

void create_simple_button(char* button_name, int draw_func, unsigned int texture_id, float x, float y)
{

    Simple_Buttons = realloc(Simple_Buttons, (Buttons_Count + 1) * sizeof(TSimpleButton));

    int w , h;
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

    Simple_Buttons[Buttons_Count].m_ID = gui_get_next_id();
    Simple_Buttons[Buttons_Count].m_Color = (TPoint3_f){ .r = rand(), .g = rand(), .b = rand() };
    Simple_Buttons[Buttons_Count].m_Pos = (TPoint2_f){.x = x, .y = y};
    Simple_Buttons[Buttons_Count].m_Size = (TPoint2_f){.x = (float)w, .y = (float)h};
    Simple_Buttons[Buttons_Count].m_IsHovered = False;
    Simple_Buttons[Buttons_Count].m_TextureID = texture_id;
    Simple_Buttons[Buttons_Count].m_Draw      = ButtonDrawFuncs[draw_func];
    strcpy( Simple_Buttons[Buttons_Count].m_Text, button_name );

    Buttons_Count += 1;
}

void init_simple_button()
{
    //handle_simple_button();
    //draw_simple_button();
}


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


void draw_simple_button_t(int id)
{

    TSimpleButton b = Simple_Buttons[id];

    glBindTexture(GL_TEXTURE_2D, b.m_TextureID);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_GlProgram_button.ID);
    float m[16];
    float n[16];
    loadIdentity(m);
    loadIdentity(n);
    float k = 720.0f / 1280.0f;
    matrixTranslate(m, b.m_Pos.x, b.m_Pos.y, 1.0f);
    matrixScale(m,  2 * b.m_Size.x / 1280.0f / k, 2 * b.m_Size.y / 720.0f , 1.0f);

    glUniformMatrix4fv(m_GlProgram_button.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    //glUniformMatrix4fv(m_GlProgram_button.viewLocation, 1, GL_FALSE, m);
    glUniformMatrix4fv(m_GlProgram_button.modelLocation, 1, GL_FALSE,  m);
    glUniform1i(m_GlProgram_button.isHoveredLocation, GL_FALSE);

    if(b.m_IsHovered)
        glUniform1f(m_GlProgram_button.colorLightnessLocation, 0.5);
    else
        glUniform1f(m_GlProgram_button.colorLightnessLocation, 1.0);

    glVertexAttribPointer(m_GlProgram_button.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram_button.vertexLocation);

    glVertexAttribPointer(m_GlProgram_button.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates_flipped);
    glEnableVertexAttribArray(m_GlProgram_button.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}


void draw_simple_button_t_stroke(int id)
{

    TSimpleButton b = Simple_Buttons[id];

    glBindTexture(GL_TEXTURE_2D, b.m_TextureID);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_GlProgram_button.ID);
    float m[16];
    float n[16];
    loadIdentity(m);
    loadIdentity(n);
    float k = 720.0f / 1280.0f;



    glVertexAttribPointer(m_GlProgram_button.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram_button.vertexLocation);

    glVertexAttribPointer(m_GlProgram_button.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates_flipped);
    glEnableVertexAttribArray(m_GlProgram_button.textureCoordsLocation);
    glUniform1i(m_GlProgram_button.isHoveredLocation, b.m_IsHovered);


    if(b.m_IsHovered)
    {

        loadIdentity(m);
        matrixScale(m,  1.1f, 1.1f, 1.0f);
        matrixTranslate(m, b.m_Pos.x, b.m_Pos.y, 1.0f);
        matrixScale(m,  2 * b.m_Size.x / 1280.0f / k, 2 * b.m_Size.y / 720.0f , 1.0f);
        glUniformMatrix4fv(m_GlProgram_button.modelLocation, 1, GL_FALSE,  m);
        glUniform3f(m_GlProgram_button.strokeColorLocation, 1.0f, 0.0f, 0.0f);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    }

    glUniform1i(m_GlProgram_button.isHoveredLocation, GL_FALSE);

    loadIdentity(m);
    matrixTranslate(m, b.m_Pos.x, b.m_Pos.y, 1.0f);
    matrixScale(m,  2 * b.m_Size.x / 1280.0f / k, 2 * b.m_Size.y / 720.0f , 1.0f);

    glUniform1f(m_GlProgram_button.colorLightnessLocation, 1.0);
    glUniformMatrix4fv(m_GlProgram_button.modelLocation, 1, GL_FALSE,  m);
    glUniformMatrix4fv(m_GlProgram_button.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    //glUniformMatrix4fv(m_GlProgram_button.viewLocation, 1, GL_FALSE, m);
    glUniformMatrix4fv(m_GlProgram_button.modelLocation, 1, GL_FALSE,  m);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}




void draw_simple_button_c(int id)
{

    TSimpleButton b = Simple_Buttons[id];

    glBindTexture(GL_TEXTURE_2D, b.m_TextureID);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_GlProgram_button.ID);
    float m[16];
    float n[16];
    loadIdentity(m);
    loadIdentity(n);
    float k = 720.0f / 1280.0f;
    matrixTranslate(m, b.m_Pos.x, b.m_Pos.y, 1.0f);
    matrixScale(m,  2 * b.m_Size.x / 1280.0f / k, 2 * b.m_Size.y / 720.0f , 1.0f);

    glUniformMatrix4fv(m_GlProgram_button.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    //glUniformMatrix4fv(m_GlProgram_button.viewLocation, 1, GL_FALSE, m);
    glUniformMatrix4fv(m_GlProgram_button.modelLocation, 1, GL_FALSE,  m);

    if(b.m_IsHovered)
        glUniform1f(m_GlProgram_button.colorLightnessLocation, 0.5);
    else
        glUniform1f(m_GlProgram_button.colorLightnessLocation, 1.0);

    glVertexAttribPointer(m_GlProgram_button.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram_button.vertexLocation);

    glVertexAttribPointer(m_GlProgram_button.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates_flipped);
    glEnableVertexAttribArray(m_GlProgram_button.textureCoordsLocation);


    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glPointSize(100.0f);
    glDrawArrays(GL_POINTS, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);

}

void handle_simple_button()
{

}

void destroy_button()
{

}
