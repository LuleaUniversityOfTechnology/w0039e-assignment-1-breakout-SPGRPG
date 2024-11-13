#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "game.h"
#include "Play.h"
#include "constants.h"
#include "paddle.h"

const float ballSpeed = 3.2f;
paddle pad123;

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
	CollidingBB();
	DrawPaddle(pad123);
	UpdatePaddle(pad123);
	for (int i = 0; i < ballIds.size(); i++)
	{
		Play::GameObject& ball123 = Play::GetGameObject(ballIds[i]);

	}
	

}
void SetupScene()
{
	


	for (int x = 1; x < DISPLAY_WIDTH-18; x=x+18)
		{
			for (int y = 200; y < DISPLAY_HEIGHT-12; y=y+12)
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
		else if (ball.pos.x > DISPLAY_WIDTH-5 && ball.velocity.x > 0)
		{
			ball.velocity.x = -ball.velocity.x;
		}
		else if (ball.pos.y < 0 && ball.velocity.y < 0)
		{
			ball.velocity.y = -ball.velocity.y;
		}
		else if (ball.pos.y > DISPLAY_HEIGHT-5 && ball.velocity.y > 0)
		{
			ball.velocity.y = -ball.velocity.y;
		}
		else if (isColliding(ball, pad123) == true)
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
		ball.velocity = { 1 * ballSpeed, -1 * ballSpeed } ;
	}
}
void CollidingBB() 
{
	const std::vector<int> bricksIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BRICK);
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(ObjectType::TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++)
	{
		Play::GameObject& ball123 = Play::GetGameObject(ballIds[i]);
		for (int j = 0; j < bricksIds.size(); j++)
		{
			Play::GameObject& brick = Play::GetGameObject(bricksIds[j]);
			if(Play::IsColliding(ball123,brick))
			{
				Play::DestroyGameObject(bricksIds[j]);
				ball123.velocity.x = ball123.velocity.x;
				ball123.velocity.y = -ball123.velocity.y;
			}
		}
	}
}

