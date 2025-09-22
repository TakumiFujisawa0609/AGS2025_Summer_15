#include "Runboo.h"
#include<DxLib.h>
#include "../../Tutorial/BossTutorial.h"
#include "../../../../Manager/SceneManager.h"


Runboo::Runboo():
	image_(-1),
	smokeImg_(),
	moveSpeed_(0),
	smokeAnimIndex_(0.0f),
	maxHp_(0),
	weak_(),
	pillar_()
{

}

Runboo::~Runboo()
{
}



void Runboo::Init()
{
	this->Release();

	image_ = LoadGraph((Application::PATH_IMAGE + "Boss/Runboo/Runboo.png").c_str());
	
	//LoadDivGraph((Application::PATH_IMAGE + "Boss/Runboo/smoke.png").c_str(),
	//	SMOKE_IMAGE_NUM, SMOKE_IMAGE_NUM_X, SMOKE_IMAGE_NUM_Y,
	//	SMOKE_IMAGE_SIZE_X, SMOKE_IMAGE_SIZE_Y, smokeImg_);

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
		Vector2F weakPos = { unit_.pos_.x, (unit_.pos_.y + 200 * ii) - 200 };

		weak_.emplace_back(new Weakness());
		weak_[weak_.size() - 1]->SetPlayerPosPtr(playerPosPtr_);
		weak_[weak_.size() - 1]->Init(weakPos, moveSpeed_);
	}

	for (auto& weak : weak_)
	{
		unit_.hp_ += weak->GetUnit().hp_;
	}

	smokeAnimIndex_ = 0.0f;
}

void Runboo::Update()
{
	
	smokeAnimIndex_ += 0.5f;
	if (smokeAnimIndex_ > SMOKE_IMAGE_NUM)
	{
		smokeAnimIndex_ = 0.0f;
	}

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
		for (const auto& w : weak_)
		{
			w->SetHardMode();
		}
		break;
	}

	BossBase::Update();

	const float noiseX = (GetRand(200) - 100) / 500.0f;
	unit_.nextpos_.x += sinf(weak_[0]->GetCnt()) * Weakness::AMPLITUDE + noiseX;

	int totalHP = 0;

	for (auto& w : weak_)
	{ 
		w->AttackManager(deadCount != 0);
		w->Update(unit_.pos_, moveSpeed_);
		w->Update();

		totalHP += w->GetUnit().hp_;
	}

	static int cnt = 0;;

	unit_.hp_ = totalHP;

	if (unit_.hp_ <= 0 &&
		!weak_[0]->GetUnit().isAlive_ &&
		!weak_[1]->GetUnit().isAlive_ &&
		!weak_[2]->GetUnit().isAlive_)
	{
		SceneManager::GetIns().Shake(SceneManager::DIAG,ShakeSize::BIG,20);
		cnt++;

		moveSpeed_ = 0;

		if (cnt > 180)
		{
			cnt = 0;
			ChangeState(STATE::DEATH);
		}
	}


	unit_.nextpos_.x += moveSpeed_;
}

void Runboo::Draw()
{
	Vector2F disp = { unit_.disppos_.x - 600.0f, unit_.disppos_.y - 16 };

	DrawRotaGraph(
		disp.x,
		disp.y,
		1.5f, 0.0f, image_,
		true, true
	);

	// ‹N“_À•W
	float baseX = unit_.disppos_.x;
	float baseY = unit_.disppos_.y + 300;

	// ƒ‰ƒ“ƒ_ƒ€”¼Œa‚ÆŠp“x‚ð‹‚ß‚é
	float radius = 100.0f; // ”¼Œa
	float angle = GetRand(359) * DX_PI_F / 180.0f;
	float dist = (float)GetRand((int)radius); // 0`”¼Œa‚Ü‚Å‚Ìƒ‰ƒ“ƒ_ƒ€‹——£

	// ‰~“à‚Ìƒ‰ƒ“ƒ_ƒ€À•W‚ðŽZo
	float randX = baseX + cosf(angle) * dist;
	float randY = baseY + sinf(angle) * dist;

		//// •`‰æ
		//DrawRotaGraph(
		//	(int)randX,
		//	(int)randY,
		//	0.2f, 0.0f,
		//	smokeImg_[(int)smokeAnimIndex_],
		//	true
		//);

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

	//for (int i = 0; i < SMOKE_IMAGE_NUM; i++)
	//{
	//	DeleteGraph(smokeImg_[i]);
	//}

}

void Runboo::DrawHp()
{
	for (int ii = 0; ii < WEAK_MAX; ii++)weak_[ii]->Draw();

	float hpSize = (Application::SCREEN_SIZE_X * 0.3f) / 2;
	float xCenter = Application::SCREEN_SIZE_X / 2;

	DrawBar(
		xCenter-hpSize,
		Application::SCREEN_SIZE_Y - 100,
		xCenter + hpSize,
		Application::SCREEN_SIZE_Y - 40,
		weak_[1]->GetUnit().hp_, Weakness::HP_MAX, RGB(0, 0, 150)
	);

	DrawBar(
		(xCenter - hpSize) - hpSize * 2,
		Application::SCREEN_SIZE_Y - 100,
		(xCenter + hpSize) - hpSize * 2,
		Application::SCREEN_SIZE_Y - 40,
		weak_[0]->GetUnit().hp_, Weakness::HP_MAX, RGB(0, 0, 150)
	);

	DrawBar(
		(xCenter - hpSize) + hpSize * 2,
		Application::SCREEN_SIZE_Y - 100,
		(xCenter + hpSize) + hpSize * 2,
		Application::SCREEN_SIZE_Y - 40,
		weak_[2]->GetUnit().hp_, Weakness::HP_MAX, RGB(0, 0, 150)
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



