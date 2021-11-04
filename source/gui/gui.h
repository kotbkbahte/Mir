#ifndef GUI_HANDLER_H_INCLUDED
#define GUI_HANDLER_H_INCLUDED

#include "../core/mir.h"

#include "main_menu.h"
#include "start_menu.h"
#include "settings_menu.h"
#include "simple_button.h"

void SetupGUI();
void CloseGUI();

int gui_get_next_id();

void gui_remove_id(int id);
void GoBackMenu();
void ChangeBgColor();

#endif // GUI_HANDLER_H_INCLUDED
