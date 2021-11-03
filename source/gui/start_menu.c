#include "start_menu.h"

extern TState State;
void DrawStartMenu()
{
    RenderText("Draw Start Menu!", 0.0f, 0.0f, 1.0f);
}

void MouseMoveStartMenu(int x, int y)
{
    printf("%d %d\n", x, y);

    GLuint index;
    int vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);

    glReadPixels(x, vp[3] - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    index-=1;

    printf("%d\n", index);
}



void ToStartMenu()
{
    State.m_StateIndex     = START_MENU;
    State.m_StateDraw      = DrawStartMenu;
    State.f_MouseMoveEvent = MouseMoveStartMenu;
}
