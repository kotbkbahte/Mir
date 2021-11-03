#include "gui.h"

const TMouseMoveEventFunc MouseEventFuncs[] = {MouseMoveMainMenu, MouseMoveStartMenu};
const TButtonFunc ButtonFuncs[] = {ToMainMenu, ToStartMenu, goBack};// ToSettingsMenu, ToQuit};//, DrawTextMenu, DrawGame, DrawGameMenu, DrawResearchTree};

const TDrawButtonFunc ButtonDrawFuncs[] = {draw_simple_button_t, draw_simple_button_t_stroke};


int ids[10];

int id_queue = 0;

void DrawGuiColor()
{

}

void goBack()
{

}


int gui_get_next_id()
{
    static int id = 0;

    if(id_queue == 0)
    {
        return id++;
    }
    else
    {
        h_log_msg("Rewrite gui_get_next_id before use it\n!");
        id_queue-=1;
        return ids[id_queue+=1];
    }
}

void gui_remove_id(int id)
{
    h_log_msg("Rewrite gui_remove_id before use it\n!");

    id_queue++;
    ids[id_queue] = id;
}
