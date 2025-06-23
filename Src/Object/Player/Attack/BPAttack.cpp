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

	if (aliveCounter_-- <= 0)obj_.isAlive_ = false;

	switch (dir_)
	{
	case AsoUtility::DIRECTION::E_DIR_RIGHT:
		obj_.pos_.x += DEFAULT_SPEED / bp_;
		break;
	case AsoUtility::DIRECTION::E_DIR_LEFT:
		obj_.pos_.x -= DEFAULT_SPEED / bp_;
		break;
	}

	ChangeDispPos();
}

void BPAttack::Draw(void)
{
	if (!obj_.isAlive_)return;
	DrawRotaGraph(obj_.disppos_.x, obj_.disppos_.y, (float)bp_, 0, image_, true);
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

	aliveCounter_ = ALIVE_TIME;

	this->bp_ = bp;

	obj_.radius_ = DEFAULT_RADIUS * bp;

	obj_.size_ = { DEFAULT_SIZE_X * bp,DEFAULT_SIZE_Y * bp };
}
