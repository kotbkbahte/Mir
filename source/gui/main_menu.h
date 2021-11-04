#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED

#include "../core/game_types.h"
#include "../graphics/graphics.h"
#include "simple_button.h"

void SetupMainMenu();
void CloseMainMenu();


void DrawMainMenu();

void ToMainMenu();

void MouseMoveMainMenu(int x, int y);
void MouseClickMainMenu(int x, int y);

#endif // MAIN_MENU_H_INCLUDED
