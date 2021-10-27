#include "start_menu.h"

extern TState State;
void DrawStartMenu()
{
    RenderText("Draw Start Menu!", 0.0f, 0.0f, 1.0f);
}

void ToStartMenu()
{
    State.m_StateIndex = START_MENU;
    State.m_StateDraw  = DrawStartMenu;
}
