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
	if (a> b)
	{
		return b;
	}
	else if (a< b)
	{
		return a;
	}
}
float Max(float a, float b)
{
	if (a > b)
	{
		return a;
	}

	else if (a< b)
	{
		return b;
	}
}