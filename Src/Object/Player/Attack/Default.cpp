#include"Default.h"

#include<DxLib.h>

Default::Default(Vector2F* pPos) : PlayerAttackBase(pPos)
{
}

Default::~Default()
{
}

void Default::Init(AsoUtility::DIRECTION dir)
{
	PlayerAttackBase::Init(dir);
}

void Default::Update()
{
	switch (dir_)
	{
	case AsoUtility::DIRECTION::E_DIR_RIGHT:

		break;
	case AsoUtility::DIRECTION::E_DIR_LEFT:
		break;
	default:
		break;
	}
}

void Default::Draw()
{

}

void Default::Release()
{

}