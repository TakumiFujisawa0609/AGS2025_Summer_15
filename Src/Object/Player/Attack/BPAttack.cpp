#include"BPAttack.h"

#include"../Player.h"

BPAttack::BPAttack() : PlayerAttackBase()
{
}

BPAttack::~BPAttack()
{
}

void BPAttack::Init(void)
{
}

void BPAttack::Update(void)
{
	if (!obj_.isAlive_)return;

	switch (dir_)
	{
	case AsoUtility::DIRECTION::E_DIR_RIGHT:
		obj_.pos_.x += DEFAULT_SPEED / ((float)bp_ / 10.0f);
		break;
	case AsoUtility::DIRECTION::E_DIR_LEFT:
		obj_.pos_.x -= DEFAULT_SPEED / ((float)bp_ / 10.0f);
		break;
	}

	ChangeDispPos();
}

void BPAttack::Draw(void)
{
	DrawCircleAA(obj_.disppos_.x, obj_.disppos_.y, obj_.radius_, 30, RGB(0, 200, 0));
}

void BPAttack::Release(void)
{
}

void BPAttack::On(Vector2F pPos, AsoUtility::DIRECTION dir,int bp)
{
	obj_.isAlive_ = true;

	this->dir_ = dir;

	obj_.pos_ = pPos;
	obj_.pos_.x += (dir == AsoUtility::DIRECTION::E_DIR_RIGHT) ? Player::SIZE_X : -Player::SIZE_X;


	this->bp_ = bp;

	obj_.radius_ = DEFAULT_SIZE * ((float)bp / 10.0f);

	obj_.size_ = { obj_.radius_,obj_.radius_ };



}
