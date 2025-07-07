#include"Bamboo.h"

#include"../Player/Player.h"

Bamboo::Bamboo()
{
}

Bamboo::~Bamboo()
{
}

void Bamboo::Init(void)
{
}

void Bamboo::Set(Vector2F pos, int image)
{
	this->image_ = image;

	Set(pos);
}

void Bamboo::Set(Vector2F pos)
{
	unit_.nextpos_ = pos;
	unit_.pos_ = unit_.nextpos_;
	ChangeDispPos();

	scale_ = (float)(GetRand(2) + 1);
	unit_.radius_ = (DEFAULT_SIZE * scaleTb[(int)scale_]) / 2;
	unit_.size_ = { unit_.radius_ * 2.0f,unit_.radius_ * 2.0f };

	unit_.yAccel_ = -20.0f;
	unit_.xAccel_ = (float)(GetRand(40) - 20);

	unit_.isGravity_ = true;

	aliveTime_ = ALIVE_TIME;

	unit_.isAlive_ = true;
}

void Bamboo::Update(void)
{
	if (!unit_.isAlive_)return;

	aliveTime_--;
	if (aliveTime_ <= 0)unit_.isAlive_ = false;

	UnitBase::Update();
}

void Bamboo::Draw(void)
{
	if (unit_.isAlive_ &&
		((aliveTime_ > (int)(ALIVE_TIME * 0.3f)) || ((aliveTime_ / 10) % 2 == 0))) {
		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, scaleTb[(int)scale_], 0, image_, true);
	}
}

void Bamboo::Release(void)
{
}
