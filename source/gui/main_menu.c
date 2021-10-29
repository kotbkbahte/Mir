#include "main_menu.h"

extern TState State;

void DrawMainMenu()
{
    //draw_simple_button(0);

    draw_simple_button_t(0);
    draw_simple_button_t(1);
    draw_simple_button_t(2);

    //draw_simple_button_t(1);
    //draw_simple_button_t(2);

    //RenderText_w("A", 0.0f, 0.0f, 0.0f);

    //RenderText("Main Menu!", 0.0f, 0.0f, 1.0f);


}


void ToMainMenu()
{
    State.m_StateIndex = MAIN_MENU;
    State.m_StateDraw  = DrawMainMenu;

}
