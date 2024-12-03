#pragma once

#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"
void SpawnBall();
void StepFrame(float elapsedTime);
void SetupScene();
void CollisionBall();
void MoveBall();
void CollidingBB(float elapsedTime);
void DrawHighScore();
void fileload();
void create_del_arr();
void create_arr();
void reset(float elapsedTime);
extern int mainscore;
void deletearr();
int countlines();
void resetall();
void filesave();
void movingarrbetween(int a);
void movingarrback(int a);


