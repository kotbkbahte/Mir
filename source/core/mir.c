#include "mir.h"

extern TState State;
extern const TDrawState DrawStates[];
extern TToState ToState[];


void InitGame()
{
    SetState(MAIN_MENU);
}

void SetState(int i)
{
    if(i < 0)
        return;
    ToState[i]();
}
