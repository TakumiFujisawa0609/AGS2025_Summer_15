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
	unit_.hp_ = 1000;

	idleTime_ = 300;

	animeCounter_ = 0;
	animeInterval_ = 0;
}

void Bammoon::Update(void)
{
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


std::vector<Base*> Bammoon::GetObj(void)
{
	return std::vector<Base*>();
}

void Bammoon::Idle(void)
{
	if (--idleTime_ <= 0) {
		ChangeState(STATE::MOVE);
	}
}

void Bammoon::Move(void)
{
	static bool jumpmotion = false;
	static bool jump = false;
	static bool move = false;
	static int stopCou = 100;
	static Vector2F vec = {};

	if (!jumpmotion) { ChangeMotion(MOTION::JUMP, false); jumpmotion = true; }

	if (motion_ != MOTION::JUMP && jumpmotion && !jump) {
		jump = true;
		unit_.yAccel_ = -50.0f;
	}


	if (jump && unit_.yAccel_ > 0.0f && unit_.isGravity_) {
		unit_.isGravity_ = false;
		unit_.yAccel_ = 0.0f;
		vec = { 0.0f,50.0f };
		return;
	}

	if (jump && !unit_.isGravity_) {
		if (--stopCou <= 0 && !move) {
			unit_.xAccel_ = vec.x;
			unit_.yAccel_ = vec.y;
			move = true;
		}

		if (unit_.isGround_) {
			//static éŒ¾‚ðƒŠƒZƒbƒg--
			jumpmotion = false;
			jump = false;
			vec = {};
			move = false;
			stopCou = 100;
			//-----------------------
			unit_.isGravity_ = true;
			idleTime_ = 300;
			ChangeState(STATE::IDLE);
		}

	}

}

void Bammoon::Attack(void)
{
}

void Bammoon::Damage(void)
{
}

void Bammoon::Death(void)
{
}











void Bammoon::IsGround(Collision::DIR dir)
{
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
}

void Bammoon::DrawBammoonImage(void)
{
	DrawRotaGraphF(unit_.disppos_.x, unit_.disppos_.y, SCALE, 0, image_[(int)motion_][animeCounter_], true);
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
			ChangeMotion(MOTION::IDLE);
			ChangeState(STATE::IDLE);
		}
	}
}

void Bammoon::ChangeMotion(MOTION m, bool loop)
{
	if (m == motion_)return;

	motion_ = m;
	animeCounter_ = 0;
	animeLoop_ = loop;
}