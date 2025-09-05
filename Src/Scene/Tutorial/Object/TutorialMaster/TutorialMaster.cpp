#include"TutorialMaster.h"

#include"../../../../Utility/AsoUtility.h"

TutorialMaster::TutorialMaster(const TutorialTaskManager::TASK& task, const bool& taskEnd):
	nowTask_(task),
	taskEnd_(taskEnd),
	image_(),
	pos_(),
	animeCounter_(0),
	animeInterval_(0),
	attack_(nullptr),
	attackIntarval_(0)
{
}

TutorialMaster::~TutorialMaster()
{
}

void TutorialMaster::Load(void)
{
	AsoUtility::LoadArrayImg("Data/Image/Tutorial/Master/Idle.png", IDLE_ANIME_NUM, IDLE_ANIME_NUM, 1, LOAD_SIZE, LOAD_SIZE, image_[(int)MOTION::IDLE]);
	AsoUtility::LoadArrayImg("Data/Image/Tutorial/Master/Attack.png", ATTACK_ANIME_NUM, ATTACK_ANIME_NUM, 1, LOAD_SIZE, LOAD_SIZE, image_[(int)MOTION::ATTACK]);

	attack_ = new TutorialMasterAttack(pos_);
	attack_->Load();
}

void TutorialMaster::Init(void)
{
	pos_ = { 1200.0f,545.0f };

	motion_ = MOTION::IDLE;

	animeCounter_ = 0;
	animeInterval_ = 0;

	attack_->Init();
	attackIntarval_ = ATTACK_INTERVAL;
}

void TutorialMaster::Update(void)
{
	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= image_[(int)motion_].size()) {
			animeCounter_ = 0;
			if (!animeLoop_) { motion_ = MOTION::IDLE; }
		}
	}

	if ((nowTask_ == TutorialTaskManager::TASK::TASK2 || nowTask_ == TutorialTaskManager::TASK::TASK5) &&
		(!taskEnd_)) { Attack(); }
	attack_->Update();
}

void TutorialMaster::Draw(void)
{
	DrawRotaGraph(1200, 545, SIZE_SCALE, 0, image_[(int)motion_].at(animeCounter_), true, true);
	attack_->Draw();
}

void TutorialMaster::Release(void)
{
	if (attack_) {
		attack_->Release();
		delete attack_;
		attack_ = nullptr;
	}
	for (auto& img : image_) { for (auto& id : img) { DeleteGraph(id); } }
}

void TutorialMaster::AttackMotion(void)
{
	if (motion_ == MOTION::ATTACK) { return; }

	motion_ = MOTION::ATTACK;
	animeLoop_ = false;
	animeCounter_ = animeInterval_ = 0;
}

void TutorialMaster::Attack(void)
{
	if (attackIntarval_ > 0) { attackIntarval_--; }
	else {
		AttackMotion();
		if (animeCounter_ == 5) {
			attack_->On();
			attackIntarval_ = ATTACK_INTERVAL;
		}
	}
}
