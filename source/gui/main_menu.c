#include "main_menu.h"

extern TState State;

void DrawMainMenu()
{
    RenderText("Main Menu!", 0.0f, 0.0f, 1.0f);
}


void ToMainMenu()
{
    State.m_StateIndex = MAIN_MENU;
    State.m_StateDraw  = DrawMainMenu;

}
