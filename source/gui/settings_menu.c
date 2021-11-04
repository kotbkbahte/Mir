#include "settings_menu.h"


extern TState State;

void ToSettingsMenu()
{
    State.m_StateIndex = SETTINGS_MENU;
    State.m_StateDraw     = DrawSettingsMenu;
    State.f_MouseMoveEvent = MouseMoveSettingsMenu;
    State.m_HoveredButton  = -1;
}

void DrawSettingsMenu()
{

}

void MouseMoveSettingsMenu(int x, int y)
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
