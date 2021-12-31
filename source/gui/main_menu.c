#include "main_menu.h"

extern TState State;
extern TSimpleButton* Simple_Buttons;

static int* _Buttons;
static int _ButtonsCount;

void SetupMainMenu()
{
    _ButtonsCount = 3;
    _Buttons = malloc( sizeof(int) * _ButtonsCount );

    _Buttons[0] = 0;
    _Buttons[1] = 1;
    _Buttons[2] = 3;
}

void CloseMainMenu()
{
    free(_Buttons);
}

void DrawMainMenu()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Draw Stuff
    int i, id, t;
    for(i = 0; i < _ButtonsCount ; i++)
    {
        id = _Buttons[i];
        //t  = Simple_Buttons[ id ].m_TextureID;
        glStencilFunc(GL_ALWAYS, id + 1, 1);
        Simple_Buttons[ id ].m_Draw_txy( id, 0.0f, -(i - 1) * 1.2f );
    }

    glDisable(GL_STENCIL_TEST);
}


void ToMainMenu()
{
    State.m_StateIndex = MAIN_MENU;
    State.f_StateDraw     = DrawMainMenu;
    State.f_MouseMoveEvent =  gui_MouseMove;
    State.f_MouseClickEvent = gui_MouseClick;

    State.f_KeyboardPress   = gui_KeyboardPress;

}
