#include "event_handler.h"

extern int Running;
extern TKeyboard m_Keyboard;

#define log_int(a) printf("%s: %f\n", #a, a);
const float a[] = {0.125, 0.25, 0.5, 1,1.25, 1.5, 1.75 , 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

void HandleEvents()
{
    SDL_Event event;


    if (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Running = False;
                break;

            case SDL_MOUSEWHEEL:
                {
                    static int scale_i = 0.0f;
                    scale_i += event.wheel.y;
                    if ( (scale_i >= 100) || (scale_i <= -3) )
                        scale_i -= event.wheel.y;
                    //printf("%d\n", scale_i );
                    log_int(a[scale_i + 3]);
                    UpdateCamProjection( a[scale_i + 3] );
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                {
                    ms_Click(event);
                }
                break;
            case SDL_MOUSEMOTION:
                {
                    ms_Move(event);
                }
                break;

            case SDL_KEYUP:
                kb_KeyUp(event.key.keysym.sym);
                break;

            case SDL_KEYDOWN:
                //kb_KeyDown(event.key.keysym.sym);
                kb_KeyPressed(event.key.keysym.sym);
                break;

            case SDL_WINDOWEVENT:
                {
                    switch(event.window.event)
                        {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            {
                                //UpdateViewportProjection(Core, event.window.data1, event.window.data2);
                                //Core->m_Graphics.m_Width  = event.window.data1;
                                //Core->m_Graphics.m_Height = event.window.data2;

                                //glViewport(0, 0, Core->m_Graphics.m_Width, Core->m_Graphics.m_Height);
                                //float k = Core->m_Graphics.m_Width / (float)Core->m_Graphics.m_Height;
                                //glOrtho(-k, k, -1,1, -1,1);
                                //cam_SetOrtho(&Core->m_Camera, -1, 1, -k, k, -5.0f, 5.0f);

                            }
                            break;
                        }
                }
                break;


        }





    }
}

