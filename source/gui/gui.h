#ifndef GUI_HANDLER_H_INCLUDED
#define GUI_HANDLER_H_INCLUDED

#include "../core/mir.h"
#include "../graphics/graphics.h"

#include "main_menu.h"
#include "start_menu.h"
#include "settings_menu.h"
#include "simple_button.h"

void SetupGUI();
void CloseGUI();


void gui_MouseClick(int x, int y);
void gui_MouseMove(int x, int y);
void gui_KeyboardPress(SDL_Keycode code);

void GoBackMenu();

void ChangeBgColor();
void SetBgImage(int);
void DrawBackground();

#endif // GUI_HANDLER_H_INCLUDED
