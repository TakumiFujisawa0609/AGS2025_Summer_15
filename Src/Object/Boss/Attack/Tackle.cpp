#include"Tackle.h"
#include<DxLib.h>

Tackle::Tackle()
{

}

Tackle::~Tackle()
{
}

void Tackle::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);
	dir_ = DIR::JUMP;
}

void Tackle::Update()
{
	attackCounter_++;

	switch (dir_)
	{
	case DIR::JUMP:
		if (attackCounter_ > NON_TIME / 2)dir_ = DIR::STANDBY;
		break;
	case Tackle::DIR::STANDBY:
		if (attackCounter_ > NON_TIME)dir_ = DIR::TACKLE_RIGHT;
		break;
	case DIR::TACKLE_RIGHT:
		if(boss->x )
		break;
	case DIR::TACKLE_LEFT:
		break;
	case DIR::END:
		break;
	}
}

void Tackle::Draw()
{
	if (obj_.isDraw_)
	{

	}
}

void Tackle::Release()
{
}

void Tackle::CollisionLenDraw(Vector2F startPos, float radius)
{
	DrawBox(startPos.x, boss->y - radius, boss->x, startPos.y + radius, RGB(0, 0, 255), true);
}