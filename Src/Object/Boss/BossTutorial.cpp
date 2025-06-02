#include"BossTutorial.h"


BossTutorial::BossTutorial()
{
}

BossTutorial::~BossTutorial()
{
}

void BossTutorial::Init()
{
	idolImg = LoadGraph("Data/Image/Boss/TutrialBoss.png");
	StartSlashtImg_ = LoadGraph("Data/Image/Boss/BossSlash.png");
	EndSlashImg_ = LoadGraph("Data/Image/Boss/BossSlashEnd.png");

	unit_.isAlive_ = true;
	unit_.isDraw_ = true;
	unit_.pos_ = { 4500,250 };
	unit_.nextpos_ = unit_.pos_;
	unit_.radius_ = 0;
	unit_.size_ = { 240, 249};
	unit_.speed_ = 10.0f;

	pattaern_ = E_NON;
	attackState_ = NON;
	attackCounter_ = 0;
	targetIndex_ = 2;
	encount_ = false;

	slash_ = new Slash();
	bullet_ = new Bullet();
	tackle_ = new Tackle();

	DrawPat_ = NORMAL;
}

void BossTutorial::Update()
{
	unit_.isGravity_ = true;
	if (EnCount())encount_ = true;

	if (encount_) {
		PattaernManager();
	}


	EnemyBase::Update();
}

void BossTutorial::Draw()
{
	if (unit_.isDraw_)
	{
		bullet_->Draw();

		switch (DrawPat_)
		{
		case NORMAL:
			// 通常状態
			DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, 1.0f, 0.0f, idolImg, true, bossDir_);
			break;
		case E_SLASH_START:
			// 剣を振り上げる
			DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, 1.0f, 0.0f, StartSlashtImg_, true, bossDir_);
			break;
		case E_SLASH_END:
			// 剣を振り下ろす
			DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y + 14, 1.0f, 0.0f, EndSlashImg_, true, bossDir_);
			break;
		}

		slash_->Draw();

		
		//DrawBox(unit_.disppos_.x - 70, unit_.disppos_.y - 120, unit_.disppos_.x + 70, unit_.disppos_.y + 120, 0xfffff0, true);
	}
	DrawFormatString(120, 120, 0x0fffff, "boss(%.2f,%.2f)", unit_.nextpos_.x, unit_.nextpos_.y);
}

void BossTutorial::Release()
{
	bullet_->Release();
	delete bullet_;

	slash_->Release();
	delete slash_;

	tackle_->Release();
	delete tackle_;

	//画像の開放
	DeleteGraph(idolImg);
	DeleteGraph(StartSlashtImg_);
	DeleteGraph(EndSlashImg_);
}

void BossTutorial::PattaernManager(void)
{
	switch (pattaern_)
	{
	case BossTutorial::E_NON:
		switch (targetIndex_)
		{
		case 0:
		case 2:
			targetIndex_ = 1;	//真ん中へ
			break;
		case 1:
			targetIndex_ = GetRand(1);
			targetIndex_ *= 2;	//右か左へ
			break;
		}

		if (targetIndex_ == 0)
		{
			bossDir_ = AttackBase::DIR::LEFT;
		}
		else if (targetIndex_ == 2)
		{
			bossDir_ = AttackBase::DIR::RIGHT;
		}

		attackCounter_ = 0;
		pattaern_ = E_MOVE;

		break;

	case BossTutorial::E_MOVE:
		Move();
		break;
	case BossTutorial::E_ATTACK:
		Attack();
		break;
	}
}


bool BossTutorial::EnCount(void)
{
	Vector2F vec = { player_->GetUnit().pos_.x - unit_.nextpos_.x,player_->GetUnit().pos_.y - unit_.nextpos_.y };

	float distance = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (distance < 500.0f)return true;

	return false;
}


void BossTutorial::Move()
{
	Vector2F point = BOSS_POINT[targetIndex_];

	DrawPat_ = NORMAL;

	if (attackCounter_ == 0) {
		Vector2F d = { point.x - unit_.nextpos_.x, point.y - unit_.nextpos_.y };
		float t = d.x / unit_.speed_;
		if (t <= 0.0f) t *= -1;
		float jumppower = (d.y + 0.5f * gravity_ * t * t) / t;
		unit_.yAccel_ -= jumppower;
	}


	if (targetIndex_ == 0)
	{
		bossDir_ = AttackBase::DIR::LEFT;
	}
	else if (targetIndex_ == 2)
	{
		bossDir_ = AttackBase::DIR::RIGHT;
	}


	attackCounter_++;

	unit_.nextpos_.x += GetMoveVec(unit_.nextpos_, point, unit_.speed_).x;


	if (GetDis(unit_.nextpos_, point) <= unit_.speed_) {
		attackCounter_ = 0;
		attackState_ = (ATTACK)GetRand(1);
		pattaern_ = E_ATTACK;
	}
}


void BossTutorial::Attack()
{
	switch (attackState_)
	{
	case BossTutorial::SLASH:

		if (attackCounter_ == 0) {
			panVec_ = { 0.0f,0.0f };
			slash_->Init(&unit_.pos_);
			DrawPat_ = E_SLASH_START;

		}

		if (attackCounter_ == Slash::CHARGE - 1) {
			target_ = player_->GetUnit().pos_;

			Slash::DIR dir;

			if (target_.x <= unit_.pos_.x) {
				dir = Slash::DIR::LEFT;
				bossDir_ = AttackBase::DIR::LEFT;
			}
			else {
				dir = Slash::DIR::RIGHT;
				bossDir_ = AttackBase::DIR::RIGHT;
			}

			slash_->SetTarget(dir);
		}

		if (attackCounter_ == Slash::CHARGE) {
			panVec_ = GetMoveVec(unit_.pos_,target_, unit_.speed_ * 3.0f);
		}

		if (!(panVec_.x == 0.0f && panVec_.y == 0.0f)) {

			unit_.isGravity_ = false;

			float dis = target_.x - unit_.nextpos_.x;
			if (dis < 0)dis *= -1;
			if (dis <= player_->GetUnit().size_.x / 2 + unit_.size_.x / 2) {
				panVec_ = { 0.0f,0.0f };
				slash_->On();
				DrawPat_ = E_SLASH_END;
			}

		}

		unit_.nextpos_ += panVec_;

		if (slash_->End()) {
			attackCounter_ = 0;
			unit_.isGravity_ = true;
			pattaern_ = E_NON;
			attackState_ = NON;
		}

		slash_->Update();

		break;
	case BossTutorial::BULLET:

		if (attackCounter_ == 0) {
			bullet_->Init(&unit_.pos_);
		}

		if (bullet_->End()) {
			attackCounter_ = 0;
			pattaern_ = E_NON;
			attackState_ = NON;
		}

		bullet_->Update();
		break;
	case BossTutorial::ROAR:

		break;
	case BossTutorial::BLAST:

		break;
	case BossTutorial::TACKLE:
		
		break;
	}
	attackCounter_++;
	if (CheckHitKey(KEY_INPUT_U) == 1) {
		pattaern_ = E_NON;
	}

}


void BossTutorial::IsGround(Collision::DIR dir)
{
	switch (dir)
	{
	case Collision::UP:

		//天井に衝突していたら行う処理
		unit_.yAccel_ = 0;

		break;

	case Collision::DOWN:

		//地面に接地していたら行う処理
		unit_.yAccel_ = 0;

		if (unit_.isGround_==false) {
			unit_.isGround_ = true;
			SceneManager::GetInstance().SHAKE();
		}
		unit_.isGravity_ = false;

		if (player_->GetUnit().pos_.x <= unit_.pos_.x) bossDir_ = AttackBase::DIR::LEFT;
		else										   bossDir_ = AttackBase::DIR::RIGHT;
		

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


const std::vector<Base> BossTutorial::GetObjAttack(const ATTACK state) const
{
	std::vector<Base>ret;

	switch (state)
	{
	case BossTutorial::NON:
		break;
	case BossTutorial::SLASH:
		ret = slash_->Get();
		break;
	case BossTutorial::BULLET:
		ret = bullet_->Get();
		break;
	case BossTutorial::ROAR:
		break;
	case BossTutorial::BLAST:
		break;
	case BossTutorial::TACKLE:
		break;
	case BossTutorial::MAX:
		break;
	}

	return ret;
}