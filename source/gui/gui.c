#include "gui.h"

extern TState State;
extern TGameState GameState;

const TMouseMoveEventFunc MouseEventFuncs[] = {MouseMoveMainMenu, MouseMoveStartMenu};


const TButtonEventFunc ButtonEventFuncs[] = {ToMainMenu, ToStartMenu, ToSettingsMenu, GoBackMenu, ToQuit, PassButtonEvent };// , ToQuit};//, DrawTextMenu, DrawGame, DrawGameMenu, DrawResearchTree};
const TButtonDrawFunc ButtonDrawFuncs[] = {draw_simple_button_t, draw_simple_button_t_stroke, draw_simple_button_t1};


// States {MAIN_MENU, START_MENU, SETTINGS_MENU, QUIT, TEST_MENU, GAME, GAME_MENU, RESEARCH_TREE, STATES_COUNT};

const int BackStates[] = {-1, MAIN_MENU, MAIN_MENU, -1, MAIN_MENU};
const TToState ToState[] = {ToMainMenu, ToStartMenu, ToSettingsMenu};

int ids[10];

int id_queue = 0;

void SetupGUI()
{
    SetupMainMenu();
    SetupSettingsMenu();
    SetupStartMenu();
}

void CloseGUI()
{
    CloseMainMenu();
}

void DrawGuiColor()
{

}

void GoBackMenu()
{
    SetState(BackStates[State.m_StateIndex]);
}

void ChangeBgColor()
{
    GameState.m_BgColor.r = (float)rand() / (float)RAND_MAX;
    GameState.m_BgColor.g = (float)rand() / (float)RAND_MAX;
    GameState.m_BgColor.b = (float)rand() / (float)RAND_MAX;
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
