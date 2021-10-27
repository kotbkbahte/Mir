#ifndef SIMPLE_BUTTON_H_INCLUDED
#define SIMPLE_BUTTON_H_INCLUDED

#include "../core/game_types.h"
#include "../handlers/gui_handler.h"

#include "main_menu.h"
#include "start_menu.h"

void create_simple_button(char* button_name, float x, float y, float h, float w);

void draw_simple_button(int id);

void handle_simple_button();


#endif // SIMPLE_BUTTON_H_INCLUDED
