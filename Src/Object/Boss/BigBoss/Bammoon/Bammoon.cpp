#include"Bammoon.h"

#include<DxLib.h>
#include<string>

#include"Attack/BamBlast.h"
#include"Attack/Pbullet.h"
#include"Attack/Stripe.h"

Bammoon::Bammoon()
{
}

Bammoon::~Bammoon()
{
}

void Bammoon::Init(void)
{
	ChangeState(STATE::IDLE);
	LoadBammoonImage();
	ChangeMotion(MOTION::IDLE);

	attackState_ = ATTACK::NON;

	blast_ = new BamBlast();
	blast_->Init(&unit_.pos_);

	pBullet_ = new Pbullet();
	pBullet_->Init(&unit_.pos_);

	stripe_ = new Stripe();
	stripe_->Init(&unit_.pos_);

	unit_.size_ = { SIZE_X,SIZE_Y };
	unit_.radius_ = unit_.size_.x/2;
	unit_.speed_ = 10.0f;


	unit_.isAlive_ = true;
	unit_.nextpos_ = { 1000.0f,400.0f };
	unit_.pos_ = unit_.nextpos_;
	unit_.hp_ = HP_MAX;

	idleTime_ = 300;

	animeCounter_ = 0;
	animeInterval_ = 0;

	counter_ = 0;

	TargetLook(*playerPosPtr_);
}

void Bammoon::Update(void)
{
	Animation();
	AttackUpdate();
	BossBase::Update();
}

void Bammoon::Draw(void)
{
	if (unit_.isAlive_) {
		DrawBammoonImage();
		AttackDraw();
	}
	Vector2 start, end, size;
	size = { 800,50 };
	end = { Application::SCREEN_SIZE_X - 5,Application::SCREEN_SIZE_Y - 20 };
	start = end - size;
	DrawBar(start.x, start.y, end.x, end.y, unit_.hp_, HP_MAX, RGB(0, 255, 255));
}

void Bammoon::Release(void)
{
	stripe_->Release();
	delete stripe_;
	stripe_ = nullptr;

	pBullet_->Release();
	delete pBullet_;
	pBullet_ = nullptr;

	blast_->Release();
	delete blast_;
	blast_ = nullptr;

	for (int i = 0; i < (int)MOTION::MAX; i++) {
		for (auto id : image_[i]) {
			DeleteGraph(id);
		}
		image_[i].clear();
	}
}



void Bammoon::Idle(void)
{
	TargetLook(*playerPosPtr_);
	if (--idleTime_ <= 0) {
		counter_ = 0;
		attackState_ = ATTACK::NON;
		ChangeState(STATE::MOVE);
	}
}

void Bammoon::Move(void)
{
	static bool jumpmotion = false;
	static bool jump = false;
	static int stopCou = 100;
	if (counter_ == 0) {
		jumpmotion = false;
		jump = false;
		stopCou = 100;
	}

	TargetLook(*playerPosPtr_);

	if (!jumpmotion) { ChangeMotion(MOTION::JUMP, false); jumpmotion = true; }

	if (motion_ != MOTION::JUMP && jumpmotion && !jump) {
		jump = true;
		unit_.yAccel_ = -50.0f;
	}


	if (jump && unit_.yAccel_ > 0.0f && unit_.isGravity_) {
		unit_.isGravity_ = false;
		unit_.yAccel_ = 0.0f;
	}

	if (jump && !unit_.isGravity_) {
		if (--stopCou <= 0) {
			AttackRand();
			ChangeState(STATE::ATTACK);
			counter_ = 0;
			//static 宣言をリセット--
			jumpmotion = false;
			jump = false;
			stopCou = 100;
			//-----------------------
			return;
		}
	}
	counter_++;
}

void Bammoon::Attack(void)
{
	static bool mot = false;
	static Vector2F vec;
	if (counter_ == 0) {
		mot = false;
		vec = {};
	}

	switch (attackState_)
	{
	case Bammoon::ATTACK::SWEEP:
		if (counter_ == 0) {
			Vector2F v = *playerPosPtr_ - unit_.pos_;
			float size = sqrtf(v.x * v.x + v.y * v.y);
			vec = (v / size) * 30.0f;
		}

		if (counter_ == 100) {
			unit_.xAccel_ = vec.x;
			unit_.yAccel_ = vec.y;
			unit_.isGravity_ = true;
			unit_.isXAttenu = false;
		}


		if (unit_.isGround_) {
			ChangeMotion(MOTION::ATTACK, false);

			unit_.isGravity_ = true;
			unit_.isXAttenu = true;

			counter_ = 0;

			idleTime_ = 400;
			ChangeState(STATE::IDLE);
			return;
		}
		break;
	case Bammoon::ATTACK::BLAST: {
		int rate = 15;	//何フレームに一回打つか
		if (counter_ % rate == 0) blast_->On(counter_ / rate, *playerPosPtr_);
		if (blast_->End()) {
			counter_ = 0;
			unit_.isGravity_ = true;
			unit_.isXAttenu = true;
			idleTime_ = 300;
			ChangeState(STATE::IDLE);
			return;
		}
		break;
	}
	case Bammoon::ATTACK::PBULLET: {
		int rate = 5;	//何フレームに一回打つか
		if (counter_ % rate == 0) {
			pBullet_->On(counter_ / rate, *playerPosPtr_);
		}
		if (pBullet_->End()) {
			counter_ = 0;
			unit_.isGravity_ = true;
			unit_.isXAttenu = true;
			idleTime_ = 300;
			ChangeState(STATE::IDLE);
			return;
		}
		break;
	}
	case Bammoon::ATTACK::STRIPE: {
		int rate = 30;
		if (counter_ % rate == 0)stripe_->On(counter_ / rate);

		if (stripe_->End()) {
			counter_ = 0;
			unit_.isGravity_ = true;
			unit_.isXAttenu = true;
			idleTime_ = 300;
			ChangeState(STATE::IDLE);
			return;
		}
	}
	}
	counter_++;
}

void Bammoon::Damage(void)
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
		idleTime_ = 400;
		ChangeState(STATE::IDLE);
		attackState_ = ATTACK::NON;
		ChangeMotion(MOTION::DAMAGE);
	}
}

void Bammoon::Death(void)
{
}

std::vector<Base> Bammoon::GetObj(void)
{
	switch (attackState_)
	{
	case Bammoon::ATTACK::NON:
		break;
	case Bammoon::ATTACK::SWEEP:
		break;
	case Bammoon::ATTACK::BLAST:
		return blast_->Get();
		break;
	case Bammoon::ATTACK::PBULLET:
		return pBullet_->Get();
		break;
	case Bammoon::ATTACK::STRIPE:
		return stripe_->Get();
		break;
	default:
		break;
	}
	return std::vector<Base>();
}

AttackBase* Bammoon::GetAttackIns(void)
{
	return nullptr;
}

void Bammoon::ObjHit(int i)
{
	switch (attackState_)
	{
	case Bammoon::ATTACK::NON:
		break;
	case Bammoon::ATTACK::SWEEP:
		break;
	case Bammoon::ATTACK::BLAST:
		blast_->Hit(i);
		break;
	case Bammoon::ATTACK::PBULLET:
		pBullet_->Hit(i);
		break;
	case Bammoon::ATTACK::STRIPE:
		break;
	case Bammoon::ATTACK::MAX:
		break;
	default:
		break;
	}
}

void Bammoon::SetDamage(int dmg)
{
	if (unit_.hp_ <= 0) return;

	unit_.hp_ -= dmg;
	unit_.inviCounter_ = 10;

	if (unit_.hp_ <= 0) {
		auto& mana = SceneManager::GetInstance();
		mana.HitStop(60);
		mana.ZoomPos(unit_.pos_);
		mana.ZoomScale(2.0f);
		ChangeState(STATE::DEATH);
	}
}

void Bammoon::AttackUpdate(void)
{
	switch (attackState_)
	{
	case Bammoon::ATTACK::NON:
		break;
	case Bammoon::ATTACK::SWEEP:
		break;
	case Bammoon::ATTACK::BLAST:
		blast_->Update();
		break;
	case Bammoon::ATTACK::PBULLET:
		pBullet_->Update();
		break;
	case Bammoon::ATTACK::STRIPE:
		stripe_->Update();
		break;
	case Bammoon::ATTACK::MAX:
		break;
	default:
		break;
	}
}

void Bammoon::AttackDraw(void)
{
	switch (attackState_)
	{
	case Bammoon::ATTACK::NON:
		break;
	case Bammoon::ATTACK::SWEEP:
		break;
	case Bammoon::ATTACK::BLAST:
		blast_->Draw();
		break;
	case Bammoon::ATTACK::PBULLET:
		pBullet_->Draw();
		break;
	case Bammoon::ATTACK::STRIPE:
		stripe_->Draw();
		break;
	case Bammoon::ATTACK::MAX:
		break;
	default:
		break;
	}
}

void Bammoon::AttackRand(void)
{
	int r = GetRand(1000);

	if (r <= 100) {
		attackState_ = ATTACK::SWEEP;
	}
	else if (r <= 400) {
		attackState_ = ATTACK::BLAST;
	}
	else if (r <= 700) {
		attackState_ = ATTACK::PBULLET;
	}
	else if (r <= 1000) {
		attackState_ = ATTACK::STRIPE;
	}
	attackState_ = ATTACK::STRIPE;
}


void Bammoon::SetDown(Vector2F pos)
{
	BossBase::SetDown(pos);
	TargetLook(*playerPosPtr_);
	if (state_ == STATE::ATTACK) {
		auto& mana = SceneManager::GetInstance();
		mana.HitStop(60);
		Vector2F point = unit_.pos_ + (pos - unit_.pos_);
		mana.ZoomPos(point);
		mana.ZoomScale(2.0f);

	}
}


void Bammoon::TargetLook(Vector2F target)
{
	if (target.x <= unit_.pos_.x)	bossDir_ = AttackBase::DIR::LEFT;
	else							bossDir_ = AttackBase::DIR::RIGHT;
}



void Bammoon::IsGround(Collision::DIR dir)
{
	switch (dir)
	{
	case Collision::UP:
		//天井に衝突していたら行う処理
		unit_.yAccel_ = 0.0f;
		break;
	case Collision::DOWN:
		//地面に接地していたら行う処理
		unit_.yAccel_ = 0.0f;
		if (unit_.isGround_ == false) {
			unit_.isGround_ = true;
			SceneManager::GetInstance().SHAKE();
		}
		break;
	case Collision::LEFT:
		//左側の壁に衝突していたら行う処理
		unit_.xAccel_ = 0.0f;
		break;
	case Collision::RIGHT:
		//右側の壁に衝突していたら行う処理
		unit_.xAccel_ = 0.0f;
		break;
	}
}













void Bammoon::LoadBammoonImage(void)
{
	const std::string PATH = "Data/Image/Boss/Bammoon/";

	int motion = 0;

	motion = (int)MOTION::IDLE;

	int idleLoad[IDLE_LOAD_NUM];

	LoadDivGraph((PATH + "Run/Run.png").c_str(), IDLE_LOAD_NUM, 2, 2, LOAD_SIZE_X, LOAD_SIZE_Y, idleLoad);

	image_[motion].insert(image_[motion].end(), idleLoad, idleLoad + IDLE_LOAD_NUM);

	motion = (int)MOTION::JUMP;

	int jumpLoad[IDLE_LOAD_NUM];

	LoadDivGraph((PATH + "Run/Run.png").c_str(), IDLE_LOAD_NUM, 2, 2, LOAD_SIZE_X, LOAD_SIZE_Y, jumpLoad);

	image_[motion].insert(image_[motion].end(), jumpLoad, jumpLoad + IDLE_LOAD_NUM);

	motion = (int)MOTION::ATTACK;

	for (int i = 1; i <= ATTACK_LOAD_NUM; i++) {
		std::string filePath = PATH + "Attack/Attack" + std::to_string(i) + ".png";
		int load = LoadGraph(filePath.c_str());
		image_[motion].emplace_back(load);
	}
}

void Bammoon::DrawBammoonImage(void)
{
	bool invic = false;
	if (!(unit_.inviCounter_ / 5 % 2 == 0))invic = true;

	if (invic)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

	DrawRotaGraphF(unit_.disppos_.x, unit_.disppos_.y, SCALE, 0,
		image_[(int)motion_][animeCounter_], true,
		(bossDir_ == AttackBase::DIR::LEFT) ? true : false);

	if (invic)SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Bammoon::Animation(void)
{
	animeInterval_++;
	if (!(animeInterval_ > ANIMATION_SPEED))return;
	else animeInterval_ = 0;

	animeCounter_++;
	if (animeCounter_ >= image_[(int)motion_].size()) {
		if (animeLoop_) {
			animeCounter_ = 0;
		}
		else {
			animeCounter_ = 0;
			ChangeMotion(MOTION::IDLE);
		}
	}
}

void Bammoon::ChangeMotion(MOTION m, bool loop)
{
	if (image_[(int)m].size() == 0)return;
	if (m == motion_)return;
	motion_ = m;
	animeCounter_ = 0;
	animeLoop_ = loop;
}