#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED




#include "../core/game_types.h"
#include "../handlers/event_handler.h"
#include "../handlers/message_handler.h"
#include "../handlers/texture_handler.h"
#include "../gui/gui.h"
#include "camera.h"

#include <GL/glu.h>

#include <stdlib.h>


void InitGraphics();

void InitSDL2();
void InitOpenGL();
void InitFreeType2();

void CloseSDL2();
void CloseOpenGL();
void CloseFreeType2();

void RenderFrame();
void RenderText(char* text, float x, float y, float scale);
void RenderText_w(char* text, float x, float y, float width);


void UpdateCamProjection(float scale);

int LoadProgram(GLuint* ID, char* frag, char* vert);

void InitProgram(TOpenGLProgram_base* program);
void InitProgram_text(TOpenGLProgram_text* program);
void InitProgram_color(TOpenGLProgram_color* program);
void InitProgram_button(TOpenGLProgram_button* program);


void DrawSquare();

void ClientToOpenGL(int x, int y, double *ox, double *oy, double *oz);

// Prepare all stuff

#endif // GRAPHICS_H_INCLUDED
