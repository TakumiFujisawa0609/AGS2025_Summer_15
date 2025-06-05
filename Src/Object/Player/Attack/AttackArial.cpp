#include<DxLib.h>
#include "AttackArial.h"
#include"../../../Manager/InputManager.h"
#include"../../../Utility/AsoUtility.h"

AttackArial::AttackArial()
{
}

AttackArial::~AttackArial()
{
}

void AttackArial::Init(Vector2F* movePos, Vector2F* drawPos, AsoUtility::DIRECTION* dir)
{
	PlayerAttackBase::Init(movePos, drawPos);
	obj_.radius_ = 50.0f;
	direction_ = dir;
	obj_.pos_.x = pDrawPos_->x;
	obj_.pos_.y = pDrawPos_->y;
	obj_.isAlive_ = true;
}

void AttackArial::Update(void)
{
	if (*direction_ == AsoUtility::DIRECTION::E_DIR_RIGHT) {
		obj_.pos_.x = pDrawPos_->x + 80;
		obj_.pos_.y = pDrawPos_->y;
	}
	else if (*direction_ == AsoUtility::DIRECTION::E_DIR_LEFT) {
		obj_.pos_.x = pDrawPos_->x - 80;
		obj_.pos_.y = pDrawPos_->y;
	}
}

void AttackArial::Draw(void)
{
	DrawCircle(obj_.pos_.x, obj_.pos_.y, 50, 0x00ffff, true);
	DrawCircle(obj_.pos_.x, obj_.pos_.y, 5, 0xff0000, true);
}

void AttackArial::Release(void)
{

}
