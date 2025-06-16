#include "EffectTakeDrop.h"
#include"../../Utility/ShapesPosition.h"


EffectTakeDrop::EffectTakeDrop()
{
}

EffectTakeDrop::EffectTakeDrop(Vector2F* generation)
{
	unit_.pos_ = *generation;
}

EffectTakeDrop::~EffectTakeDrop()
{

}

void EffectTakeDrop::Init(void)
{
	EffectBase::Init();
}


void EffectTakeDrop::Update(void)
{
	EffectBase::Update();
}

void EffectTakeDrop::Draw(void)
{
	EffectBase::Draw();
	std::vector<Vector2F>tPos = ShapesPosition::GetPositionCircle(unit_.pos_.x, unit_.pos_.y, 300.0f, 0, 5);
	for (auto& p : tPos) {
		DrawCircle(p.x, p.y, 10, 0x0000ff, true);
	}
}

void EffectTakeDrop::Release(void)
{
}

void EffectTakeDrop::Load(void)
{
	int a = 0;
}

void EffectTakeDrop::SetParam(void)
{
	lifeTime_ = LIFE_TIME;
}
