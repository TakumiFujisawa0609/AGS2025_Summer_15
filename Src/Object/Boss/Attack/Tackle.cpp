#include"Tackle.h"
#include<DxLib.h>

Tackle::Tackle()
{

}

Tackle::~Tackle()
{
}

void Tackle::Init(const Vector2F* pos)
{
	AttackBase::Init(pos);
}

void Tackle::Update()
{
	if (obj_.isAlive_)
	{
		
	}
}

void Tackle::Draw()
{
	if (obj_.isAlive_)
	{
		
	}
}

void Tackle::Release()
{
}
