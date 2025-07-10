#include "Takenoko.h"

Takenoko::Takenoko()
{
}

Takenoko::~Takenoko()
{
}

void Takenoko::Init(Vector2F pos)
{
	unit_.radius_ = 10;
	unit_.pos_ = pos;
	unit_.isAlive_ = true;
}

void Takenoko::Update(void)
{
}

void Takenoko::Draw(void)
{
	DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, 0x000AAA);
}

void Takenoko::Release(void)
{
}

void Takenoko::IsGround(Collision::DIR dir)
{
}
