#include "graphics.h"

extern TCore *Core;
extern TState State;
extern TOpenGLProgram_base m_GlProgram;


void InitGraphics()
{
    InitSDL2();

    InitOpenGL();
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

    State.m_BgColor.r = (float)rand() / (float)RAND_MAX;
    State.m_BgColor.g = (float)rand() / (float)RAND_MAX;
    State.m_BgColor.b = (float)rand() / (float)RAND_MAX;

    if(LoadProgram(&m_GlProgram.ID, "source/shaders/main_frag.glsl", "source/shaders/main_vert.glsl" )  < 0)
    {
        h_log_msg("Failed load program: source/shaders/main_frag.glsl");
    }
}

void RenderFrame()
{
    glClearColor(State.m_BgColor.r, State.m_BgColor.g, State.m_BgColor.b, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT);

    //glEnable(GL_MULTISAMPLE);
    //glEnable(GL_STENCIL_TEST);
    //glEnable(GL_DEPTH_TEST);

    glFinish();
    SDL_GL_SwapWindow(Core->m_Window);
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

void InitProgram_m(TOpenGLProgram_base* program)
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

