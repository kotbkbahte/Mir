#include "keyboard_handler.h"


#include "../gui/main_menu.h"
#include "../gui/start_menu.h"
#include "../gui/settings_menu.h"

extern TGameState GameState;
extern const Uint8* m_Keyboard;
extern int Running;
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

    GameState.m_BgColor.r = (float)rand() / (float)RAND_MAX;
    GameState.m_BgColor.g = (float)rand() / (float)RAND_MAX;
    GameState.m_BgColor.b = (float)rand() / (float)RAND_MAX;
}

void kb_KeyPressed(SDL_Keycode code)
{
    switch(code)
    {
    case SDLK_ESCAPE:
        Running = 0;
        break;
    case SDLK_1:
        ToMainMenu();
        break;
    case SDLK_2:
        ToStartMenu();
        break;
    case SDLK_3:
        ToSettingsMenu();
        break;
    case SDLK_b:
        goBackMenu();
        break;

    default:
        break;
    }
}
