#ifndef ANIMATIONS_H_INCLUDED
#define ANIMATIONS_H_INCLUDED

#include "../core/game_types.h"
#include "message_handler.h"


void InitAnimations();
void UpdateAnimations(float dt);

void BindTextureToAnimation(TTextureAnimation* texture_animation,
                            TAnimatedTexture* animated_texture,
                            int frame);

void InitGameAnimations();
#endif // ANIMATIONS_H_INCLUDED
