#ifndef TEXTURE_HANDLER_H_INCLUDED
#define TEXTURE_HANDLER_H_INCLUDED


#define STB_IMAGE_IMPLEMENTATION
#include "../extern/stb_image.h"
#include "../core/game_types.h"
#include "message_handler.h"

void LoadTextures();
void LoadTexture(const char* file_name, GLuint* texture);


#endif // TEXTURE_HANDLER_H_INCLUDED
