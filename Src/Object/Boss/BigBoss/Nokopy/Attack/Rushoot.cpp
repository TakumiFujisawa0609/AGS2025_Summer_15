#include "Rushoot.h"

Rushoot::Rushoot()
{
}

Rushoot::~Rushoot()
{
}

void Rushoot::Init(const Vector2F* pos)
{
    AttackBase::Init(pos);
    obj_.pos_ = *pos;
	obj_.radius_ = 200;
    obj_.size_={ 200,200 };
	obj_.speed_ = 10.0f;
	lookOn_ = false;
	obj_.isAlive_ = true;
	obj_.isCircle_ = true;
	isParry_ = true;

}

void Rushoot::Update(void)
{
	obj_.pos_ = *boss;
}

void Rushoot::Draw(void)
{
}

void Rushoot::Release(void)
{
}

const std::vector<Base> Rushoot::Get(void) const
{
    return std::vector<Base>();
}

void Rushoot::On(void)
{
}

void Rushoot::Off(void)
{
}

