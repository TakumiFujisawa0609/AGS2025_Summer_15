#include<cmath>
#include "Nokopy.h"
#include"Attack/BamBeam.h"
#include"Attack/Wavemboo.h"
#include"Attack/Rushoot.h"
#include"Attack/Spine.h"
#include"../../../../Utility/ShapesPosition.h"

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
	isRushReflection_ = false;
	ChangeState(BossBase::STATE::IDLE);
	idleCounter_ = 0;
	//-----------------------------------------------------------------
	//描画の初期化
	std::string path = "Data/Image/Boss/Nokopy/";
	img_[DRAW::DRAW_IDLE] = LoadGraph((path + "Idle.png").c_str());
	img_[DRAW::DRAW_BAMBEAM] = LoadGraph((path + "Beam.png").c_str());
	img_[DRAW::DRAW_WAVEMBOO] = LoadGraph((path + "Wave.png").c_str());
	img_[DRAW::DRAW_RUSHOOT] = LoadGraph((path + "Rush.png").c_str());
	img_[DRAW::DRAW_SPINE] = LoadGraph((path + "Spine.png").c_str());

	DrawPat_ = DRAW_IDLE;
	//-------------------------------------------------------------------
	//移動の初期化
	moveCounter_ = 0;
	dir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
	//------------------------------------------------------------------
	//攻撃の初期化
	//攻撃用インスタンスの実体化
	beam_ = new BamBeam();
	rush_ = new Rushoot();
	wave_ = new Wavemboo();
	attackState_ = NON;
	targetPos_ = { 0.0f,0.0f };
	//攻撃パターン
	attackUpdateFuncs_ = {
		{BAMBEAM,&Nokopy::UpdateBamBeam},
		{RUSHOOT,&Nokopy::UpdateRushoot},
		{WAVEMBOO,&Nokopy::UpdateWavemboo},
		{SPINE,&Nokopy::UpdateSpine}
	};
	attackCounter_ = 0;
	//------------------------------------------------------------------
}

void Nokopy::Update(void)
{
	if (!unit_.isAlive_)return;
	BossBase::Update();
	if (unit_.inviCounter_ > 0)unit_.inviCounter_--;
}

void Nokopy::Draw(void)
{
	if (unit_.isAlive_) {
		BossDraw();
		beam_->Draw();
		wave_->Draw();
	}
	if (targetLine_) {
		DrawLine(unit_.pos_.x, unit_.pos_.y, targetPos_.x+10, targetPos_.y+10, GetColor(0, 255, 30));
	}
	DrawHp();
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
	case Nokopy::WAVEMBOO:
		ret = wave_->Get();
		break;
	case Nokopy::RUSHOOT:
		ret = rush_->Get();
		break;
	case Nokopy::SPINE:
		ret = spine_->Get();
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
	case Nokopy::WAVEMBOO:
		return wave_;
	case Nokopy::RUSHOOT:
		return rush_;
	case Nokopy::SPINE:
		return spine_;
	}
	return nullptr;
}

int Nokopy::GetAttackState(void)
{
	return attackState_;
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
		beam_->Hit();
		break;
	case Nokopy::WAVEMBOO:
		wave_->Hit(i);
		break;
	case Nokopy::RUSHOOT:
		break;
	case Nokopy::SPINE:
		spine_->Hit(i);
	}

}

void Nokopy::BossDraw(void)
{
	switch (DrawPat_)
	{
	case Nokopy::DRAW_IDLE:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(255, 255, 255), true);
		break;
	case Nokopy::DRAW_MOVE:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(255, 255, 0), true);
		break;
	case Nokopy::DRAW_BAMBEAM:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(255, 0, 0), true);
		break;
	case Nokopy::DRAW_WAVEMBOO:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(0, 255, 255), true);
		break;
	case Nokopy::DRAW_RUSHOOT:
		DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.radius_, GetColor(0, 0, 255), true);
		break;
	}
}

void Nokopy::Idle(void)
{
	DrawPat_ = DRAW_IDLE;
	isDive_ = false;
	unit_.isStageCollision_ = true;
	unit_.isGravity_ = true;
	isRushReflection_ = false;
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
		attackCounter_ = 0;
		ChangeState(BossBase::STATE::ATTACK);
		//ChangeAttackState(static_cast<ATTACK>(GetRand(static_cast<int>(ATTACK::MAX - 1))));
		ChangeAttackState(WAVEMBOO);
		return;
	}
	//移動遷移
	ChangeState(BossBase::STATE::MOVE);
	DrawPat_ = DRAW_MOVE;
}
void Nokopy::DrawHp(void)
{
	Vector2 start, end, size;
	size = { 800,50 };
	end = { Application::SCREEN_SIZE_X - 5,Application::SCREEN_SIZE_Y - 20 };
	start = end - size;
	DrawBar(start.x, start.y, end.x, end.y, unit_.hp_, BOSS_HP, RGB(0, 255, 255));
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
	else if (moveCounter_ > 210)
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
	//アタックの状態遷移
	auto it = attackUpdateFuncs_.find(attackState_);
	(this->*(it->second))();
	attackCounter_++;

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
	static int counter = 0;
	counter++;
	if (counter > 15) {
		isDive_ = false;
		unit_.isStageCollision_ = true;
	}
	if (unit_.yAccel_ == 0) {
	ChangeState(STATE::IDLE);

	}
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
	if (attackCounter_ == 1) {
		beam_->Init(&unit_.pos_);
		beam_->LookOn(*playerPosPtr_);
	}
	if (attackCounter_ > 1) {
		beam_->Update();
	}
	if (attackCounter_ > 120) {
		beam_->Off();
		ChangeState(BossBase::STATE::IDLE);

	}
}



void Nokopy::UpdateWavemboo(void)
{
	if (attackCounter_ == 0) {
		wave_->Init(&unit_.pos_);
		wave_->LookOn(*playerPosPtr_);
	}
	if (attackCounter_ > 1) {
		wave_->Update();
	}
	if (attackCounter_ > 300) {
		ChangeState(BossBase::STATE::IDLE);
		wave_->Off();

	}
}

void Nokopy::UpdateRushoot(void)
{
	static int num = 0;
	static int rushCounter = 0;
	Vector2F centerPos = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 2 };
	static Vector2F vecN = { 0,0 };

	if (isRushReflection_) {

		unit_.isGravity_ = true;
		attackCounter_ = 0;
		vecN = { 0,0 };
		num = 0;
		SetDown(*playerPosPtr_);
		ChangeState(STATE::DAMAGE);
	}
	if (num >= 5) {
		unit_.nextpos_.x = SPAWN_POS_RIGHT;
		unit_.nextpos_.y = SPAWN_POS_Y;
		attackCounter_ = 0;
		vecN = { 0,0 };
		num = 0;
		ChangeState(STATE::IDLE);
	}
	if (attackCounter_ == 0) {
		rush_->Init(&unit_.pos_);
	}else if (attackCounter_ < 30) {
		isDive_ = true;
		unit_.isStageCollision_ = false;
		unit_.nextpos_.y += (unit_.pos_.y <= Application::SCREEN_SIZE_Y) ? unit_.speed_ : 0;
	}else if (attackCounter_ < 31) {
	Vector2F pos = ShapesPosition::GetOnePositionCircle(centerPos.x, centerPos.y, Application::SCREEN_SIZE_X / 2, GetRand(AsoUtility::Deg2RadF(360)));
	unit_.nextpos_ = pos;
	targetPos_ = *playerPosPtr_;
	targetVec_ = targetPos_ - pos;
	float length =sqrtf(targetVec_.x * targetVec_.x + targetVec_.y * targetVec_.y);
	vecN = targetVec_ / length;
	}else if (attackCounter_ <50) {
		targetLine_ = true;
	}else if (attackCounter_ <120) {
		targetLine_ = false;
		unit_.nextpos_ += vecN*unit_.speed_*(num+1);
	}else{
	num++;
	attackCounter_ = 0;
	}

	rush_->Update();

}

void Nokopy::UpdateSpine(void)
{
	if (attackCounter_ == 0)spine_->Init(&unit_.pos_);
	if (attackCounter_ > 1) {
		spine_->Update();
	}
	if (attackCounter_ > 180) {
		ChangeState(BossBase::STATE::IDLE);
		spine_->Off();
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
