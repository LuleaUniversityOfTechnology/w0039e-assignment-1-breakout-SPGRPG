#include "game.h"
#include "paddle.h"

void DrawPaddle(paddle& p)
{
	Play::DrawRect(p.position, p.position + Play::Point2D{ 150, 20 }, Play::cBlue, true);

}
void UpdatePaddle(paddle& p)
{
	p.botRight = p.position + Play::Point2D{150,0};
	p.topLeft = p.position + Play::Point2D{ 0, 20 };
	if (Play::KeyDown(Play::KeyboardButton::KEY_LEFT))
	{
		p.position += -p.velocity;
	}
	else if (Play::KeyDown(Play::KeyboardButton::KEY_RIGHT))
	{
		p.position += p.velocity;
	}
}
bool isColliding(Play::GameObject& obj, paddle& p)
{
	const float dx = obj.pos.x - Max(p.topLeft.x, Min(obj.pos.x, p.botRight.x));
	const float dy = obj.pos.y - Max(p.topLeft.y, Min(obj.pos.y, p.botRight.y));
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
float Max(float idknum1, float idknum2)
{
	if (idknum1 > idknum2)
	{
		return idknum1;
	}

	else if (idknum1 < idknum2)
	{
		return idknum2;
	}
}