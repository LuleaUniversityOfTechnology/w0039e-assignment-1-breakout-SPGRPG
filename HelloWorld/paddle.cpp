#include "game.h"
#include "paddle.h"

void DrawPaddle(paddle& paddle)
{
	Play::DrawRect(paddle.position, paddle.position + Play::Point2D{ 150, 20 }, Play::cBlue, true);

}
void UpdatePaddle(paddle& paddle)
{
	paddle.botRight = paddle.position + Play::Point2D{150,0};
	paddle.topLeft = paddle.position + Play::Point2D{ 0, 20 };
	if (Play::KeyDown(Play::KeyboardButton::KEY_LEFT))
	{
		paddle.position += -paddle.velocity;
	}
	else if (Play::KeyDown(Play::KeyboardButton::KEY_RIGHT))
	{
		paddle.position += paddle.velocity;
	}
	paddlecollision(paddle);
	
	
}
bool isColliding(Play::GameObject& obj, paddle& paddle)
{
	const float dx = obj.pos.x - Max(paddle.topLeft.x, Min(obj.pos.x, paddle.botRight.x));
	const float dy = obj.pos.y - Max(paddle.topLeft.y, Min(obj.pos.y, paddle.botRight.y));
	bool isCol = (dx * dx + dy * dy) < (obj.radius * obj.radius);
	return isCol;
}

float Min(float a, float b)
{
	return (a>b) ? b : a;
}
float Max(float a, float b)
{
	return (a > b) ? a : b;
}
void paddlecollision(paddle& paddle)
{
	if (paddle.topLeft.x<0)
	{
		paddle.position.x += paddle.velocity.x;
	}
	else if (paddle.botRight.x > DISPLAY_WIDTH)
	{
		paddle.position.x -= paddle.velocity.x;
	}
}