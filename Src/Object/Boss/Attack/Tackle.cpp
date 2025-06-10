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
	dir_ = DIR::STANDBY;
}

void Tackle::Update()
{
	attackCounter_++;

	switch (dir_)
	{
	case Tackle::DIR::STANDBY:
		if (attackCounter_ > NON_TIME)dir_ = DIR::TACKLE_MODE;
		break;
	case Tackle::DIR::TACKLE_MODE:
		break;
	case Tackle::DIR::END:
		break;
	}
}

void Tackle::Draw()
{
	if (obj_.isAlive_)
	{
	}
}

void Tackle::Release()
{
}
