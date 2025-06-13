#include"BPAttack.h"

#include"../Player.h"

BPAttack::BPAttack() : PlayerAttackBase()
{
}

BPAttack::~BPAttack()
{
}

void BPAttack::Init(int image)
{
	this->image_ = image;
}

void BPAttack::Update(void)
{
	if (!obj_.isAlive_)return;

	switch (dir_)
	{
	case AsoUtility::DIRECTION::E_DIR_RIGHT:
		obj_.pos_.x += DEFAULT_SPEED / ((float)bp_ / 20.0f);
		break;
	case AsoUtility::DIRECTION::E_DIR_LEFT:
		obj_.pos_.x -= DEFAULT_SPEED / ((float)bp_ / 10.0f);
		break;
	}

	ChangeDispPos();
}

void BPAttack::Draw(void)
{
	if (!obj_.isAlive_)return;
	DrawRotaGraph(obj_.disppos_.x, obj_.disppos_.y, bp_/10.0f, 0, image_, true);
}

void BPAttack::Release(void)
{
}

void BPAttack::On(Vector2F pPos, AsoUtility::DIRECTION dir,float bp)
{
	obj_.isAlive_ = true;

	this->dir_ = dir;

	obj_.pos_ = pPos;
	obj_.pos_.x += (dir == AsoUtility::DIRECTION::E_DIR_RIGHT) ? Player::SIZE_X : -Player::SIZE_X;


	this->bp_ = bp;

	obj_.radius_ = DEFAULT_RADIUS * (bp / 10.0f);

	obj_.size_ = { DEFAULT_SIZE_X * (bp / 10.0f),DEFAULT_SIZE_Y * (bp / 10.0f) };
}
