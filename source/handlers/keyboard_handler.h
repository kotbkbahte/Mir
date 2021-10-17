#ifndef KEYBOARD_HANDLER_H_INCLUDED
#define KEYBOARD_HANDLER_H_INCLUDED

#include "../core/game_types.h"


int kb_GetKeyDown(SDL_Scancode key);

int kb_GetDoubleKeyDown(SDL_Scancode key1, SDL_Scancode key2);

void InitKeyboard();

void kb_KeyUp();

void kb_KeyDown();

void kb_KeyPressed(SDL_Keycode code);


#endif // KEYBOARD_HANDLER_H_INCLUDED
