#ifndef MIR_H_INCLUDED
#define MIR_H_INCLUDED

#include <time.h>

#include "game_types.h"
#include "../gui/gui.h"
#include "../gui/game_gui.h"
#include "../utils/utils.h"
#include "../handlers/animations.h"

#include "../math/perlin_noise.h"
#include "../math/additive_white_gaussian_noise.h"


void ToGame1();
void ToGame2();
void ToGame3();


void InitScene();


void SetState(int i);

void ToGame();
void InitGameMap();


void DrawGame();
void DrawMap();

void DrawMirMap();
void DrawMirMap_();

void DrawMirTile(int texture, int i, int j, int layer);
void DrawMirTile_(TPoint2_c texture, int i, int j, int layer);

void DrawMirTileAnimated(int texture, int frame, int i, int j, int layer);
void DrawMirSelectedTile();
void DrawMirUnit();

void DrawMirBuildings();
void DrawMirBuildingOffset(TBuilding* b);
void DrawMirBuildings_();


void DrawMirLandscape();
void DrawMirLandscape_();

void DrawTile(TTile* tile, float x, float y);

void DrawSelectedTile(TTile* tile, float x, float y);
void DrawSquare_xyz_rgb(float x, float y, float z, float r, float g, float b);

void DrawSubTile(int i, float x, float y);
void DrawSubTile_xyz(int i, float x, float y, float z);

void GenerateRandomNoiseMap();
void GeneratePerlinNoiseMap();

void GenerateRandomNoiseMirMap();
void GenerateRandomBuildings();
void GenerateRandomLandscape();
void GenerateRandomLandscape_();


void PrintBuildingsMap();
void PrintLandscapeMap();

void game_PressKeyboard(SDL_Keycode code);
void game_MouseMove(int x, int y);
void game_MouseDown(int x, int y, int button);
void game_MouseUp(int x, int y, int button);


int GetTileByCoord(double ox, double oy, int* x, int* y);


void UpdateState(float dt);
#endif // MIR_H_INCLUDED
