#include"BossTutorial.h"

#include<DxLib.h>

#include"../../../Manager/SceneManager.h"
#include"../../../Manager/Camera.h"
#include"../../../Manager/SoundManager.h"

#include"../../Player/Player.h"

BossTutorial::BossTutorial()
{
}

BossTutorial::~BossTutorial()
{
}

void BossTutorial::Init()
{
	this->Release();

	img_[DRAWPAT::NORMAL] = LoadGraph("Data/Image/Boss/TutrialBoss.png");
	img_[DRAWPAT::E_SLASH_START] = LoadGraph("Data/Image/Boss/BossSlash.png");
	img_[DRAWPAT::E_SLASH_END] = LoadGraph("Data/Image/Boss/BossSlashEnd.png");
	img_[DRAWPAT::E_DAMAGE] = LoadGraph("Data/Image/Boss/BossDamage.png");

	unit_.isAlive_ = true;
	unit_.isDraw_ = true;
	unit_.pos_ = { 1000,250 };
	unit_.nextpos_ = unit_.pos_;
	unit_.size_ = { SIZE_X, SIZE_Y };
	unit_.radius_ = unit_.size_.x / 2;
	unit_.speed_ = 10.0f;
	unit_.hp_ = BOSS_HP;
	dispHp_ = 0.0f;
	hpShakeTimer_ = 0;  // 揺れ時間（フレーム数）
	prevHp_ = -1;       // 直前のHP（変化検出用）
	flashInterval_ = 20;
	frameCounter_ = 0;
	hitTimer_ = 0;
	diedCounter = 0;
	slashCnt_ = Slash::CHARGE;

	state_ = E_NON;
	attackState_ = NON;
	attackCounter_ = 0;
	targetIndex_ = 2;
	encount_ = false;
	isHit_ = false;
	unit_.isGravity_ = true;

	endFlg = false;

	slash_ = new Slash();
	bullet_ = new Bullet();
	blast_ = new Blast();
	tackle_ = new Tackle();

	DrawPat_ = NORMAL;


	//攻撃パターン{ Key, value }
	attackUpdateFuncs_ = {
		{ SLASH,	&BossTutorial::SlashUpdate },
		{ BULLET,	&BossTutorial::BulletUpdate },
		{ ROAR,		&BossTutorial::RoarUpdate },
		{ BLAST,	&BossTutorial::BlastUpdate },
		{ TACKLE,	&BossTutorial::TackleUpdate }
	};

	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Load(S::SOUND::TUTORIALDAMAGE);
	sound.Load(S::SOUND::TUTORIALJUMP);
	sound.Load(S::SOUND::TUTORIALLANDING);
}

void BossTutorial::Update()
{
	if (unit_.inviCounter_ > 0)unit_.inviCounter_--;

	if (attackState_ != BossTutorial::TACKLE) unit_.isGravity_ = true;

	if (EnCount())encount_ = true;
	if (encount_) {
		PattaernManager();
	}


	if (hitTimer_ > 0)
	{
		hitTimer_--;
		frameCounter_++;
	}
	else
	{
		frameCounter_ = 0;
	}

	if (CheckHitKey(KEY_INPUT_0)) {
		SetDamage(20);
	}
	if (CheckHitKey(KEY_INPUT_1))unit_.isAlive_ = false;

	HpUpdate();

	frameCounter_ += 2;

	UnitBase::Update();

	if (!unit_.isAlive_)state_ = STATE::E_DEATH;
}

void BossTutorial::Draw()
{

	if (unit_.isDraw_)
	{
		bullet_->Draw();
		blast_->Draw();

		BossDraw();

		slash_->Draw();
	}
}

void BossTutorial::BossDraw()
{

	bool isFlash = false;

	if (hitTimer_ > 0)
	{
		if ((frameCounter_ / (flashInterval_ / 2)) % 2 == 0)
		{
			isFlash = true;
			SetDrawBright(255, 128, 128); 
			SetDrawBlendMode(DX_BLENDMODE_ADD, 180);        
		}
	}

	switch (DrawPat_)
	{
	case NORMAL:
	case E_DAMAGE:
		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, 1.0f, 0.0f, img_[DrawPat_], true, bossDir_);
		break;
	case E_SLASH_START:
		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y, 1.0f, 0.0f, img_[DrawPat_], true, bossDir_);

		DrawBar(
			unit_.disppos_.x - 100,
			unit_.disppos_.y - unit_.size_.y / 2,
			unit_.disppos_.x + 100,
			unit_.disppos_.y - (unit_.size_.y / 2 + 10),
			slashCnt_, Slash::CHARGE,
			RGB(255, 0, 255),
			RGB(0, 0, 0));


		break;
	case E_SLASH_END:
		DrawRotaGraph(unit_.disppos_.x, unit_.disppos_.y + 14, 1.0f, 0.0f, img_[DrawPat_], true, bossDir_);
		break;
	}

	if (isFlash)
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBright(255, 255, 255);
	}
}

void BossTutorial::Release()
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(S::SOUND::TUTORIALLANDING);
	sound.Delete(S::SOUND::TUTORIALJUMP);
	sound.Delete(S::SOUND::TUTORIALDAMAGE);

	if (tackle_) {
		tackle_->Release();
		delete tackle_;
		tackle_ = nullptr;
	}

	if (blast_) {
		blast_->Release();
		delete blast_;
		blast_ = nullptr;
	}

	if (bullet_) {
		bullet_->Release();
		delete bullet_;
		bullet_ = nullptr;
	}

	if (slash_) {
		slash_->Release();
		delete slash_;
		slash_ = nullptr;
	}

	//画像の開放
	for (int ii = 0; ii < DRAWPAT::DRAW_MAX; ii++) DeleteGraph(img_[ii]);
}

void BossTutorial::PattaernManager(void)
{
	switch (state_)
	{
	case BossTutorial::E_NON:
		attackCounter_++;
		if (attackCounter_ > 100) {
			attackCounter_ = 0;
			state_ = E_IDLE;
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
	case BossTutorial::E_DOWN:
		Down();
		break;
	case BossTutorial::E_DEATH:
		Death();
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
	state_ = E_MOVE;
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

		SoundManager::GetIns().Play(SoundManager::SOUND::TUTORIALJUMP, true, 200);

		TargetLook(point);
	}

	attackCounter_++;

	unit_.nextpos_.x += GetMoveVec(unit_.nextpos_, point, unit_.speed_).x;

	if (GetDis(unit_.nextpos_, point) <= unit_.speed_) {
		attackCounter_ = 0;
		if (!(targetIndex_ == 1)) {
			TargetLook(player_->GetUnit().pos_);
			attackState_ = (ATTACK)GetRand((int)ATTACK::MAX - 2);
			state_ = E_ATTACK;
		}
		else {
			state_ = E_NON;
		}
	}

	
}

void BossTutorial::Attack()
{
	attackCounter_++;

	//アタックの状態遷移（関数ポインタ）
	auto it = attackUpdateFuncs_.find(attackState_);
	(this->*(it->second))();

	//デバック用（アタックの状態を攻撃をしてないときの状態にする）
	if (CheckHitKey(KEY_INPUT_U) == 1) {
		state_ = E_NON;
	}

	//バグが起きた時のための最終手段
	//（一定の時間を超えたら攻撃状態が強制的に終了する）
	if (attackCounter_ > 1000 || attackState_ == NON) {
		attackCounter_ = 0;
		state_ = E_IDLE;
		attackState_ = NON;
	}
}

void BossTutorial::Down()
{
	unit_.isGravity_ = true;

	if (bossDir_ == AttackBase::DIR::LEFT) {
		unit_.nextpos_.x += 10.0f;
	}
	else
	{
		unit_.nextpos_.x -= 10.0f;
	}


	if (unit_.isGround_ && unit_.yAccel_ >= 0) {
		state_ = STATE::E_NON;
		DrawPat_ = DRAWPAT::NORMAL;
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
			SceneManager::GetIns().Shake();
			SoundManager::GetIns().Play(SoundManager::SOUND::TUTORIALLANDING,true,200);
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

void BossTutorial::HpUpdate()
{
	if (encount_)
	{
		//ボスが死んだらHPバーが揺れ続ける（ただの演出用）
		if (unit_.hp_ <= 0) {
			hpShakeTimer_ = 10;
			unit_.hp_ = 0;
			unit_.isAlive_ = false;
		}

		//HPの変化を検出（減少時のみ揺らす）
		if (unit_.hp_ < prevHp_) {
			hpShakeTimer_ = 10;
		}

		prevHp_ = unit_.hp_;

		if (dispHp_ < unit_.hp_) dispHp_ += 3;			//ボスがエンカウントしたら増える！！！！
		if (dispHp_ > unit_.hp_) dispHp_ -= 3;			//HPをゆっくり減らすよ
	}



}

void BossTutorial::DrawHP()
{
	if (encount_) {

		//鮭鮭
		int shakeX = 0;
		int shakeY = 0;
		if (hpShakeTimer_ > 0) {
			hpShakeTimer_--;
			shakeX = GetRand(6) - 3;
			shakeY = GetRand(4) - 2;
		}

		Vector2 start, end, size;
		size = { 800,50 };
		end = { Application::SCREEN_SIZE_X - 5,Application::SCREEN_SIZE_Y - 20 };
		start = end - size;

		DrawBar(
			start.x + shakeX, start.y + shakeY,
			end.x + shakeX, end.y + shakeY,
			dispHp_, BOSS_HP, RGB(100, 100, 255)
		);
	}
}

void BossTutorial::SlashUpdate(void)
{
	static bool on = false;
	static int time = 0;

	if (attackCounter_ == 1) {
		panVec_ = { 0.0f,0.0f };
		slash_->Init(&unit_.pos_);
		DrawPat_ = E_SLASH_START;
		slashCnt_ = Slash::CHARGE;
		on = false;
		time = 0;
	}

	if (attackCounter_ < Slash::CHARGE)
	{
		slashCnt_--;
		TargetLook(player_->GetUnit().pos_);
	}

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

		float dis = target_.x - unit_.pos_.x;
		if (dis < 0)dis *= -1;
		if (dis <= (player_->GetUnit().radius_ + unit_.radius_)+30.0f) {
			panVec_ = { 0.0f,0.0f };
			on = true;
		}
	}
	
	if (on) time++;

	if (time > 5) { slash_->On(); DrawPat_ = E_SLASH_END; time = 0; }

	unit_.nextpos_ += panVec_;

	if (slash_->End()) {
		attackCounter_ = 0;
		unit_.isGravity_ = true;
		state_ = E_IDLE;
		attackState_ = NON;
	}

	slash_->SetBoss(unit_);
	slash_->SetTarget(player_->GetUnit());
	slash_->Update();
}

void BossTutorial::BulletUpdate(void)
{
	if (attackCounter_ == 1) {
		bullet_->Init(&unit_.pos_);
	}

	if (bullet_->End()) {
		attackCounter_ = 0;
		state_ = E_IDLE;
		attackState_ = NON;
	}

	bullet_->Update();
}

void BossTutorial::RoarUpdate(void)
{
	state_ = E_IDLE;
	attackState_ = NON;
}

void BossTutorial::BlastUpdate(void)
{

	if (attackCounter_ == 1) {
		blast_->Init(&unit_.pos_);
	}
	if (attackCounter_ == 60) {
		blast_->LookOn(player_->GetUnit().pos_);
	}

	if (blast_->End()) {
		attackCounter_ = 0;
		state_ = E_IDLE;
		attackState_ = NON;
	}

	blast_->Update();
}

void BossTutorial::TackleUpdate(void)
{
	Vector2F start = UnitBase::GetStartPos();


	if (attackCounter_ == 1) {
		tackle_->Init(&unit_.pos_);

		tackle_->SetEndPos(unit_.nextpos_);
	}

	tackle_->Update();
	tDir_ = tackle_->GetDir();

	switch (tDir_)
	{
	case Tackle::DIR::JUMP:

		//地団駄
		if (unit_.nextpos_.y > start.y)
		{
			unit_.isGravity_ = true;
			unit_.isStageCollision_ = true;
			unit_.nextpos_.y -= 10;
		}

		break;
	case Tackle::DIR::STANDBY:

		unit_.isGravity_ = false;


		//画面上に消える
		unit_.nextpos_.y -= 20;

		if (unit_.nextpos_.y < start.y - 100)
		{
			unit_.nextpos_.x = (start.x + Application::SCREEN_SIZE_X);
			unit_.nextpos_.y = player_->GetUnit().disppos_.y - unit_.radius_;
			tackle_->SetStandBy(true);
		}


		break;
	case Tackle::DIR::TACKLE_LEFT:

		unit_.isGravity_ = false;
		unit_.isStageCollision_ = false;

		//左に向かってタックル
		unit_.nextpos_.x -= Tackle::TACKLE_SPEED;

		break;
	case Tackle::DIR::TACKLE_RIGHT:

		unit_.isGravity_ = false;

		//右に向かってタックル
		unit_.nextpos_.x += Tackle::TACKLE_SPEED;

		if (unit_.nextpos_.x > start.x + Application::SCREEN_SIZE_X) {
			unit_.nextpos_.y = start.y - 100;
			unit_.nextpos_.x = tackle_->GetEndPos().x;

		}

		unit_.isGravity_ = true;
		unit_.isStageCollision_ = true;

		int cnt = tackle_->GetCounter();

		if (cnt > 120) {
			attackState_ = BossTutorial::ATTACK::NON;
		}
		break;
	}
}


void BossTutorial::ObjHit(int i)
{
	switch (attackState_)
	{
	case BossTutorial::NON:
		break;
	case BossTutorial::SLASH:
		break;
	case BossTutorial::BULLET:
		bullet_->Hit(i);
		break;
	case BossTutorial::ROAR:
		break;
	case BossTutorial::BLAST:
		blast_->Hit();
		break;
	case BossTutorial::TACKLE:
		break;
	case BossTutorial::MAX:
		break;
	default:
		break;
	}
}

AttackBase* BossTutorial::GetAttackIns(void)
{
	switch (attackState_)
	{
	case BossTutorial::NON:
		break;
	case BossTutorial::SLASH:
		return slash_;
	case BossTutorial::BULLET:
		return bullet_;
	case BossTutorial::ROAR:
		break;
	case BossTutorial::BLAST:
		return blast_;
	case BossTutorial::TACKLE:
		break;
	case BossTutorial::MAX:
		break;
	default:
		break;
	}
	return nullptr;
}


void BossTutorial::Death()
{
	auto& scene_ = SceneManager::GetIns();

	diedCounter++;
	/*unit_.isGravity_ = false;*/

	DrawPat_ = DRAWPAT::E_DAMAGE;

	//scene_.HitStop(60);

	if (diedCounter < 120)return;

	endFlg = true;

	//if (endFlg) scene_.ChangeScene(SceneManager::SCENE_ID::CLEAR);
}

void BossTutorial::DiedDraw()
{
}

void BossTutorial::SetDamage(int damage)
{
	if (unit_.hp_ <= 0) return;

	unit_.hp_ -= damage;
	hitTimer_ = 10;
	unit_.inviCounter_ = 5;

	if (unit_.hp_ <= 0) {
		unit_.isAlive_ = false;
	}

	SoundManager::GetIns().Play(SoundManager::SOUND::TUTORIALDAMAGE, true, 200);
}

void BossTutorial::SetDown(Vector2F pos)
{
	if (unit_.pos_.x < pos.x) {
		bossDir_ = AttackBase::DIR::RIGHT;
	}
	else {
		bossDir_ = AttackBase::DIR::LEFT;
	}
	unit_.yAccel_ = -10.0f;

	unit_.nextpos_.y += unit_.yAccel_;

	state_ = STATE::E_DOWN;
	attackState_ = ATTACK::NON;
	DrawPat_ = DRAWPAT::E_DAMAGE;
}
