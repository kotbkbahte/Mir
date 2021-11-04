#include "start_menu.h"

extern TState State;
extern TSimpleButton* Simple_Buttons;


void DrawStartMenu()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


    // Draw Stuff
    int i;
    for(i = 3; i < 7 ; i++)
    {
        glStencilFunc(GL_ALWAYS, i + 1, 1);
        //draw_simple_button_t(i);
        Simple_Buttons[i].m_Draw(i);
    }
}

void MouseMoveStartMenu(int x, int y)
{
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



void ToStartMenu()
{
    State.m_StateIndex     = START_MENU;
    State.m_StateDraw      = DrawStartMenu;
    State.f_MouseMoveEvent = MouseMoveStartMenu;
    State.f_MouseClickEvent = MouseClickStartMenu;
}

void MouseClickStartMenu(int x, int y)
{
    if(State.m_HoveredButton != -1)
    {
        printf("%s\n", Simple_Buttons[State.m_HoveredButton].m_Text);
        Simple_Buttons[State.m_HoveredButton].m_Event();
    }
}

