#include "graphics.h"

extern TCore *Core;
extern TGameState GameState;
extern TOpenGLProgram_base m_GlProgram;
extern GLuint m_Textures[10];
extern float m_ProjectionMatrix[16];
extern float m_TestMatrix[16];
    extern float r_x, r_y, r_z;

extern FT_Library ft2_lib;
extern FT_Face ft2_face;

extern unsigned int VAO, VBO;
extern TCharTexture m_Characters[128];

const TDrawState DrawStates[] = {DrawMainMenu};//, DrawStartMenu, DrawSettingsMenu, DrawQuit};//, DrawTextMenu, DrawGame, DrawGameMenu, DrawResearchTree};


void InitGraphics()
{
    InitSDL2();

    InitOpenGL();

    LoadTextures();

    InitCamera();

    InitFreeType2();

    LoadCharactersTextures();

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
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    //SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 1 );

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

    GameState.m_BgColor.r = (float)rand() / (float)RAND_MAX;
    GameState.m_BgColor.g = (float)rand() / (float)RAND_MAX;
    GameState.m_BgColor.b = (float)rand() / (float)RAND_MAX;

    if(LoadProgram(&m_GlProgram.ID, "source/shaders/main_frag.glsl", "source/shaders/main_vert.glsl" )  < 0)
    {
        h_log_msg("Failed load program: source/shaders/main_frag.glsl");
    } InitProgram(&m_GlProgram);


    InitBuffers();
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

    FT_Set_Pixel_Sizes(ft2_face, 0, 48);


    if (FT_Load_Char(ft2_face, 'X', FT_LOAD_RENDER))
    {
        h_error_msg("Failed to load Glyph", ERROR);
    }

}

void InitBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
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
    glClear(GL_COLOR_BUFFER_BIT);

    //glEnable(GL_MULTISAMPLE);
    //glEnable(GL_STENCIL_TEST);
    //glEnable(GL_DEPTH_TEST);

    //RenderText("A", 1, 1, 1, 1.0f);
    DrawSquare();
    DrawMainMenu();

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

void RenderText(char* text, int len, float x, float y, float scale)
{
    // activate corresponding render state

    glUseProgram(m_GlProgram.ID);
    float m[16];
    loadIdentity(m);
    loadIdentity(m_TestMatrix);
    matrixRotateZ(m_TestMatrix, r_z);
    matrixRotateY(m_TestMatrix, r_y);
    matrixRotateX(m_TestMatrix, r_x);


    glUniformMatrix4fv(m_GlProgram.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(m_GlProgram.viewLocation, 1, GL_FALSE, m);
    glUniformMatrix4fv(m_GlProgram.modelLocation, 1, GL_FALSE, m_TestMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    for (int i = 0 ; i < len; i++)
    {
        TCharTexture ch = m_Characters[(int)*(text + i) ];

        float xpos = x + ch.m_Bearing.x * scale;
        float ypos = y - (ch.m_Size.y - ch.m_Bearing.y) * scale;

        float w = ch.m_Size.x * scale;
        float h = ch.m_Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        //printf("%f %f %f %f\n", xpos, ypos, h, w);
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.m_TextureID);
        //printf("%d\n", ch.m_TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
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

