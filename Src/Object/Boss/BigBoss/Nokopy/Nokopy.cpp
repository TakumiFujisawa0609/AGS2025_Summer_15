
#include <algorithm> 
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
	img_[DRAW::DRAW_KNOCKBACK] = LoadGraph((path + "Damage.png").c_str());
	img_[DRAW::DRAW_DEATH]= LoadGraph((path + "Damage.png").c_str());

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
	spine_ = new Spine();
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
	auto& p = playerPosPtr_;
	//if (unit_.pos_.x >p->x)
	//{
	//	dir_ = AsoUtility::DIRECTION::E_DIR_LEFT;
	//}
	//else {
	//	dir_ = AsoUtility::DIRECTION::E_DIR_RIGHT;
	//}
	if (state_ == STATE::DEATH) {
		unit_.isAlive_ = false;
	}
}

void Nokopy::Draw(void)
{
	if (targetLine_) {
		DrawLine(unit_.pos_.x, unit_.pos_.y, targetPos_.x+10, targetPos_.y+10, GetColor(0, 255, 30));
	}
	if (unit_.isAlive_) {
		BossDraw();
		beam_->Draw();
		wave_->Draw();
		spine_->Draw();
	}
}

void Nokopy::Release(void)
{
	//画像の開放
	for (int i = 0; i < DRAW::DRAW_MAX; i++) DeleteGraph(img_[i]);

	// 攻撃用インスタンスの解放
	if (beam_) {
		beam_->Release();
		delete beam_;
		beam_ = nullptr;
	}
	if (rush_) {
		rush_->Release();
		delete rush_;
		rush_ = nullptr;
	}
	if (wave_) {
		wave_->Release();
		delete wave_;
		wave_ = nullptr;
	}
	if (spine_) {
		spine_->Release();
		delete spine_;
		spine_ = nullptr;
	}
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
	unit_.inviCounter_ = 30;

	if (unit_.hp_ <= 0) {
		auto& mana = SceneManager::GetInstance();
		mana.HitStop(60);
		mana.ZoomPos(unit_.pos_);
		mana.ZoomScale(2.0f);
		DrawPat_ = DRAW::DRAW_DEATH;
		ChangeState(STATE::DEATH);
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
		int d = 0;
		d= (dir_ == AsoUtility::DIRECTION::E_DIR_RIGHT) ? 1 : 0;
	switch (DrawPat_)
	{
	case Nokopy::DRAW_IDLE:
        DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 0.22, 0.0, img_[DRAW_IDLE], true,d);
		break;
	case Nokopy::DRAW_MOVE:
		DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 0.2, 0.0, img_[DRAW_RUSHOOT], true);
		break;
	case Nokopy::DRAW_BAMBEAM:
		DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 0.22, 0.0, img_[DRAW_IDLE], true);
		break;
	case Nokopy::DRAW_WAVEMBOO:
		DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 0.22, 0.0, img_[DRAW_IDLE], true);
		break;
	case Nokopy::DRAW_RUSHOOT:
		DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 0.2, angle_, img_[DRAW_RUSHOOT], true);
		break;
	case Nokopy::DRAW_SPINE:
		DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 0.22, 0.0, img_[DRAW_IDLE], true);
		break;

	case Nokopy::DRAW_KNOCKBACK:
		DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 0.22, 0, img_[DRAW_KNOCKBACK], true);
		break;
	case Nokopy::DRAW_DEATH:
		DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 0.22, 0, img_[DRAW_DEATH], true);
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
		ChangeAttackState(BAMBEAM);
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
	DrawPat_ = DRAW::DRAW_KNOCKBACK;
	static int counter = 0;
	counter++;
	if (counter > 15) {
		isDive_ = false;
		unit_.isStageCollision_ = true;
	}

	if (counter > 120) {
		DrawPat_ = DRAW::DRAW_IDLE;
		ChangeState(STATE::IDLE);
		counter = 0;
	}
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
	case Nokopy::SPINE:
		attackState_ = SPINE;
		DrawPat_ = DRAW_SPINE;
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
   Vector2F centerPos = { Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2 };
   static Vector2F vecN = { 0, 0 };

   if (isRushReflection_) {
       unit_.isGravity_ = true;
       attackCounter_ = 0;
       vecN = { 0, 0 };
       num = 0;
       SetDown(*playerPosPtr_);
       ChangeState(STATE::DAMAGE);
	   angle_ = 0;
   }
   if (num >= 5) {
       unit_.nextpos_.x = SPAWN_POS_RIGHT;
       unit_.nextpos_.y = SPAWN_POS_Y;
       attackCounter_ = 0;
       vecN = { 0, 0 };
       num = 0;
	   angle_ = 0;
       ChangeState(STATE::IDLE);
   }
   if (attackCounter_ == 0) {
       rush_->Init(&unit_.pos_);
   } else if (attackCounter_ < 30) {
       isDive_ = true;
       unit_.isStageCollision_ = false;
       unit_.nextpos_.y += (unit_.pos_.y <= Application::SCREEN_SIZE_Y) ? unit_.speed_ : 0;
   } else if (attackCounter_ < 31) {
       Vector2F pos = ShapesPosition::GetOnePositionCircle(centerPos.x, centerPos.y, Application::SCREEN_SIZE_X / 2, GetRand(AsoUtility::Deg2RadF(360)));
       unit_.nextpos_ = pos;
       // targetPosを延長上に伸ばす
       Vector2F playerPos = *playerPosPtr_;
       targetVec_ = playerPos - pos;
       float length = sqrtf(targetVec_.x * targetVec_.x + targetVec_.y * targetVec_.y);
       vecN = targetVec_ / length;
        // 角度をunit_.pos_からplayerPosへのベクトルで計算
        angle_ = atan2(playerPos.y - pos.y, playerPos.x - pos.x);
		angle_ += AsoUtility::Deg2RadF(90);
       // 画面外まで延長（例: 画面対角線の2倍分延長）
       float extendLength =Application::SCREEN_SIZE_X * 2.0f;
       targetPos_ = pos + vecN * extendLength;
   } else if (attackCounter_ < 50) {
       targetLine_ = true;
   } else if (attackCounter_ < 120) {
       targetLine_ = false;
       unit_.nextpos_ += vecN * unit_.speed_ * (num + 2);
   } else {
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
		attackCounter_ = 0;

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
