#include "Nokopy.h"
#include"Attack/BamBeam.h"
#include"Attack/BamBreath.h"
#include"Attack/Wavemboo.h"
#include"Attack/Rushoot.h"

Nokopy::Nokopy()
{
}

Nokopy::~Nokopy()
{
}

void Nokopy::Init(void)
{
	BossBase::Init();
	unit_.isAlive_ = true;
	unit_.isDraw_ = true;
	unit_.nextpos_ = unit_.pos_ = { 1000,400 };
	unit_.size_ = { SIZE_X, SIZE_Y };
	unit_.radius_ = unit_.size_.x / 2;
	unit_.speed_ = 10.0f;
	unit_.hp_ = BOSS_HP;
	unit_.isCircle_ = true;
	isDive_ = false;
	ChangeState(BossBase::STATE::IDLE);
	idleCounter_ = 0;
	//-----------------------------------------------------------------
	//描画の初期化
	std::string path = "Data/Image/Boss/Nokopy/";
	img_[DRAW::DRAW_IDLE] = LoadGraph((path + "Idle.png").c_str());
	img_[DRAW::DRAW_BAMBEAM] = LoadGraph((path + "Beam.png").c_str());
	img_[DRAW::DRAW_BAMBREATH] = LoadGraph((path + "Breath.png").c_str());
	img_[DRAW::DRAW_WAVEMBOO] = LoadGraph((path + "Wave.png").c_str());
	img_[DRAW::DRAW_RUSHOOT] = LoadGraph((path + "Rush.png").c_str());

	DrawPat_ = DRAW_RUSHOOT;
	//-------------------------------------------------------------------
	//移動の初期化
	moveCounter_ = 0;
	dir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
	//------------------------------------------------------------------
	//攻撃の初期化
	//攻撃用インスタンスの実体化
	beam_ = new BamBeam();
	breath_ = new BamBreath();
	rush_ = new Rushoot();
	wave_ = new Wavemboo();
	attackState_ = NON;

	//攻撃パターン
	attackUpdateFuncs_ = {
		{BAMBEAM,&Nokopy::UpdateBamBeam},
		{BAMBREATH,&Nokopy::UpdateBamBreath},
		{RUSHOOT,&Nokopy::UpdateRushoot},
		{WAVEMBOO,&Nokopy::UpdateWavemboo}
	};
	attackCounter_ = 0;
	//------------------------------------------------------------------
}

void Nokopy::Update(void)
{
	BossBase::Update();
}

void Nokopy::Draw(void)
{
	if (unit_.isDraw_) {
		BossDraw();
	}
}

void Nokopy::Release(void)
{
	//画像の開放
	for (int i = 0; i < DRAW::DRAW_MAX; i++)DeleteGraph(img_[i]);
}

std::vector<Base> Nokopy::GetObj(void)
{
	std::vector<Base>ret;
	switch (attackState_)
	{
	case Nokopy::BAMBEAM:
		ret = beam_->Get();
		break;
	case Nokopy::BAMBREATH:
		ret = breath_->Get();
		break;
	case Nokopy::WAVEMBOO:
		ret = wave_->Get();
		break;
	case Nokopy::RUSHOOT:
		ret = rush_->Get();
		break;
	}
	return ret;

}

void Nokopy::SetDamage(int dmg)
{
	if (unit_.hp_ <= 0) return;

	unit_.hp_ -= dmg;
	//hitTimer_ = 10;
	unit_.inviCounter_ = 5;

	if (unit_.hp_ <= 0) {
		unit_.isAlive_ = false;
	}
}

void Nokopy::BossDraw(void)
{
	switch (DrawPat_)
	{
	case Nokopy::DRAW_IDLE:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, 0x0000ff, true);
		break;
	case Nokopy::DRAW_BAMBEAM:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, 0x00ff00, true);
		break;
	case Nokopy::DRAW_BAMBREATH:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, 0xff0000, true);
		break;
	case Nokopy::DRAW_WAVEMBOO:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, 0x000110, true);
		break;
	case Nokopy::DRAW_RUSHOOT:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, 0xffffff, true);
		break;
	}
}

void Nokopy::Idle(void)
{
	//出現用
	static int AppearanceCounter = 0;
	AppearanceCounter++;
	if (AppearanceCounter < 120)return;
	//行動後の暇
	idleCounter_++;
	if (idleCounter_ < 60)return;
	idleCounter_ = 0;
	//攻撃遷移
	if (moveCounter_ < 2) {
		ChangeState(BossBase::STATE::ATTACK);
		//ChangeAttackState(static_cast<ATTACK>(GetRand(static_cast<int>(ATTACK::MAX-1))));
		ChangeAttackState(static_cast < ATTACK>(4));
		return;
	}
	//移動遷移
	ChangeState(BossBase::STATE::MOVE);
}

void Nokopy::Move(void)
{
	moveCounter_++;
	if (moveCounter_ < 120)return;	//移動にかかる時間
	ChangeState(BossBase::STATE::IDLE);
	moveCounter_ = 0;
}

void Nokopy::Attack(void)
{
	attackCounter_++;
	//アタックの状態遷移
	auto it = attackUpdateFuncs_.find(attackState_);
 	(this->*(it->second))();

	//デバック用（アタックの状態を攻撃をしてないときの状態にする）
	if (CheckHitKey(KEY_INPUT_U) == 1) {
		state_ = BossBase::STATE::IDLE;
	}

	//バグが起きた時のための最終手段
	//（一定の時間を超えたら攻撃状態が強制的に終了する）
	if (attackCounter_ > 1000 || attackState_ == NON) {
		attackCounter_ = 0;
		state_ = BossBase::STATE::IDLE;
		attackState_ = NON;
	}
}

void Nokopy::Damage(void)
{
}

void Nokopy::Death(void)
{
}

void Nokopy::ChangeAttackState(ATTACK atc)
{
	moveCounter_++;
	attackState_ = atc;
	switch (attackState_)
	{
	case Nokopy::BAMBEAM:
		attackState_ = BAMBEAM;
		break;
	case Nokopy::BAMBREATH:
		attackState_ = BAMBREATH;
		break;
	case Nokopy::WAVEMBOO:
		attackState_ = WAVEMBOO;
		break;
	case Nokopy::RUSHOOT:
		attackState_ = RUSHOOT;
		break;
	}
}

void Nokopy::UpdateBamBeam(void)
{
	ChangeState(BossBase::STATE::IDLE);
}

void Nokopy::UpdateBamBreath(void)
{
	ChangeState(BossBase::STATE::IDLE);
}

void Nokopy::UpdateWavemboo(void)
{
	ChangeState(BossBase::STATE::IDLE);
}

void Nokopy::UpdateRushoot(void)
{
	ChangeState(BossBase::STATE::IDLE);
}

void Nokopy::IsGround(Collision::DIR dir)
{
	if (isDive_)return;
	switch (dir)
	{
	case Collision::UP:

		//天井に衝突していたら行う処理
		unit_.yAccel_ = 0;

		break;
	case Collision::DOWN:

		//地面に接地していたら行う処理
		unit_.yAccel_ = 0;

		//if (unit_.isGround_ == false) {
		//	unit_.isGround_ = true;
		//	SceneManager::GetInstance().SHAKE();
		//}
		unit_.isGravity_ = false;

		break;
	case Collision::LEFT:

		//左側の壁に衝突していたら行う処理
		unit_.xAccel_ = 0;
		break;

	case Collision::RIGHT:

		//右側の壁に衝突していたら行う処理
		unit_.xAccel_ = 0;

		break;
	}
}
