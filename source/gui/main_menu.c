#include "main_menu.h"

extern TState State;
extern TSimpleButton* Simple_Buttons;

int _Buttons[] = {};
int _ButtonsCount;
void SetupMainMenu()
{

}

void DrawMainMenu()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


    // Draw Stuff
    int i;
    for(i = 0; i < 3 ; i++)
    {
        glStencilFunc(GL_ALWAYS, i + 1, 1);
        //draw_simple_button_t(i);
        Simple_Buttons[i].m_Draw(i);
    }

    glDisable(GL_STENCIL_TEST);
}

void MouseMoveMainMenu(int x, int y)
{
    //printf("%d %d\n", x, y);
    GLuint index;
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);

    glReadPixels(x, vp[3] - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    index-=1;

    printf("%d\n", index);

    if(State.m_HoveredButton != -1)
        Simple_Buttons[State.m_HoveredButton].m_IsHovered = False;
    State.m_HoveredButton = index;
    Simple_Buttons[State.m_HoveredButton].m_IsHovered = True;

}

void ToMainMenu()
{
    State.m_StateIndex = MAIN_MENU;
    State.m_StateDraw     = DrawMainMenu;
    State.f_MouseMoveEvent = MouseMoveMainMenu;
}
