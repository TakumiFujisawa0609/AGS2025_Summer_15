#include "Runboo.h"
#include<DxLib.h>
#include "../../Tutorial/BossTutorial.h"
#include "../../../../Manager/SceneManager.h"
#include"Weakness.h"


Runboo::Runboo()
{
}

Runboo::~Runboo()
{
}



void Runboo::Init()
{
	image_ = LoadGraph((Application::PATH_IMAGE + "Boss/Runboo/Runboo.png").c_str());
	moveSpeed_ = MOVE_SPEED;

	BossBase::Init();
	for (int ii = 0; ii < WEAK_MAX; ii++)
	{
		Vector2F weakPos = { unit_.pos_.x, (float)(Application::SCREEN_SIZE_Y / 5.0f) * (ii + 1) };

		weak_.emplace_back(new Weakness());
		weak_[weak_.size() - 1]->Init(weakPos, moveSpeed_);
	}

	unit_.nextpos_ = { HALF_X, HALF_Y };
	unit_.pos_ = unit_.nextpos_;
	ChangeDispPos();
	unit_.size_ = { HALF_X * 2 ,HALF_Y * 2 };

	unit_.hp_ = HP_MAX;
	unit_.isAlive_ = true;
	unit_.isGravity_ = false;
	unit_.isStageCollision_ = false;
}

void Runboo::Update()
{
	unit_.nextpos_.x += moveSpeed_;

	BossBase::Update();

	const float noiseX = (GetRand(200) - 100) / 500.0f;
	unit_.nextpos_.x += sinf(weak_[0]->GetCnt()) * Weakness::AMPLITUDE + noiseX;

	for (auto& w : weak_)
	{ 
		w->Update(unit_.pos_);
		w->Update();
	}

	if (unit_.inviCounter_ > 0)
	{
		unit_.inviCounter_--;
	}

	if (unit_.inviCounter_ <= 0 && unit_.hp_ <= 0)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}
}

void Runboo::Draw()
{
	DrawRotaGraph(
		unit_.disppos_.x - 600.0f,
		unit_.disppos_.y - 16,
		1.5f, 0.0f, image_,
		true, true
	);

	for (int ii = 0; ii < WEAK_MAX; ii++)weak_[ii]->Draw();

	DrawBar(
		100,
		Application::SCREEN_SIZE_Y - 80,
		Application::SCREEN_SIZE_X - 100,
		Application::SCREEN_SIZE_Y - 30,
		unit_.hp_, HP_MAX, RGB(100, 100, 200)
	);

}

void Runboo::Release()
{
	for (int ii = 0; ii < WEAK_MAX; ii++)
	{
		weak_[ii]->Release();
		delete weak_[ii];
	}

	weak_.clear();

	DeleteGraph(image_);

}

AttackBase* Runboo::GetAttackIns(void)
{
	return nullptr;
}

//std::vector<Base> Runboo::GetObj(void)
//{
//	std::vector<Base> ret;
//
//	for (auto& w : weak_)
//	{
//		ret.emplace_back(w->GetObj());
//	}
//
//	return ret;
//}

void Runboo::ObjHit(int i)
{
}

void Runboo::SetDamage(int dmg)
{
	unit_.hp_ -= dmg;
	unit_.inviCounter_ = INVI_COUNTER;
}

bool Runboo::GetWeakAllDeath(void)
{
	return (weak_[0]->GetUnit().isAlive_ == false &&
			weak_[1]->GetUnit().isAlive_ == false &&
			weak_[2]->GetUnit().isAlive_ == false);

}

//std::vector<Base*> Runboo::GetObj(void)
//{
//	return std::vector<Base*>();
//}

void Runboo::Idle(void)
{
}

void Runboo::Move(void)
{
}

void Runboo::Attack(void)
{
}

void Runboo::Damage(void)
{
}

void Runboo::Death(void)
{
}

void Runboo::HpUpdate(void)
{
}



