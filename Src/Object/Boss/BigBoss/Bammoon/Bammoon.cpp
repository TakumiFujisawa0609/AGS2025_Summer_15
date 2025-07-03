#include"Bammoon.h"

#include<DxLib.h>
#include<string>

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


	unit_.size_ = { SIZE_X,SIZE_Y };
	unit_.radius_ = unit_.size_.x/2;
	unit_.speed_ = 10.0f;


	unit_.isAlive_ = true;
	unit_.nextpos_ = { 1000.0f,400.0f };
	unit_.pos_ = unit_.nextpos_;
	unit_.hp_ = 100;

	idleTime_ = 300;

	animeCounter_ = 0;
	animeInterval_ = 0;

	counter_ = 0;
}

void Bammoon::Update(void)
{
	if (unit_.hp_ <= 0) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}
	Animation();
	BossBase::Update();
}

void Bammoon::Draw(void)
{
	if (unit_.isAlive_) {
		DrawBammoonImage();
	}
}

void Bammoon::Release(void)
{
	for (int i = 0; i < (int)MOTION::MAX; i++) {
		for (auto id : image_[i]) {
			DeleteGraph(id);
		}
		image_[i].clear();
	}
}

std::vector<Base> Bammoon::GetObj(void)
{
	return std::vector<Base>();
}

AttackBase* Bammoon::GetAttackIns(void)
{
	return nullptr;
}

void Bammoon::SetDamage(int dmg)
{
	if (unit_.hp_ <= 0) return;

	unit_.hp_ -= dmg;
	unit_.inviCounter_ = 10;

	if (unit_.hp_ <= 0) {
		unit_.isAlive_ = false;
	}
}

void Bammoon::ObjHit(int i)
{
}


//std::vector<Base*> Bammoon::GetObj(void)
//{
//	return std::vector<Base*>();
//}

void Bammoon::Idle(void)
{
	if (--idleTime_ <= 0) {
		counter_ = 0;
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
	case Bammoon::ATTACK::BLAST:

		break;
	}
	counter_++;
}

void Bammoon::Damage(void)
{
}

void Bammoon::Death(void)
{
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
	DrawRotaGraphF(unit_.disppos_.x, unit_.disppos_.y, SCALE, 0, image_[(int)motion_][animeCounter_], true,true);
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