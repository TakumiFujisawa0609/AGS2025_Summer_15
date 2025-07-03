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
	unit_.nextpos_ = unit_.pos_ = { SPAWN_POS_RIGHT,SPAWN_POS_Y };
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
	if (unit_.inviCounter_ > 0)unit_.inviCounter_--;
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

AttackBase* Nokopy::GetAttackIns(void)
{
	switch (attackState_)
	{
	case Nokopy::NON:
		break;
	case Nokopy::BAMBEAM:
		return beam_;
	case Nokopy::BAMBREATH:
		return breath_;
	case Nokopy::WAVEMBOO:
		return wave_;
	case Nokopy::RUSHOOT:
		return rush_;
	}
	return nullptr;
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

void Nokopy::ObjHit(int i)
{
	switch (attackState_)
	{
	case Nokopy::BAMBEAM:
		break;
	case Nokopy::BAMBREATH:
		break;
	case Nokopy::WAVEMBOO:
		break;
	case Nokopy::RUSHOOT:
		break;
	}

}

void Nokopy::BossDraw(void)
{
	switch (DrawPat_)
	{
	case Nokopy::DRAW_IDLE:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(255,255,255), true);
		break;
	case Nokopy::DRAW_MOVE:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(255, 255, 0), true);
		break;
	case Nokopy::DRAW_BAMBEAM:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(255,0,0), true);
		break;
	case Nokopy::DRAW_BAMBREATH:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(0,255,0), true);
		break;
	case Nokopy::DRAW_WAVEMBOO:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(0,255,255), true);
		break;
	case Nokopy::DRAW_RUSHOOT:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(0,0,255), true);
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
	if (idleCounter_ < 120)return;
	idleCounter_ = 0;
	//攻撃遷移
	if (moveCounter_ < 2) {
		ChangeState(BossBase::STATE::ATTACK);
		ChangeAttackState(static_cast<ATTACK>(GetRand(static_cast<int>(ATTACK::MAX - 1))));
		return;
	}
	//移動遷移
	ChangeState(BossBase::STATE::MOVE);
	DrawPat_ = DRAW_MOVE;
}

void Nokopy::Move(void)
{
	moveCounter_++;
	if (moveCounter_ < 30)
	{
		isDive_ = true;
		unit_.isStageCollision_ = false;
		unit_.nextpos_.y += (unit_.pos_.y <= Application::SCREEN_SIZE_Y) ? unit_.speed_ : 0;
	}
	else if (moveCounter_ < 210)
	{
		//目標とする座標のXまで移動
		switch (dir_)
		{
		case AsoUtility::DIRECTION::E_DIR_RIGHT:
			unit_.nextpos_.x += (unit_.pos_.x <= SPAWN_POS_RIGHT) ? unit_.speed_ : 0;
			break;
		case AsoUtility::DIRECTION::E_DIR_LEFT:
			unit_.nextpos_.x -= (unit_.pos_.x >= SPAWN_POS_LEFT) ? unit_.speed_ : 0;
			break;
		}
	}
	else if (moveCounter_ >210)
	{
		//目標とする座標のYまで移動
		unit_.nextpos_.y -= (unit_.pos_.y > SPAWN_POS_Y) ? unit_.speed_ : 0;
	}
	//目標座標についたら遷移
	if (unit_.pos_.y <= SPAWN_POS_Y) {
		switch (dir_)
		{
		case AsoUtility::DIRECTION::E_DIR_RIGHT:
			dir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
			break;
		case AsoUtility::DIRECTION::E_DIR_LEFT:
			dir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;
			break;
		}
	isDive_ = false;
	unit_.isStageCollision_ = true;
	unit_.isGravity_ = true;
	moveCounter_ = 0;
	ChangeState(BossBase::STATE::IDLE);
	DrawPat_ = DRAW_IDLE;
	}
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
	if (unit_.hp_ <= 0) {
		ChangeState(BossBase::STATE::DEATH);
	}
}

void Nokopy::ChangeAttackState(ATTACK atc)
{
	moveCounter_++;
	attackState_ = atc;
	switch (attackState_)
	{
	case Nokopy::BAMBEAM:
		attackState_ = BAMBEAM;
		DrawPat_ = DRAW_BAMBEAM;
		break;
	case Nokopy::BAMBREATH:
		attackState_ = BAMBREATH;
		DrawPat_ = DRAW_BAMBREATH;
		break;
	case Nokopy::WAVEMBOO:
		attackState_ = WAVEMBOO;
		DrawPat_ = DRAW_WAVEMBOO;
		break;
	case Nokopy::RUSHOOT:
		attackState_ = RUSHOOT;
		DrawPat_ = DRAW_RUSHOOT;
		break;
	}
}

void Nokopy::UpdateBamBeam(void)
{
	if (attackCounter_ == 1)beam_->Init(&unit_.pos_);

	if (attackCounter_ > 120) {

		ChangeState(BossBase::STATE::IDLE);
	}
}

void Nokopy::UpdateBamBreath(void)
{
	if (attackCounter_ == 1)breath_->Init(&unit_.pos_);

	if (attackCounter_ > 120) {
		ChangeState(BossBase::STATE::IDLE);

	}
}

void Nokopy::UpdateWavemboo(void)
{
	if (attackCounter_ == 1)wave_->Init(&unit_.pos_);

	if (attackCounter_ > 120) {
		ChangeState(BossBase::STATE::IDLE);

	}
}

void Nokopy::UpdateRushoot(void)
{
	if (attackCounter_ == 1)rush_->Init(&unit_.pos_);
	if (attackCounter_ > 120) {
		ChangeState(BossBase::STATE::IDLE);

	}
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
