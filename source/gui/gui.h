#ifndef GUI_HANDLER_H_INCLUDED
#define GUI_HANDLER_H_INCLUDED

#include "../core/game_types.h"
#include "main_menu.h"
#include "start_menu.h"
#include "simple_button.h"

int gui_get_next_id();

void gui_remove_id(int id);
void goBack();

#endif // GUI_HANDLER_H_INCLUDED
