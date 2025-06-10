#include"BossTutorial.h"


BossTutorial::BossTutorial()
{
}

BossTutorial::~BossTutorial()
{
}

void BossTutorial::Init()
{
	img_[DRAWPAT::NORMAL] = LoadGraph("Data/Image/Boss/TutrialBoss.png");
	img_[DRAWPAT::E_SLASH_START] = LoadGraph("Data/Image/Boss/BossSlash.png");
	img_[DRAWPAT::E_SLASH_END] = LoadGraph("Data/Image/Boss/BossSlashEnd.png");

	unit_.isAlive_ = true;
	unit_.isDraw_ = true;
	unit_.pos_ = { 4500,250 };
	unit_.nextpos_ = unit_.pos_;
	unit_.radius_ = 0;
	unit_.size_ = { 240, 249 };
	unit_.speed_ = 10.0f;
	unit_.hp_ = BOSS_HP;
	hpShakeTimer_ = 0;  // 揺れ時間（フレーム数）
	prevHp_ = -1;       // 直前のHP（変化検出用）
	flashInterval_ = 20;
	frameCounter_ = 0;
	hitTimer_ = 0;

	pattaern_ = E_NON;
	attackState_ = NON;
	attackCounter_ = 0;
	targetIndex_ = 2;
	encount_ = false;
	isHit_ = false;
	unit_.isGravity_ = true;

	slash_ = new Slash();
	bullet_ = new Bullet();
	blast_ = new Blast();
	tackle_ = new Tackle();

	DrawPat_ = NORMAL;
}

void BossTutorial::Update()
{
	if (attackState_ != BossTutorial::TACKLE) unit_.isGravity_ = true;

	if (EnCount())encount_ = true;

	if (encount_) {
		PattaernManager();
	}

	if (CheckHitKey(KEY_INPUT_0)) {
		SetDamage(1);
	}

	if (unit_.hp_ < 0)
	{
		unit_.hp_--;
	}

	frameCounter_ += 2;

	EnemyBase::Update();
}

void BossTutorial::Draw()
{

	if (hitTimer_ > 0)
	{
		hitTimer_--;
		frameCounter_++;
	}
	else
	{
		frameCounter_ = 0;
	}

	if (encount_) {
		DrawHP();
	}

	if (unit_.isDraw_)
	{
		bullet_->Draw();
		blast_->Draw();

		BossDraw();

		if (attackState_ == BossTutorial::SLASH)
		{

			DrawBar(
				unit_.pos_.x - unit_.size_.x / 2,
				unit_.pos_.y - unit_.size_.y / 2,
				unit_.pos_.x + unit_.size_.x / 2,
				unit_.pos_.y - unit_.size_.y / 2 + 15,
				attackCounter_, Slash::CHARGE,
				RGB(255, 0, 0, ));
		}
		slash_->Draw();
	}

	DrawFormatString(120, 120, 0x0fffff, "boss(%.2f,%.2f)", unit_.nextpos_.x, unit_.nextpos_.y);
}

void BossTutorial::BossDraw()
{

	bool shouldFlash = false;

	if (hitTimer_ > 0)
	{
		if ((frameCounter_ / (flashInterval_ / 2)) % 2 == 0)
		{
			shouldFlash = true;
			SetDrawBright(255, 128, 128);                   // 明るく赤っぽく
			SetDrawBlendMode(DX_BLENDMODE_ADD, 180);        // 加算ブレンド
		}
	}

	switch (DrawPat_)
	{
	case NORMAL:
		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, 1.0f, 0.0f, img_[DrawPat_], true, bossDir_);
		break;
	case E_SLASH_START:
		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, 1.0f, 0.0f, img_[DrawPat_], true, bossDir_);
		break;
	case E_SLASH_END:
		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y + 14, 1.0f, 0.0f, img_[DrawPat_], true, bossDir_);
		break;
	}

	if (shouldFlash)
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBright(255, 255, 255);
	}
}

void BossTutorial::Release()
{
	tackle_->Release();
	delete tackle_;
	tackle_ = nullptr;

	blast_->Release();
	delete blast_;
	blast_ = nullptr;

	bullet_->Release();
	delete bullet_;
	bullet_ = nullptr;

	slash_->Release();
	delete slash_;
	slash_ = nullptr;

	//画像の開放
	for (int ii = 0; ii < DRAWPAT::DRAW_MAX; ii++) DeleteGraph(img_[ii]);
}

void BossTutorial::PattaernManager(void)
{
	switch (pattaern_)
	{
	case BossTutorial::E_NON:
		attackCounter_++;
		if (attackCounter_ > 100) {
			attackCounter_ = 0;
			pattaern_ = E_IDLE;
		}
		break;

	case BossTutorial::E_IDLE:
		Idle();
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

void BossTutorial::Idle(void)
{
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

		TargetLook(point);
	}

	attackCounter_++;

	unit_.nextpos_.x += GetMoveVec(unit_.nextpos_, point, unit_.speed_).x;

	if (GetDis(unit_.nextpos_, point) <= unit_.speed_) {
		attackCounter_ = 0;
		if (!(targetIndex_ == 1)) {
			TargetLook(player_->GetUnit().pos_);
			attackState_ = BossTutorial::TACKLE;//(ATTACK)GetRand((int)ATTACK::MAX-2);
			pattaern_ = E_ATTACK;
		}
		else {
			pattaern_ = E_NON;
		}
	}

	
}

void BossTutorial::Attack()
{
	attackCounter_++;

	switch (attackState_)
	{
	case BossTutorial::SLASH:

		if (attackCounter_ == 1) {
			panVec_ = { 0.0f,0.0f };
			slash_->Init(&unit_.pos_);
			DrawPat_ = E_SLASH_START;
		}

		if (attackCounter_ < Slash::CHARGE) TargetLook(player_->GetUnit().pos_);


		if (attackCounter_ == Slash::CHARGE) {
			target_ = player_->GetUnit().pos_;

			Slash::DIR dir;

			if (target_.x <= unit_.pos_.x)	dir = Slash::DIR::LEFT;
			else							dir = Slash::DIR::RIGHT;

			slash_->SetTarget(dir);
		
			panVec_ = GetMoveVec(unit_.pos_, target_, unit_.speed_ * 3.0f);
		}

		if (!(panVec_.x == 0.0f && panVec_.y == 0.0f)) {

			unit_.isGravity_ = false;

			float dis = target_.x - unit_.nextpos_.x;
			if (dis < 0)dis *= -1;
			if (dis <= player_->GetUnit().size_.x + unit_.size_.x) {
				panVec_ = { 0.0f,0.0f };
				slash_->On();
				DrawPat_ = E_SLASH_END;
			}
		}

		unit_.nextpos_ += panVec_;

		if (slash_->End()) {
			attackCounter_ = 0;
			unit_.isGravity_ = true;
			pattaern_ = E_IDLE;
			attackState_ = NON;
		}

		slash_->Update();

		break;
	case BossTutorial::BULLET:

		if (attackCounter_ == 1) {
			bullet_->Init(&unit_.pos_);
		}

		if (bullet_->End()) {
			attackCounter_ = 0;
			pattaern_ = E_IDLE;
			attackState_ = NON;
		}

		bullet_->Update();
		break;
	case BossTutorial::ROAR:
		pattaern_ = E_IDLE;
		attackState_ = NON;
		break;
	case BossTutorial::BLAST:

		if (attackCounter_ == 1) {
			blast_->Init(&unit_.pos_);
		}
		if (attackCounter_ == 60) {
			blast_->LookOn(player_->GetUnit().pos_);
		}

		if (blast_->End()) {
			attackCounter_ = 0;
			pattaern_ = E_IDLE;
			attackState_ = NON;
		}

		blast_->Update();
		break;
	case BossTutorial::TACKLE:

		Vector2 start;
		start.x = (Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2;
		start.y = (Application::MAIN_SCREEN_SIZE_Y - Application::SCREEN_SIZE_Y) / 2;

		if (attackCounter_ == 1) {
			tackle_->Init(&unit_.pos_);
		}

		unit_.isGravity_ = false;
		unit_.isStageCollision_ = false;

		tackle_->Update();
		tDir_ = tackle_->GetDir();

		switch (tDir_)
		{
		case Tackle::DIR::STANDBY:

			if (unit_.nextpos_.y > start.y)
			{
				unit_.nextpos_.y -= 10;
			}
			else
			{
				unit_.nextpos_.x = Application::SCREEN_SIZE_X;
				unit_.nextpos_.y = player_->GetUnit().nextpos_.y;
			}

			break;
		case Tackle::DIR::TACKLE_MODE:

			unit_.nextpos_.x -= 20;

			break;
		case Tackle::DIR::END:
			break;
		}

		tackle_->SetTarget(player_->GetUnit().pos_);
	}

	if (CheckHitKey(KEY_INPUT_U) == 1) {
		pattaern_ = E_NON;
	}

	if (attackCounter_ > 1000 || attackState_ == NON) {
		attackCounter_ = 0;
		pattaern_ = E_IDLE;
		attackState_ = NON;
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


const std::vector<Base> BossTutorial::GetAttackObj() const
{
	std::vector<Base>ret;

	switch (attackState_)
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
		ret = blast_->Get();
		break;
	case BossTutorial::TACKLE:
		break;
	}

	return ret;
}

void BossTutorial::TargetLook(Vector2F target)
{
	if (target.x <= unit_.pos_.x)	bossDir_ = AttackBase::DIR::LEFT;
	else							bossDir_ = AttackBase::DIR::RIGHT;
}

void BossTutorial::DrawHP()
{
	//ボスが死んだらHPバーが揺れ続ける（ただの演出）
	if (unit_.hp_ > -100) {
		if (unit_.hp_ < 0)unit_.hp_--;
	}

	//HPの変化を検出（減少時のみ揺らす）
	if (unit_.hp_ < prevHp_) {
		hpShakeTimer_ = 10;
	}

	prevHp_ = unit_.hp_;

	if (dispHp_ < unit_.hp_) dispHp_ += 1;			//ボスがエンカウントしたら増える！！！！
	if (dispHp_ > unit_.hp_) dispHp_ -= 3;			//HPをゆっくり減らすよ

	Vector2 start;
	start.x = (Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2;
	start.y = (Application::MAIN_SCREEN_SIZE_Y - Application::SCREEN_SIZE_Y) / 2;

	//鮭鮭
	int shakeX = 0;
	int shakeY = 0;
	if (hpShakeTimer_ > 0) {
		hpShakeTimer_--;
		shakeX = GetRand(6) - 3;
		shakeY = GetRand(4) - 2;
	}

	bool isCritical = (unit_.hp_ < BOSS_HP * HP_YABAI);
	bool blinkOn = (frameCounter_ % BLINK_FLAME) < (BLINK_FLAME / 2);

	for (int i = 0; i < unit_.hp_; ++i) {
		if (isCritical && !blinkOn) {
			continue;
		}
	}

	DrawBar(
		start.x + Application::SCREEN_SIZE_X / 4 + shakeX,
		start.y + Application::SCREEN_SIZE_Y - 50 + shakeY,
		start.x + Application::SCREEN_SIZE_X / 4 * 3 + shakeX,
		start.y + Application::SCREEN_SIZE_Y - 20 + shakeY,
		dispHp_, BOSS_HP, RGB(100, 100, 255)
	);
}

void BossTutorial::BossDeath()
{
	if (unit_.isAlive_)
	{

	}
}

void BossTutorial::SetDamage(int damage)
{
	if (unit_.hp_ <= 0) return;

	unit_.hp_ -= damage;
	hitTimer_ = 10;

	if (unit_.hp_ <= 0) {
		unit_.isAlive_ = false;
	}
}