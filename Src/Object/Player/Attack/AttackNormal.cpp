#include<DxLib.h>
#include "AttackNormal.h"  
#include"../../../Manager/InputManager.h"
#include"../../../Utility/AsoUtility.h"

AttackNormal::AttackNormal()  
{  
}  

AttackNormal::~AttackNormal()  
{  
}  
void AttackNormal::Init(void)
{
}
void AttackNormal::Init(Vector2F* movePos, Vector2F* drawPos, AsoUtility::DIRECTION* dir)
{
	PlayerAttackBase::Init(movePos, drawPos);
	obj_.radius_ = 50.0f; 
	direction_ = dir;
	obj_.pos_.x = pDrawPos_->x;
	obj_.pos_.y = pDrawPos_->y;
	obj_.isAlive_ = true;
	obj_.size_ = { 50.0f,50.0f };
}

void AttackNormal::Update(void)
{
	if (*direction_ == AsoUtility::DIRECTION::E_DIR_RIGHT) {
		obj_.pos_.x = pDrawPos_->x + 80;
		obj_.pos_.y = pDrawPos_->y;
	}
	else if (*direction_ == AsoUtility::DIRECTION::E_DIR_LEFT) {
		obj_.pos_.x = pDrawPos_->x - 80;
		obj_.pos_.y = pDrawPos_->y;
	}
	PlayerAttackBase::Update();

}

void AttackNormal::Draw(void)  
{  
	DrawCircle(obj_.pos_.x, obj_.pos_.y, 50, 0x00ffff, true);
	DrawCircle(obj_.pos_.x, obj_.pos_.y,5, 0xff0000, true);
}  

void AttackNormal::Release(void)  
{  

}
