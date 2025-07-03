#include"Bammoon.h"

#include<DxLib.h>

Bammoon::Bammoon()
{
}

Bammoon::~Bammoon()
{
}

void Bammoon::Init(void)
{
	BossBase::Init();

	unit_.radius_ = 50.0f;
	unit_.size_ = { unit_.radius_ * 2,unit_.radius_ * 2 };
	unit_.speed_ = 10.0f;


	unit_.isAlive_ = true;
	unit_.nextpos_ = { 1000.0f,400.0f };
	unit_.pos_ = unit_.nextpos_;
	unit_.hp_ = 1000;
}

void Bammoon::Update(void)
{

	BossBase::Update();
}

void Bammoon::Draw(void)
{
	if (unit_.isAlive_) {
		DrawCircleAA(unit_.disppos_.x, unit_.disppos_.y, unit_.radius_, 30, RGB(0, 255, 0));
	}
}

void Bammoon::Release(void)
{
}


//std::vector<Base*> Bammoon::GetObj(void)
//{
//	return std::vector<Base*>();
//}




void Bammoon::Idle(void)
{
	if (--idleTime_ <= 0) {
		ChangeState(STATE::MOVE);
	}
}

void Bammoon::Move(void)
{
}

void Bammoon::Attack(void)
{
}

void Bammoon::Damage(void)
{
}

void Bammoon::Death(void)
{
}


void Bammoon::IsGround(Collision::DIR dir)
{
}