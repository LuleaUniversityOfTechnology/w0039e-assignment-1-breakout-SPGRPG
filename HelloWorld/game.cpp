#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "game.h"
#include "Play.h"
#include "constants.h"
#include "paddle.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

const float ballSpeed = 3.2f;
paddle paddle123;
int arraycount = 0;

int* arrint;

void create_arr()
{
	arrint = new int[5];
	for (int i = 0; i < 5; i++)
	{
		arrint[i] = 0;
	}
	arraycount = 5;

}
int countlines()
{
	arraycount = 0;
	string newline;
	ifstream myfile("example.txt");

	if (myfile.is_open())
	{
		
		while (getline(myfile, newline))
		{
			arraycount = arraycount + 1;
		}
		myfile.close();
	}
	return arraycount;
}


int* arrcounting(int arraycount)
{
	return new int[arraycount];
}

void create_del_arr()
{
	arraycount = countlines();
	
	if (arraycount == 0)
	{
		create_arr();
	}
	else
	{
		fileload();
	}
}

int mainscore = 0;

void StepFrame(float elapsedTime)
{
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BALL);

	for (int i = 0; i < ballIds.size(); i++)
	{
		Play::GameObject& ball123 = Play::GetGameObject(ballIds[i]);
		Play::UpdateGameObject(ball123);
		Play::DrawObject(ball123);
	}
	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BRICK);
	for (int i = 0; i < brickIds.size(); i++)
	{
		Play::GameObject& brick123 = Play::GetGameObject(brickIds[i]);
		Play::UpdateGameObject(brick123);
		Play::DrawObject(brick123);
	}
	CollidingBB(elapsedTime);
	DrawPaddle(paddle123);
	UpdatePaddle(paddle123);
	for (int i = 0; i < ballIds.size(); i++)
	{
		Play::GameObject& ball123 = Play::GetGameObject(ballIds[i]);

	}
	DrawHighScore();


}
void SetupScene()
{

	for (int x = 1; x < DISPLAY_WIDTH - 18; x = x + 18)
	{
		for (int y = 200; y < DISPLAY_HEIGHT - 12; y = y + 12)
		{
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
		}
	}

}

void SpawnBall()
{

	Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 200 }, 4, "ball");
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++)
	{
		Play::GameObject& ball = Play::GetGameObject(ballIds[i]);
		ball.velocity = normalize({ 1, -1 }) * ballSpeed;
	}
}
void CollisionBall()
{
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++)
	{
		Play::GameObject& ball = Play::GetGameObject(ballIds[i]);
		if (ball.pos.x < 0 && ball.velocity.x < 0)
		{
			ball.velocity.x = -ball.velocity.x;
		}
		else if (ball.pos.x > DISPLAY_WIDTH - 5 && ball.velocity.x > 0)
		{
			ball.velocity.x = -ball.velocity.x;
		}
		else if (ball.pos.y < 0 && ball.velocity.y < 0)
		{
			ball.velocity.y = -ball.velocity.y;
		}
		else if (ball.pos.y > DISPLAY_HEIGHT - 5 && ball.velocity.y > 0)
		{
			ball.velocity.y = -ball.velocity.y;
		}
		else if (isColliding(ball, paddle123) == true)
		{
			ball.velocity.y = -ball.velocity.y;
		}

	}
}
void MoveBall()
{
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++)
	{
		Play::GameObject& ball = Play::GetGameObject(ballIds[i]);
		ball.velocity = { 1 * ballSpeed, -1 * ballSpeed };
	}
}
void CollidingBB(float elapsedTime)
{
	const std::vector<int> bricksIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BRICK);
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++)
	{
		Play::GameObject& ball123 = Play::GetGameObject(ballIds[i]);
		for (int j = 0; j < bricksIds.size(); j++)
		{
			Play::GameObject& brick = Play::GetGameObject(bricksIds[j]);
			if (Play::IsColliding(ball123, brick))
			{
				Play::DestroyGameObject(bricksIds[j]);
				ball123.velocity.x = ball123.velocity.x;
				ball123.velocity.y = -ball123.velocity.y;
				mainscore = mainscore + 1;
			}
			else if (ball123.pos.y < 50)
			{	
				reset(elapsedTime);
			}
		}
	}
}
void DrawHighScore()
{
	for (int i = 0; i < 5; i = i + 1) 
	{
		std::string str = to_string(arrint[i]);
		Play::DrawDebugText(Play::Point2D{ DISPLAY_WIDTH - 50, 70 - i * 15 }, str.c_str(), Play::cWhite, true);
	}
	std::string str = to_string(mainscore);
	Play::DrawDebugText(Play::Point2D{ 50, 70 }, str.c_str(), Play::cYellow, true);
}
void fileload()
{
	int* newarrint = new int[arraycount];
	string newline;
	ifstream myfile("example.txt");
	if (myfile.is_open())
	{
		int t = 0;
		while(getline(myfile, newline))
		{
			newarrint[t] = stoi(newline);
			t = t + 1;
		}
		myfile.close();
	}
	delete[] arrint;
	arrint = newarrint;
}

void reset(float elapsedTime)
{

			movingarrbetween();
			resetall();
			StepFrame(elapsedTime);
}
void deletearr()
{
	delete[] arrint;
}
void resetall()
{
	mainscore = 0;
	DestroyAllGameObjects();
	SpawnBall();
	SetupScene();
}
void filesave()
{
	ofstream myfile;
	myfile.open("example.txt");
	for (int i = 0; i < arraycount ; i = i + 1)
	{
		std::string str = to_string(arrint[i]);
		myfile << str << "\n";
	}
	myfile.close();
}
void movingarrbetween()
{
	arraycount += 1;
	int* newarrint = arrcounting(arraycount);
	int i = 0;
	arrint; newarrint; mainscore;
	while (arrint[i] > mainscore)
	{
		newarrint[i] = arrint[i];
		i++;
	}
	newarrint[i] = mainscore;
	i++;

	while (i < arraycount)
	{
		newarrint[i] = arrint[i - 1];
		i++;
	}

	delete[] arrint;
	arrint = newarrint;
	mainscore = 0;
}
