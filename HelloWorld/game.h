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
void createvalues();
void fileload();
int arrcount();
extern int mainscore;


