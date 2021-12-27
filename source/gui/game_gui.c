#include "game_gui.h"


extern TState State;
extern TSimpleButton* Simple_Buttons;

static int* _Buttons;
static int _ButtonsCount;

void SetupGameMenu()
{
    _ButtonsCount = 0;

    if (_ButtonsCount == 0)
        return;
    _Buttons = malloc(sizeof(int) * _ButtonsCount);

    _Buttons[0] = 4;
}

void DrawGameGUI(void)
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Draw Stuff
    int i, id, t;
    for(i = 0; i < _ButtonsCount ; i++)
    {
        id = _Buttons[i];
        glStencilFunc(GL_ALWAYS, id + 1, 1);
        Simple_Buttons[ id ].m_Draw_txy( id, 0.0f, -(i - 1) * 1.2f );
    }

    glDisable(GL_STENCIL_TEST);
}
