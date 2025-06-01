#include"AttackBase.h"

#include<DxLib.h>

#include"../../../Manager/Camera.h"

AttackBase::AttackBase()
{
	obj_.isAlive_ = false;
	attackCounter_ = 0;
	end_ = false;
}

AttackBase::~AttackBase()
{
}

void AttackBase::Init(const Vector2F* pos)
{
	boss = pos;
	end_ = false;
	obj_.isAlive_ = false;
	attackCounter_ = 0;
}

void AttackBase::Update()
{
	ChangeDispPos();
}

const std::vector<Base> AttackBase::Get(void) const
{
	std::vector<Base>ret;

	ret.emplace_back(obj_);

	return ret;
}




void AttackBase::ChangeDispPos()
{
	auto& camera = Camera::GetInstance();
	obj_.disppos_ = obj_.pos_ - camera.GetPos();
}