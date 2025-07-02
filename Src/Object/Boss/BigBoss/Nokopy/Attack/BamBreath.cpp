#include "BamBreath.h"

BamBreath::BamBreath()
{
}

BamBreath::~BamBreath()
{
}

void BamBreath::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);

}

void BamBreath::Update(void)
{
	AttackBase::Update();
}

void BamBreath::Draw(void)
{
}

void BamBreath::Release(void)
{
}

const std::vector<Base> BamBreath::Get(void) const
{
	return std::vector<Base>();
}

void BamBreath::On(void)
{
}

void BamBreath::Off(void)
{
}

void BamBreath::ChangeDispPos(void)
{
}
