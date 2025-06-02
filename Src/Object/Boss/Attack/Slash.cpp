#include"Slash.h"

#include<DxLib.h>

#include"../../../Manager/Camera.h"
#include"../BossTutorial.h"

Slash::Slash()
{
	image_ = -1;
}

Slash::~Slash()
{
}

void Slash::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);
	obj_.radius_ = 120.0f;
	obj_.size_ = { 240.0f,240.0f };
}

void Slash::Update()
{

	

	if (obj_.isAlive_) {
		switch (dir_)
		{
		case Slash::LEFT:
			obj_.pos_ = { boss->x - (BossTutorial::SIZE_X / 2),boss->y };
			break;
		case Slash::RIGHT:
			obj_.pos_ = { boss->x + (BossTutorial::SIZE_X / 2),boss->y };
			break;
		}
		attackCounter_++;
		if (attackCounter_ > ATTACK_TIME) {
			obj_.isAlive_ = false;
			end_ = true;
		}
	}



	AttackBase::Update();
}

void Slash::Draw()
{
	if (obj_.isAlive_) {
		DrawCircleAA(obj_.disppos_.x, obj_.disppos_.y, obj_.radius_, 30, RGB(0, 0, 0));
	}
}

void Slash::Release()
{


}




void Slash::SetTarget(const AttackBase::DIR dir)
{
	dir_ = dir;
}
