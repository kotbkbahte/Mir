

#include "source/core/core.h"

int Running;

int main(int argc, char *argv[])
{
    InitCore();
    Running = True;

    while (Running)
    {
        HandleEvents();
        UpdateState();
        RenderFrame();
    }




    return EXIT_SUCCESS;
    return 0;
}
