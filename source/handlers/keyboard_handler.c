#include "keyboard_handler.h"

Uint8* m_Keyboard;

extern TPoint3_f bg_color;

int kb_GetKeyDown(SDL_Scancode key)
{
    return m_Keyboard[key];
}

int kb_GetDoubleKeyDown(SDL_Scancode key1, SDL_Scancode key2)
{
    return (m_Keyboard[key1]) && (m_Keyboard[key2]) ;
}

void InitKeyboard()
{
    m_Keyboard = SDL_GetKeyboardState(NULL);
}

void kb_KeyUp(SDL_Scancode code)
{
    m_Keyboard = SDL_GetKeyboardState(NULL);


}

void kb_KeyDown(SDL_Scancode code)
{
    m_Keyboard = SDL_GetKeyboardState(NULL);

    bg_color.r = (float)rand() / (float)RAND_MAX;
    bg_color.g = (float)rand() / (float)RAND_MAX;
    bg_color.b = (float)rand() / (float)RAND_MAX;
}

void kb_KeyPressed(SDL_Keycode code)
{
    switch(code)
    {
    case SDLK_LCTRL:
        break;
    default:
        break;
    }
}
