#include "mouse_handler.h"

extern TState State;


void ms_Move(SDL_Event event)
{
    int x = event.motion.x;
    int y = event.motion.y;


    State.f_MouseMoveEvent(x, y);
}

void ms_Click(SDL_Event event)
{
    int x = event.motion.x;
    int y = event.motion.y;

    State.f_MouseClickEvent(x, y);
}
