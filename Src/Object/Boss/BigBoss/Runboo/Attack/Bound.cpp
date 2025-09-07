#include "Bound.h"
#include<DxLib.h>

Bound::Bound(float moveSpeed)
{
	image_ = -1;

	moveSpeed_ = moveSpeed;
}

Bound::~Bound()
{
}

void Bound::Init(const Vector2F* pos)
{
	image_ = LoadGraph("Data/Image/Boss/Runboo/a.png");

	AttackBase::Init(pos);


}

void Bound::Update(void)
{
}

void Bound::Draw(void)
{
}

void Bound::Release(void)
{
	DeleteGraph(image_);
}
