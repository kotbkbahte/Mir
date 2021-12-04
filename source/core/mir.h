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

void DrawTile(TTile* tile, int x, int y);
void DrawSubTile();


void UpdateState(float dt);
#endif // MIR_H_INCLUDED
