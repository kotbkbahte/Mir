#include "settings_menu.h"


extern TState State;
extern TSimpleButton* Simple_Buttons;

static int* _Buttons;
static int _ButtonsCount;

void SetupSettingsMenu()
{
    _ButtonsCount = 4;
    _Buttons = malloc(sizeof(int) * _ButtonsCount);

    _Buttons[0] = 4;
    _Buttons[1] = 5;
    _Buttons[2] = 6;
    _Buttons[3] = 2;

}

void ToSettingsMenu()
{

    State.m_StateIndex = SETTINGS_MENU;
    State.f_StateDraw     = DrawSettingsMenu;
    State.f_MouseMoveEvent =  gui_MouseMove;
    State.f_MouseClickEvent = gui_MouseClick;
    State.f_KeyboardPress = gui_KeyboardPress;

}

void DrawSettingsMenu()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Draw Stuff
    int i, id;
    for(i = 0; i < _ButtonsCount ; i++)
    {
        id = _Buttons[i];
        glStencilFunc(GL_ALWAYS, id + 1, 1);
        Simple_Buttons[ id ].m_Draw_txy(id , 0.0f, -(i - 1) * 1.2f );
    }

    glDisable(GL_STENCIL_TEST);
}


