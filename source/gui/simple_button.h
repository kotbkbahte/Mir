#ifndef SIMPLE_BUTTON_H_INCLUDED
#define SIMPLE_BUTTON_H_INCLUDED

#include "../core/game_types.h"
#include "../gui/gui.h"

#include "main_menu.h"
#include "start_menu.h"

//void create_simple_button(char* button_name, float x, float y, float h, float w);
void create_simple_button(char* button_name, int event_func, int draw_func, unsigned int texture_id, float x, float y);
void create_simple_buttons();

void draw_simple_button(int id);
void draw_simple_button_t(int id);
void draw_simple_button_t1(int id);
void draw_simple_button_t_stroke(int id);

void handle_simple_button();
void PassButtonEvent();
void ToQuit();

#endif // SIMPLE_BUTTON_H_INCLUDED
