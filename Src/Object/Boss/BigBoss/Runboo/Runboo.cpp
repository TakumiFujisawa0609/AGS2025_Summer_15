#include "Runboo.h"
#include<DxLib.h>
#include "../../Tutorial/BossTutorial.h"
#include "../../../../Manager/SceneManager.h"


Runboo::Runboo()
{

}

Runboo::~Runboo()
{
}



void Runboo::Init()
{
	this->Release();

	image_ = LoadGraph((Application::PATH_IMAGE + "Boss/Runboo/Runboo.png").c_str());
	moveSpeed_ = MOVE_SPEED;

	unit_.nextpos_ = { HALF_X, HALF_Y };
	unit_.pos_ = unit_.nextpos_;
	ChangeDispPos();
	unit_.size_ = { HALF_X * 2 ,HALF_Y * 2 };

	unit_.isAlive_ = true;
	unit_.isGravity_ = false;
	unit_.isStageCollision_ = false;

	ChangeState(STATE::IDLE);

	for (int ii = 0; ii < WEAK_MAX; ii++)
	{
		Vector2F weakPos = { unit_.pos_.x, (float)(Application::SCREEN_SIZE_Y / 5.0f) * (ii + 1) };

		weak_.emplace_back(new Weakness());
		weak_[weak_.size() - 1]->SetPlayerPosPtr(playerPosPtr_);
		weak_[weak_.size() - 1]->Init(weakPos, moveSpeed_);
	}

	for (auto& weak : weak_)
	{
		unit_.hp_ += weak->GetUnit().hp_;
	}

	maxHp_ = unit_.hp_;

}

void Runboo::Update()
{
	int deadCount = 0;
	for (const auto& w : weak_)
	{
		if (!w->GetUnit().isAlive_) // Ž€‚ñ‚Å‚¢‚é‚È‚ç
		{
			deadCount++;
		}
	}

	switch (deadCount)
	{
	case 0:
		break;
	case 1:
		moveSpeed_ = 3;
		break;
	case 2:
		moveSpeed_ = 5;
		break;
	}

	BossBase::Update();

	const float noiseX = (GetRand(200) - 100) / 500.0f;
	unit_.nextpos_.x += sinf(weak_[0]->GetCnt()) * Weakness::AMPLITUDE + noiseX;

	int totalHP = 0;

	for (auto& w : weak_)
	{ 
		w->AttackManager(deadCount == 0);
		w->Update(unit_.pos_, moveSpeed_);
		w->Update();

		totalHP += w->GetUnit().hp_;
	}

	static int cnt = 0;;

	unit_.hp_ = totalHP;

	if (unit_.hp_ <= 0)
	{
		cnt++;

		moveSpeed_ = 0;

		if (cnt > 180)
		{
			SceneManager::GetIns().Shake();
			ChangeState(STATE::DEATH);
		}
	}
	unit_.nextpos_.x += moveSpeed_;
}

void Runboo::Draw()
{
	DrawRotaGraph(
		unit_.disppos_.x - 600.0f,
		unit_.disppos_.y - 16,
		1.5f, 0.0f, image_,
		true, true
	);

}

void Runboo::Release()
{
	for (auto& w : weak_)
	{
		if (!w)continue;
		w->Release();
		delete w;
		w = nullptr;
	}
	weak_.clear();

	DeleteGraph(image_);

}

void Runboo::DrawHp()
{
	for (int ii = 0; ii < WEAK_MAX; ii++)weak_[ii]->Draw();

	DrawBar(
		100,
		Application::SCREEN_SIZE_Y - 100,
		Application::SCREEN_SIZE_X - 100,
		Application::SCREEN_SIZE_Y - 50,
		unit_.hp_, maxHp_, RGB(0, 0, 255)
	);
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
	unit_.isAlive_ = false;
}

void Runboo::HpUpdate(void)
{
}



