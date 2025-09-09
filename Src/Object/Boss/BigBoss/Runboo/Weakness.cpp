#include "Weakness.h"
#include"../../../UnitBase.h"
#include"../../../../Manager/Camera.h"
#include"Attack/WeakBullet.h"
#include"Attack/Laser.h"
#include"Attack/Pillar.h"
#include"Attack/Bound.h"
#include"Attack/Spiral.h"

Weakness::Weakness()
{
	bullet_ = nullptr;
	laser_ = nullptr;
	bound_ = nullptr;
	spiral_ = nullptr;
}

Weakness::~Weakness()
{
}

//初期化
void Weakness::Init(Vector2F disppos, float moveSpeed)
{
	BossBase::Init();
	moveSpeed_ = moveSpeed;

	Camera::CreateInstance();

	//画像の読み込み
	image_ = LoadGraph((Application::PATH_IMAGE + "Boss/Runboo/Weakness.png").c_str());

	//変数の初期化
	cnt_ = GetRand(16.0f);
	attackCounter_ = 0;

	//unit_.pos_ + start_;
	unit_.hp_ = HP_MAX;
	unit_.isAlive_ = true;
	unit_.size_ = { SIZE_X,SIZE_Y };
	unit_.radius_ = 64.0f;
	unit_.nextpos_ = disppos;
	unit_.pos_ = unit_.nextpos_;
	ChangeDispPos();

	ChangeState(STATE::ATTACK);

	unit_.isGravity_ = false;
	unit_.isStageCollision_ = false;

	attack_ = ATTACK::NON;

	//インスタンスの初期化
	bullet_ = new WeakBullet(moveSpeed_);
	bullet_->Init(&unit_.pos_);

	laser_ = new Laser(moveSpeed_);

	pillar_ = new Pillar(moveSpeed_);
	//pillar_->Init(&unit_.pos_);

	bound_ = new Bound(moveSpeed_);

	spiral_ = new Spiral(moveSpeed_);

	laser_->SetTarget(playerPosPtr_);
	pillar_->SetTarget(playerPosPtr_);

}

void Weakness::Init(void) {}

void Weakness::Update(Vector2F boss, float moveSpeed)
{
	if (!unit_.isAlive_)return;
	unit_.nextpos_.x = boss.x;
	moveSpeed_ = moveSpeed;
}

void Weakness::Update() 
{
	// カウント更新
	cnt_ += 0.1f;


	// ランダムにゆらゆら動く
	const float noiseY = (GetRand(200) - 100) / 500.0f;
	const float noiseX = (GetRand(200) - 100) / 500.0f;

	// 元の位置から縦にゆらゆら動かす
	unit_.nextpos_.x += sinf(cnt_) * AMPLITUDE + noiseX;
	unit_.nextpos_.y += cosf(cnt_ * 0.8f) * AMPLITUDE + noiseY;

	if (unit_.inviCounter_ > 0)
	{
		unit_.inviCounter_--;
	}

	if (unit_.hp_ <= 0)
	{
		if (unit_.hp_ <= 0) {
			unit_.isAlive_ = false;
		}

		ChangeState(STATE::DEATH);
	}
	bullet_->Update(unit_.pos_, moveSpeed_);

	BossBase::Update();

	if (CheckHitKey(KEY_INPUT_0))unit_.hp_--;

}

void Weakness::Draw()
{
	//DrawRotaGraph3(
	//	unit_.disppos_.x,
	//	unit_.disppos_.y,
	//	180,170,
	//	1.0f,1.0f, 0.0f,
	//	image_, true
	//);

	if (unit_.inviCounter_ > 0) {
		// 点滅（5フレームごとに表示・非表示）
		if ((unit_.inviCounter_ / 5) % 2 == 0) {
			// 赤く光る
			SetDrawBlendMode(DX_BLENDMODE_ADD, 180);
			DrawRotaGraph3(
				unit_.disppos_.x,
				unit_.disppos_.y,
				180, 170,
				1.0f, 1.0f, 0.0f,
				image_, true
			);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else {
		// 通常描画
		DrawRotaGraph3(
			unit_.disppos_.x,
			unit_.disppos_.y,
			180, 170,
			1.0f, 1.0f, 0.0f,
			image_, true
		);
	}

	if (!unit_.isAlive_)return;

	bullet_->Draw();
	laser_->Draw();
	pillar_->Draw();
	bound_->Draw();
	spiral_->Draw();
}

void Weakness::Release()
{
	bullet_->Release();
	delete bullet_;
	bullet_ = nullptr;

	laser_->Release();
	delete laser_;
	laser_ = nullptr;

	pillar_->Release();
	delete pillar_;
	pillar_ = nullptr;

	bound_->Release();
	delete bound_;
	bound_ = nullptr;

	spiral_->Release();
	delete spiral_;
	spiral_ = nullptr;

	DeleteGraph(image_);

	Camera::DeleteInstance();
}

AttackBase* Weakness::GetAttackIns(void)
{
	return nullptr;
}

std::vector<Base> Weakness::GetObj(void)
{
	std::vector<Base> ret;

	switch (attack_)
	{
	case ATTACK::NON:
		break;
	case ATTACK::LASER:
		ret = laser_->Get();
		break;
	case ATTACK::PILLAR:
		ret = pillar_->Get();
		break;
	case ATTACK::BOUND:
		ret = bound_->Get();
		break;
	case ATTACK::SPIRAL:
		ret = spiral_->Get();
		break;
	case ATTACK::MAX:
		break;
	}

	return ret;
}

std::vector<Base> Weakness::GetBulletObj(void)
{
	return bullet_->Get();
}

void Weakness::BulltHit(int i)
{
	bullet_->Hit(i); 
}

void Weakness::ObjHit(int i)
{
	//bullet_->Hit();

	switch (attack_)
	{
	case ATTACK::NON:
		break;
	case ATTACK::LASER:
		laser_->Hit(i);
		break;
	case ATTACK::PILLAR:
		pillar_->Hit(i);
		break;
	case ATTACK::BOUND:
		bound_->Hit(i);
		break;
	case ATTACK::SPIRAL:
		spiral_->Hit(i);
		break;
	case ATTACK::MAX:
		break;
	}
}

void Weakness::SetDamage(int dmg)
{
	if (unit_.hp_ <= 0 || unit_.isInvincible_) return;

	unit_.hp_ -= dmg;
	unit_.inviCounter_ = INVI_COUNTER;
}

void Weakness::AttackManager(bool isHard)
{


	if (attack_ == ATTACK::NON && ((isHard) ? attackCounter_ > 320 : attackCounter_ > 120))
	{
		attack_ = (ATTACK)GetRand((int)(ATTACK::MAX) - 1);
		attackCounter_ = 0;
	}
}

void Weakness::Idle(void)
{

}

void Weakness::Move(void)
{
}

void Weakness::Attack(void)
{
	switch (attack_)
	{
	case Weakness::NON:
		attackCounter_++;
		break;
	case Weakness::LASER:

		attackCounter_++;

		if (attackCounter_ <= 1)
		{
			laser_->Init(&unit_.pos_);
		}
		
		laser_->Update(unit_.pos_);

		if (laser_->End() == true)
		{
			attack_= ATTACK::NON;
			attackCounter_ = 0;
		}
		break;
	case Weakness::ATTACK::PILLAR:
		attackCounter_++;
		if (attackCounter_ <= 1)
		{
			pillar_->Init(&unit_.pos_);
		}
		pillar_->Update(unit_.pos_);

		if (pillar_->End())
		{
			attack_ = ATTACK::NON;
			attackCounter_ = 0;
		}
		break;
	case Weakness::ATTACK::BOUND:
 		attackCounter_++;
		if (attackCounter_ <= 1)
		{
			bound_->Init(&unit_.pos_);
		}

		bound_->Update(unit_.pos_);

		if (bound_->End())
		{
			attack_ = ATTACK::NON;
			attackCounter_ = 0;
		}
		break;
	case ATTACK::SPIRAL:
		attackCounter_++;
		if (attackCounter_ <= 1)
		{
			spiral_->Init(&unit_.pos_);
		}

		spiral_->Update(unit_.pos_);

		if (spiral_->End())
		{
			attack_ = ATTACK::NON;
			attackCounter_ = 0;
		}
		break;
	}
}

void Weakness::Damage(void)
{


}

//死んだ後の処理
void Weakness::Death(void)
{
	auto& camera_ = Camera::GetInstance();

	unit_.pos_.x += moveSpeed_;

	unit_.pos_.x += camera_.GetPos().x + Application::SCREEN_SIZE_X / 2;
}
