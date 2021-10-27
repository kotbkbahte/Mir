#include "main_menu.h"

extern TState State;

void DrawMainMenu()
{
    //draw_simple_button(0);
    RenderText_w("21!");

    //RenderText("Main Menu!", 0.0f, 0.0f, 1.0f);


}


void ToMainMenu()
{
    State.m_StateIndex = MAIN_MENU;
    State.m_StateDraw  = DrawMainMenu;

}
