#include "Wavemboo.h"
#include"../../../../../Utility/ShapesPosition.h"

Wavemboo::Wavemboo()
{
}

Wavemboo::~Wavemboo()
{
}

void Wavemboo::Init(const Vector2F* pos)
{
    AttackBase::Init(pos);
    obj_.pos_ =*boss;
}

void Wavemboo::Update(void)
{
}

void Wavemboo::Draw(void)
{
}

void Wavemboo::Release(void)
{
}

const std::vector<Base> Wavemboo::Get(void) const
{
    return std::vector<Base>();
}

void Wavemboo::On(void)
{
    std::vector<Vector2F>pos=
    ShapesPosition::GetPositionWave(obj_.pos_.x, obj_.pos_.y, 
        64, 320, 0, 32, 32);
    for (int i = 0; i < 32; i++) {

    }
}

void Wavemboo::Off(void)
{
}

