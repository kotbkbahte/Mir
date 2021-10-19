#include "mir.h"

extern TState State;
extern const TDrawState DrawStates[];

void InitGame()
{
    SetState(MAIN_MENU);
}

void SetState(int i)
{
    State.m_StateIndex = i;
    State.m_StateDraw  = DrawStates[i];
}
