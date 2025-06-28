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
	endPos = { 0.0f, 0.0f };
	counter_ = 0;
	isStandby_ = false;
}

void Tackle::Update()
{
	attackCounter_++;

	VECTOR start;
	start.x = Camera::GetInstance().GetPos().x;
	start.y = Camera::GetInstance().GetPos().y;

	switch (dir_)
	{
	case DIR::JUMP:
		if (attackCounter_ > TACKLE_START / 2)dir_ = DIR::STANDBY;
		break;
	case Tackle::DIR::STANDBY:
		if (isStandby_)dir_ = DIR::TACKLE_LEFT;
		break;
	case DIR::TACKLE_LEFT:
		if (boss->x < start.x - 500)dir_ = DIR::TACKLE_RIGHT;
		break;
	case DIR::TACKLE_RIGHT:
		if (boss->x > start.x + Application::SCREEN_SIZE_X + 500)dir_ = DIR::END;
		break;
	case DIR::END:
		counter_++;
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

