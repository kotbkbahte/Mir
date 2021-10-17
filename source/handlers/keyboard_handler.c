#include "keyboard_handler.h"

Uint8* m_Keyboard;

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
    printf("Init keyboard\n");
    m_Keyboard = SDL_GetKeyboardState(NULL);
}

void kb_KeyUp(SDL_Scancode code)
{
    m_Keyboard[code] = 0;
    //m_Keyboard = SDL_GetKeyboardState(NULL);
}

void kb_KeyDown(SDL_Scancode code)
{
    m_Keyboard[code] = 1;
    //m_Keyboard = SDL_GetKeyboardState(NULL);
}

void kb_KeyPressed(SDL_Keycode code)
{
    switch(code)
    {
    case SDLK_LCTRL:
        {
            //Core->m_Camera.m_IsCameraViewAround = !Core->m_Camera.m_IsCameraViewAround;
        }
        break;
    case SDLK_r:
        //cam_ResetPositionRotation(&Core->m_Camera);
        break;
    case SDLK_q:
        //Core->m_Camera.m_IsMoveAlongAxis = !Core->m_Camera.m_IsMoveAlongAxis;
        break;
    case SDLK_v:
        //Core->m_Camera.m_IsMoveAlongVector = !Core->m_Camera.m_IsMoveAlongVector;
        break;

    case SDLK_KP_5:
        //Core->m_Camera.m_IsOrthoProj = !Core->m_Camera.m_IsOrthoProj;
        //cam_SetProjection(&Core->m_Camera, (float)Core->m_Graphics.m_Width/(float)Core->m_Graphics.m_Height);
        break;
    default:
        break;
    }
}
