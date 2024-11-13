#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"


struct paddle
{
	Play::Point2D position = { 300 , 50 };
	Play::Point2D velocity{10 , 0};
	Play::Point2D botRight = { 450,50 };
	Play::Point2D topLeft = { 300,70 };
};
void DrawPaddle(paddle& p);
void UpdatePaddle(paddle& p);
bool isColliding(Play::GameObject& obj,paddle& p);
float Min(float a, float b);
float Max(float idknum1,float idknum2);
