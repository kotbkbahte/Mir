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


void ToStartMenu()
{
    State.m_StateIndex      = START_MENU;
    State.f_StateDraw       = DrawStartMenu;
    State.f_MouseMoveEvent  = gui_MouseMove;
    State.f_MouseClickEvent = gui_MouseClick;

    State.f_KeyboardPress   = gui_KeyboardPress;

}


