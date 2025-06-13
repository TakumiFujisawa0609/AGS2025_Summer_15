#include "EffectTakeDrop.h"
#include"../../Utility/ShapesPosition.h"


EffectTakeDrop::EffectTakeDrop()
{
}

EffectTakeDrop::~EffectTakeDrop()
{
}


void EffectTakeDrop::Update(Vector2F* playerPos, Vector2F* generatePos)
{
	EffectBase::Update();
	if (!isActive_)return;
	unit_.pos_ = *generatePos;
	if (currentFrame_<= SHOW_TIME) {
		unit_.pos_.y += 1;
	}
	else {
	Vector2F pPos = *playerPos;
	Vector2F v = GetMoveVec(unit_.pos_, pPos, 1);
	unit_.pos_.x += v.x;
	unit_.pos_.y += v.y;
	}
}

void EffectTakeDrop::Draw(void)
{
	std::vector<Vector2F>tPos=ShapesPosition::GetPositionCircle(unit_.pos_.x, unit_.pos_.y, 30.0f, 0, 5);
	for (auto& p : tPos) {
		DrawCircle(p.x, p.y, 10, 0x0000ff, true);
	}
}

void EffectTakeDrop::Release(void)
{
}

void EffectTakeDrop::Load(void)
{
}

void EffectTakeDrop::SetParam(void)
{
	lifeTime_ = LIFE_TIME;
}
