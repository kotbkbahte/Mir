#include "source/core/core.h"


int Running;

int main(int argc, char *argv[])
{
    InitCore();
    Running = True;

    while (Running)
    {
        HandleEvents();
        UpdateState(1.0f);
        RenderFrame();
    }

    return 0;
}
