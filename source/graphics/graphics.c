#include "graphics.h"

extern TCore *Core;
extern TState State;
extern TGameState GameState;
extern const Uint8* m_Keyboard;
    extern TOpenGLProgram_base m_GlProgram;
    extern TOpenGLProgram_text m_GlProgram_text;
    extern TOpenGLProgram_color m_GlProgram_color;
    extern TOpenGLProgram_button m_GlProgram_button;

extern GLuint m_Textures[10];
extern float m_ProjectionMatrix[16];
extern float m_ModelMatrix[16];
extern float m_TestMatrix[16];
    extern float r_x, r_y, r_z;

extern FT_Library ft2_lib;
extern FT_Face ft2_face;

extern unsigned int VAO, VBO;
extern TCharTexture m_Characters[128];

const TDrawState DrawStates[] = {DrawMainMenu, DrawStartMenu}; // DrawSettingsMenu, DrawQuit};//, DrawTextMenu, DrawGame, DrawGameMenu, DrawResearchTree};


void InitGraphics()
{
    InitSDL2();

    InitOpenGL();

    InitFreeType2();

    LoadTextures();

    LoadCharactersTextures();

    InitCamera();

    create_simple_buttons();

    SetupGUI();

//      InitScene();
}

void InitSDL2()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        h_error_msg("failed init sdl2", SDL_ERROR);
    }

    Core->m_WindowSize.width= 1280;
    Core->m_WindowSize.height = 720;

    // Set SDL Attributes

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

    Core->m_Window = SDL_CreateWindow("Mir",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      Core->m_WindowSize.width, Core->m_WindowSize.height,
                                      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN  );
    if ( Core->m_Window == NULL )
    {
        h_error_msg("Failed to create window", SDL_ERROR);
    }

    Core->m_Context = SDL_GL_CreateContext(Core->m_Window);
    if(Core->m_Context == NULL)
    {
        h_error_msg("Failed to create gl context", SDL_ERROR);
    }

}

void InitOpenGL()
{
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        h_error_msg("Failed to load glad.\n", OPENGL_ERROR);
    }

    ChangeBgColor();
    printf("%f %f %f\n", GameState.m_BgColor.r, GameState.m_BgColor.g, GameState.m_BgColor.b);


    if(LoadProgram(&m_GlProgram.ID, "source/shaders/main_frag.glsl", "source/shaders/main_vert.glsl" )  < 0)
    {
        h_log_msg("Failed load program: source/shaders/main_frag.glsl");
    } InitProgram(&m_GlProgram);


    if(LoadProgram(&m_GlProgram_text.ID, "source/shaders/text_frag.glsl", "source/shaders/text_vert.glsl" )  < 0)
    {
        h_log_msg("Failed load program: source/shaders/text_frag.glsl");
    } InitProgram_text(&m_GlProgram_text);

    if(LoadProgram(&m_GlProgram_color.ID, "source/shaders/sample_frag.glsl", "source/shaders/sample_vert.glsl" )  < 0)
    {
        h_log_msg("Failed load program: source/shaders/sample_frag.glsl");
    } InitProgram_color(&m_GlProgram_color);

    if(LoadProgram(&m_GlProgram_button.ID, "source/shaders/button_frag.glsl", "source/shaders/button_vert.glsl" )  < 0)
    {
        h_log_msg("Failed load program: source/shaders/button_frag.glsl");
    } InitProgram_button(&m_GlProgram_button);



    InitBuffers();

    ToMainMenu();
}

void InitFreeType2()
{
    if (FT_Init_FreeType(&ft2_lib))
    {
        h_error_msg("Could not init FreeType Library", ERROR);
    }

    if (FT_New_Face(ft2_lib, "fonts/Consolas_Bold.ttf", 0, &ft2_face))
    {
        h_error_msg("Failed to load font", ERROR);
    }
    //printf("%d\n", 64 << 6);

    //FT_Set_Char_Size(ft2_face, 0, 64*16, 72, 72);
    FT_Set_Pixel_Sizes(ft2_face, 0, 128);

    //FT_Set_Pixel_Sizes(ft2_face, 0, 64);
}

void InitBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 5, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CloseFreeType2()
{
    FT_Done_Face(ft2_face);
    FT_Done_FreeType(ft2_lib);
}



void RenderFrame()
{
    glClearColor(GameState.m_BgColor.r, GameState.m_BgColor.g, GameState.m_BgColor.b, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    DrawBackground();
    State.f_StateDraw();

    glFinish();
    SDL_GL_SwapWindow(Core->m_Window);
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


void DrawSquare1()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, m_Characters[57].m_TextureID);

    glUseProgram(m_GlProgram_text.ID);
    float m[16];
    loadIdentity(m);

    glUniformMatrix4fv(m_GlProgram_text.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);

    glVertexAttribPointer(m_GlProgram_text.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, squareVertices);
    glEnableVertexAttribArray(m_GlProgram_text.vertexLocation);

    glVertexAttribPointer(m_GlProgram_text.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(m_GlProgram_text.textureCoordsLocation);

    glUniform3f(m_GlProgram_text.textColorLocation, 0.0f, 1.0f, 1.0f);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawSquare()
{
    glBindTexture(GL_TEXTURE_2D, m_Characters[56].m_TextureID);

    glUseProgram(m_GlProgram.ID);
    float m[16];
    loadIdentity(m);

    glUniformMatrix4fv(m_GlProgram.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(m_GlProgram.viewLocation, 1, GL_FALSE, m);
    glUniformMatrix4fv(m_GlProgram.modelLocation, 1, GL_FALSE, m);


    glVertexAttribPointer(m_GlProgram.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram.vertexLocation);

    glVertexAttribPointer(m_GlProgram.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(m_GlProgram.textureCoordsLocation);


    //glLineWidth(10.0f);
    //glPointSize(7.0f);
    //glDrawArrays(GL_POINTS, 0, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


    glBindTexture(GL_TEXTURE_2D, 0);

    //printMatrix(m);
    //printMatrix(m_ProjectionMatrix);
    //exit(0);
}

void RenderText(char* text, float x, float y, float scale)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_GlProgram_text.ID);

    glUniformMatrix4fv(m_GlProgram_text.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);

    loadIdentity(m_ModelMatrix);
    matrixScale(m_ModelMatrix, 0.005f ,0.005f, 1.0f);
    matrixTranslate(m_ModelMatrix, x,  y, 0.0f);
    glUniformMatrix4fv(m_GlProgram_text.modelLocation, 1, GL_FALSE, m_ModelMatrix);

    glUniform4f(m_GlProgram_text.textColorLocation, 0.0f, 1.0f, 1.0f, 1.0f);
    glUniform4f(m_GlProgram_text.outlineColorLocation, 1.0f, 0.0f, 0.0f, 0.0f);


    glActiveTexture(GL_TEXTURE0);

    //glBindVertexArray(VAO);

    // iterate through all characters
    for (int i = 0 ; *(text + i) != '\0' ; i++)
    {
        TCharTexture ch = m_Characters[(int)*(text + i) ];

        float xpos = x + ch.m_Bearing.x * scale;
        float ypos = y - (ch.m_Size.y - ch.m_Bearing.y) * scale;

        float w = ch.m_Size.x * scale;
        float h = ch.m_Size.y * scale;
        // update VBO for each character
        float vertices[6][3] = {
            { xpos,     ypos + h, 2.0f},
            { xpos,     ypos,     2.0f},
            { xpos + w, ypos,     2.0f},

            { xpos,     ypos + h, 2.0f},
            { xpos + w, ypos,     2.0f},
            { xpos + w, ypos + h, 2.0f}
        };

        float tcoords[6][2] =
        {
            {0.0f, 0.0f },
            {0.0f, 1.0f },
            {1.0f, 1.0f },

            {0.0f, 0.0f },
            {1.0f, 1.0f },
            {1.0f, 0.0f }
        };
        /*
        float vertices[6][5] = {
            { xpos,     ypos + h, 0.0f,  0.0f, 0.0f },
            { xpos,     ypos,     0.0f,  0.0f, 1.0f },
            { xpos + w, ypos,     0.0f,  1.0f, 1.0f },

            { xpos,     ypos + h, 0.0f,  0.0f, 0.0f },
            { xpos + w, ypos,     0.0f,  1.0f, 1.0f },
            { xpos + w, ypos + h, 0.0f,  1.0f, 0.0f }
        };*/
        // render glyph texture over quad

        glBindTexture(GL_TEXTURE_2D, ch.m_TextureID);

        glVertexAttribPointer(m_GlProgram_text.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(m_GlProgram_text.vertexLocation);

        glVertexAttribPointer(m_GlProgram_text.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, tcoords);
        glEnableVertexAttribArray(m_GlProgram_text.textureCoordsLocation);

        /*
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        */
        // render quad

        //glPointSize(10.0f);
        //glDrawArrays(GL_POINTS, 0, 6);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.m_Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void RenderText_w(char* text, float x, float y, float width)
{
    static float s = 0;
    s += m_Keyboard[SDL_SCANCODE_9] - m_Keyboard[SDL_SCANCODE_0];
    float scale = 1.0f / (200.0f + s);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(m_GlProgram_text.ID);

    glUniformMatrix4fv(m_GlProgram_text.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);

    loadIdentity(m_ModelMatrix);
    glUniformMatrix4fv(m_GlProgram_text.modelLocation, 1, GL_FALSE, m_ModelMatrix);

    glUniform3f(m_GlProgram_text.textColorLocation, 0.0f, 1.0f, 1.0f);

    glActiveTexture(GL_TEXTURE0);

    //glBindVertexArray(VAO);

    // iterate through all characters
    for (int i = 0 ; *(text + i) != '\0' ; i++)
    {
        TCharTexture ch = m_Characters[(int)*(text + i) ];

        float xpos = x +  scale;
        float ypos = y - (ch.m_Size.y) * scale;

        float w = ch.m_Size.x * scale;
        float h = ch.m_Size.y * scale;
        //printf("%f, %f \t %u %d %d\n", w, h, ch.m_Advance, ch.m_Size.x + ch.m_Bearing.x, ch.m_Size.y );
        // update VBO for each character
        float vertices[6][3] = {
            { xpos,     ypos + h, 2.0f},
            { xpos,     ypos,     2.0f},
            { xpos + w, ypos,     2.0f},

            { xpos,     ypos + h, 2.0f},
            { xpos + w, ypos,     2.0f},
            { xpos + w, ypos + h, 2.0f}
        };

        float tcoords[6][2] =
        {
            {0.0f, 0.0f },
            {0.0f, 1.0f },
            {1.0f, 1.0f },

            {0.0f, 0.0f },
            {1.0f, 1.0f },
            {1.0f, 0.0f }
        };
        /*
        float vertices[6][5] = {
            { xpos,     ypos + h, 0.0f,  0.0f, 0.0f },
            { xpos,     ypos,     0.0f,  0.0f, 1.0f },
            { xpos + w, ypos,     0.0f,  1.0f, 1.0f },

            { xpos,     ypos + h, 0.0f,  0.0f, 0.0f },
            { xpos + w, ypos,     0.0f,  1.0f, 1.0f },
            { xpos + w, ypos + h, 0.0f,  1.0f, 0.0f }
        };*/
        // render glyph texture over quad

        glBindTexture(GL_TEXTURE_2D, ch.m_TextureID);

        glVertexAttribPointer(m_GlProgram_text.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(m_GlProgram_text.vertexLocation);

        glVertexAttribPointer(m_GlProgram_text.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, tcoords);
        glEnableVertexAttribArray(m_GlProgram_text.textureCoordsLocation);

        /*
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        */
        // render quad

        //glPointSize(10.0f);
        //glDrawArrays(GL_POINTS, 0, 6);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.m_Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)

    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


GLuint LoadFile(char* FileName, const GLchar** t)
{
    int len = 8000;
    const GLchar* text = malloc(len);
    memset((char*)text, 0, len);

    FILE *f;
    f = fopen(FileName, "rb");
    if (!f)
    {
        h_error_msg(FileName, LOAD_ERROR);
    }
    fread( (char*)text, 1, 8000, f);
    *t = text;
    fclose(f);
    return 1;

}

GLuint LoadShader(char *FileName, GLuint type)
{
    const GLchar* text = NULL;

    if (LoadFile(FileName, &text) < 0)
        return -1;

    GLint shader = glCreateShader(type);
    glShaderSource(shader, 1, &text, NULL);
    glCompileShader(shader);
    GLint ok;
    GLchar log[2000];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        glGetShaderInfoLog(shader, 2000, NULL, log);
        printf("Program log: %s\n", log);
    }

    free((char*)text);
    return shader;
}


int LoadProgram(GLuint* ID, char* frag, char* vert)
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = LoadShader(vert, GL_VERTEX_SHADER);
    fragmentShader = LoadShader(frag, GL_FRAGMENT_SHADER);

    // Create the program object
    *ID = glCreateProgram();
    if(*ID == 0)
        return -1;
    glAttachShader(*ID, vertexShader);
    glAttachShader(*ID, fragmentShader);

    // Link the program
    glLinkProgram(*ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Check the link status
    glGetProgramiv(*ID, GL_LINK_STATUS, &linked);
    if(!linked)
	{
	    GLint infoLen = 0;
	    glGetProgramiv(*ID, GL_INFO_LOG_LENGTH, &infoLen);
	    if(infoLen > 1)
		{
		    char* infoLog = malloc(sizeof(char) * infoLen);
		    glGetProgramInfoLog(*ID, infoLen, NULL, infoLog);
		    fprintf(stderr, "Error linking program:\n%s\n", infoLog);
		    free(infoLog);
		}

	    glDeleteProgram(*ID);
	    return -1;
	}

	return 1;
}

void InitProgram(TOpenGLProgram_base* program)
{
    program->projectionLocation = glGetUniformLocation(program->ID, "projection");
    program->viewLocation = glGetUniformLocation(program->ID, "view");
    program->modelLocation = glGetUniformLocation(program->ID, "model");
    program->vertexLocation = glGetAttribLocation(program->ID, "vertexPosition");

    program->textureCoordsLocation = glGetAttribLocation(program->ID, "textureCoordinates");
    program->textureLocation = glGetUniformLocation(program->ID, "texture");

    if(program->projectionLocation < 0 || program->viewLocation < 0 || program->modelLocation < 0 ||
       program->vertexLocation < 0 || program->textureCoordsLocation < 0 || program->textureLocation < 0)
    {
        h_log_msg("Error initialization GL program main.");
    }
}

void InitProgram_text(TOpenGLProgram_text* program)
{
    program->projectionLocation = glGetUniformLocation(program->ID, "projection");
    program->modelLocation = glGetUniformLocation(program->ID, "model");
    program->vertexLocation = glGetAttribLocation(program->ID, "vertexPosition");

    program->textureCoordsLocation = glGetAttribLocation(program->ID, "textureCoordinates");
    program->textureLocation = glGetUniformLocation(program->ID, "texture");
    program->textColorLocation = glGetUniformLocation(program->ID, "textColor");
    program->outlineColorLocation = glGetUniformLocation(program->ID, "outlineColor");

    if(program->projectionLocation < 0 || program->vertexLocation < 0 || program->textureCoordsLocation < 0 || program->textureLocation < 0 || program->textColorLocation < 0 || program->outlineColorLocation < 0)
    {
        h_log_msg("Error initialization GL program main.");
    }
}

void InitProgram_color(TOpenGLProgram_color* program)
{
    program->projectionLocation = glGetUniformLocation(program->ID, "projection");
    program->modelLocation = glGetUniformLocation(program->ID, "model");
    program->viewLocation = glGetUniformLocation(program->ID, "view");
    program->vertexLocation = glGetAttribLocation(program->ID, "vertexPosition");

    program->colorLocation = glGetUniformLocation(program->ID, "color");
    if(program->projectionLocation < 0 || program->vertexLocation < 0 || program->modelLocation < 0 || program->viewLocation < 0 || program->colorLocation < 0)
    {
        h_log_msg("Error initialization GL program main.");
    }
}

void InitProgram_button(TOpenGLProgram_button* program)
{
    program->projectionLocation = glGetUniformLocation(program->ID, "projection");
    program->modelLocation = glGetUniformLocation(program->ID, "model");
    program->vertexLocation = glGetAttribLocation(program->ID, "vertexPosition");

    program->textureCoordsLocation = glGetAttribLocation(program->ID, "textureCoordinates");
    program->textureLocation = glGetUniformLocation(program->ID, "texture");
    program->colorLightnessLocation = glGetUniformLocation(program->ID, "colorLightness");

    program->isHoveredLocation = glGetUniformLocation(program->ID, "isHovered");
    program->strokeColorLocation = glGetUniformLocation(program->ID, "strokeColor");

    if(program->strokeColorLocation < 0 || program->isHoveredLocation < 0 || program->projectionLocation < 0 || program->modelLocation < 0 || program->vertexLocation < 0 || program->textureCoordsLocation < 0 || program->textureLocation < 0 || program->colorLightnessLocation < 0)
    {
        h_log_msg("Error initialization GL program main.");
    }
}
