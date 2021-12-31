#ifndef MOUSE_HANDLER_H_INCLUDED
#define MOUSE_HANDLER_H_INCLUDED

#include "../core/game_types.h"

void ms_Move(SDL_Event event);
void ms_Click(SDL_Event event);

void ms_Down(SDL_Event event);
void ms_Up(SDL_Event event);


#endif // MOUSE_HANDLER_H_INCLUDED
