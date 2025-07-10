#include "Runboo.h"
#include<DxLib.h>
#include "../../Tutorial/BossTutorial.h"
#include"Weakness.h"


Runboo::Runboo()
{
}

Runboo::~Runboo()
{
}

void Runboo::Init()
{

	moveSpeed_ = MOVE_SPEED;

	BossBase::Init();
	for (int ii = 0; ii < WEAK_MAX; ii++)
	{
		Vector2F weakPos = { 150, (float)(Application::SCREEN_SIZE_Y / 5.0f) * (ii + 1) };

		weak_.emplace_back(new Weakness());
		weak_[weak_.size() - 1]->Init(weakPos, moveSpeed_);
	}

	unit_.nextpos_ = { HALF_X, HALF_Y };
	unit_.pos_ = unit_.nextpos_;
	ChangeDispPos();
	unit_.size_ = { HALF_X * 2 ,HALF_Y * 2 };

	unit_.hp_ = 100;
	unit_.isAlive_ = true;
	unit_.isGravity_ = false;
	unit_.isStageCollision_ = false;
}

void Runboo::Update()
{
	unit_.nextpos_.x += moveSpeed_;

	BossBase::Update();

	/*for (int ii = 0; ii < WEAK_MAX; ii++) {
		weak_[ii]->Update();
	}*/

	for (auto& w : weak_) { w->Update(unit_.pos_); }
}

void Runboo::Draw()
{
	DrawBox(
		unit_.disppos_.x - HALF_X,
		unit_.disppos_.y - HALF_Y,
		unit_.disppos_.x + HALF_X,
		unit_.disppos_.y + HALF_Y,
		RGB(255, 255, 255), true
	);

	for (int ii = 0; ii < WEAK_MAX; ii++)weak_[ii]->Draw();
}

void Runboo::Release()
{
	for (int ii = 0; ii < WEAK_MAX; ii++)
	{
		weak_[ii]->Release();
		delete weak_[ii];
	}
	weak_.clear();
}

AttackBase* Runboo::GetAttackIns(void)
{
	return nullptr;
}

std::vector<Base> Runboo::GetObj(void)
{
	return std::vector<Base>();
}

void Runboo::ObjHit(int i)
{
}

void Runboo::SetDamage(int dmg)
{
}

//std::vector<Base*> Runboo::GetObj(void)
//{
//	return std::vector<Base*>();
//}

void Runboo::Idle(void)
{
}

void Runboo::Move(void)
{
}

void Runboo::Attack(void)
{
}

void Runboo::Damage(void)
{
}

void Runboo::Death(void)
{
}

void Runboo::HpUpdate(void)
{
}



