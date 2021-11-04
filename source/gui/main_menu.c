#include "main_menu.h"

extern TState State;
extern TSimpleButton* Simple_Buttons;

static int* _Buttons;
static int _ButtonsCount;

void SetupMainMenu()
{
    _ButtonsCount = 3;
    _Buttons = malloc( sizeof(int) * _ButtonsCount );

    _Buttons[0] = BUTTON_PLAYGAME;
    _Buttons[1] = BUTTON_SETTINGS;
    _Buttons[2] = BUTTON_QUIT;
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
    int i, id;
    for(i = 0; i < _ButtonsCount ; i++)
    {
        id = _Buttons[i];
        glStencilFunc(GL_ALWAYS, i + 1, 1);
        Simple_Buttons[ id ].m_Draw( id );
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

void MouseClickMainMenu(int x, int y)
{
    if(State.m_HoveredButton != -1)
    {
        printf("%s\n", Simple_Buttons[State.m_HoveredButton].m_Text);
        Simple_Buttons[State.m_HoveredButton].m_Event();
    }
}

void ToMainMenu()
{
    State.m_StateIndex = MAIN_MENU;
    State.m_StateDraw     = DrawMainMenu;
    State.f_MouseMoveEvent = MouseMoveMainMenu;
    State.f_MouseClickEvent = MouseClickMainMenu;
}
