#ifndef TEXTURE_HANDLER_H_INCLUDED
#define TEXTURE_HANDLER_H_INCLUDED


#include "../core/game_types.h"
#include "message_handler.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include <ft2build.h>
#include FT_FREETYPE_H


void LoadTextures();
void LoadTexture(const char* file_name, GLuint* texture);

void LoadAnimatedTexture(TAnimatedTexture* animated_texture);
void LoadTextureMap(TTextureMap* texture_map);



void LoadCharactersTextures();


#endif // TEXTURE_HANDLER_H_INCLUDED
