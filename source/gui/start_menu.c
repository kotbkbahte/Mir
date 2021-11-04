#include "start_menu.h"

extern TState State;
extern TSimpleButton* Simple_Buttons;

static int* _Buttons;
static int _ButtonsCount;

void SetupStartMenu()
{
    _ButtonsCount = 4;
    _Buttons = malloc( sizeof(int) * _ButtonsCount );

    _Buttons[0] = 7;
    _Buttons[1] = 8;
    _Buttons[2] = 9;
    _Buttons[3] = 2;
}

void DrawStartMenu()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Draw Stuff
    int i, id;
    for(i = 0; i < 3 ; i++)
    {
        id = _Buttons[i];
        glStencilFunc(GL_ALWAYS, id + 1, 1);
        Simple_Buttons[ id ].m_Draw_txy( id, (i - 1) * 1.2f, 0.8f  );
    }
    id = _Buttons[i ];
    glStencilFunc(GL_ALWAYS, id + 1 , 1);
    Simple_Buttons[ id ].m_Draw_txy( id, 0.0f, -0.8f );

    glDisable(GL_STENCIL_TEST);
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
    State.f_StateDraw      = DrawStartMenu;
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

