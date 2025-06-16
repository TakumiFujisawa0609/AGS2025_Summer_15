#include"Bamboo.h"

Bamboo::Bamboo()
{
}

Bamboo::~Bamboo()
{
}

void Bamboo::Init(void)
{
}

void Bamboo::Set(Vector2F pos)
{
	unit_.nextpos_ = pos;

	unit_.yAccel_ = -20.0f;
	unit_.xAccel_ = (float)(GetRand(40) - 20);

	unit_.isAlive_ = true;

	unit_.radius_ = (float)(GetRand(20) + 10);
	unit_.size_ = { unit_.radius_,unit_.radius_ };
}

void Bamboo::Update(void)
{

	UnitBase::Update();
}

void Bamboo::Draw(void)
{
	if (!unit_.isAlive_)return;

	DrawCircleAA(unit_.disppos_.x, unit_.disppos_.y, unit_.radius_, 30, RGB(0, 255, 0));
}

void Bamboo::Release(void)
{
}
