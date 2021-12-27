#include "keyboard_handler.h"


#include "../gui/main_menu.h"
#include "../gui/start_menu.h"
#include "../gui/settings_menu.h"

extern TState State;
extern TGameState GameState;

extern const Uint8* m_Keyboard;
extern float m_TestMatrix[16];
    float r_x, r_y, r_z;

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
}

void kb_KeyPressed(SDL_Keycode code)
{
    State.f_KeyboardPress(code);
}
