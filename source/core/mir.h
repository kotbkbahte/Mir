#ifndef MIR_H_INCLUDED
#define MIR_H_INCLUDED

#include "game_types.h"
#include "../gui/gui.h"
#include "../gui/game_gui.h"
#include "../utils/utils.h"

void ToGame1();
void ToGame2();
void ToGame3();


void InitScene();


void SetState(int i);

void ToGame();
void GenerateRandomMap();
void InitGameMap();
void FillTileRandom(TTile* tile);




void DrawGame();
void DrawMap();

void DrawMirMap();
void DrawMirTile(int texture, int i, int j, int layer);
void DrawMirSelectedTile();

void DrawMirBuildings();
void DrawMirBuildingOffset(TBuilding* b);

void DrawMirLandscape();

void DrawTile(TTile* tile, float x, float y);
void DrawSelectedTile(TTile* tile, float x, float y);
void DrawSquare_xyz_rgb(float x, float y, float z, float r, float g, float b);


void DrawSubTile(int i, float x, float y);
void DrawSubTile_xyz(int i, float x, float y, float z);

void GenerateRandomNoiseMirMap();
void GenerateRandomBuildings();
void GenerateRandomLandscape();

void PrintBuildingsMap();

void game_PressKeyboard(SDL_Keycode code);



void UpdateState(float dt);
#endif // MIR_H_INCLUDED
