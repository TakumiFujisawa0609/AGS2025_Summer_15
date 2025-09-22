#include"TutorialTaskManager.h"

#include"../../../../Utility/AsoUtility.h"
#include"../../../../Manager/KeyManager.h"

#include"../../../../Manager/SoundManager.h"

#include"../../../../Manager/SceneManager.h"
#include"../../../Event/TitleJump/TitleJump.h"

TutorialTaskManager::TutorialTaskManager():
	nowTask_(TASK::START),
	taskIns_(),
	linesCount_(0),
	linesInterval_(0),
	hukidashiImg_(-1),
	nextButtonImg_{ -1, -1 },
	nextKeyImg_{ -1, -1 },
	nextButtonCounter_(0),
	taskConp_(true)
{
}

TutorialTaskManager::~TutorialTaskManager()
{
}

void TutorialTaskManager::Load(void)
{
	for (auto& ins : taskIns_) { ins = nullptr; }

	taskIns_[(int)TASK::TASK1] = new Task1();
	taskIns_[(int)TASK::TASK2] = new TaskBase();
	taskIns_[(int)TASK::TASK3] = new Task3();
	taskIns_[(int)TASK::TASK4] = new Task4();
	taskIns_[(int)TASK::TASK5] = new TaskBase();

	AsoUtility::LoadImg(hukidashiImg_, "Data/Image/Tutorial/Task/‚«o‚µ.png");
	AsoUtility::LoadImg(nextButtonImg_[0], "Data/Image/Tutorial/Task/Button/UnPushButton.png");
	AsoUtility::LoadImg(nextButtonImg_[1], "Data/Image/Tutorial/Task/Button/PushButton.png");
	AsoUtility::LoadImg(nextKeyImg_[0], "Data/Image/Tutorial/Task/Button/UnPush.png");
	AsoUtility::LoadImg(nextKeyImg_[1], "Data/Image/Tutorial/Task/Button/Push.png");

	for (auto& ins : taskIns_) {
		if (!ins) { continue; }
		ins->Load();
	}
}

void TutorialTaskManager::Init(void)
{
	for (auto& ins : taskIns_) {
		if (!ins) { continue; }
		ins->Init();
	}

	linesCount_ = 0;
	linesInterval_ = 0;
	taskConp_ = true;

	nowTask_ = TASK::START;

	nextButtonCounter_ = 0;
}

bool TutorialTaskManager::Update(void)
{
	if (taskIns_[(int)nowTask_]) {

		taskIns_[(int)nowTask_]->Update();

		if (taskIns_[(int)nowTask_]->End()) {
			if (taskConp_ == false) {
				linesInterval_ = 0;
				linesCount_ = 0;
				taskConp_ = true;
			}

			if (linesCount_ >= (int)END_LINES_TABLE[(int)nowTask_].size()) {
				if (KeyManager::GetIns().GetInfo(KEY_TYPE::TUTORIAL_NEXT).down) { if (NextTask()) { return true; } }
			}
		}

	}
	else {
		if (taskConp_ == false) {
			linesInterval_ = 0;
			linesCount_ = 0;
			taskConp_ = true;
		}

		if (linesCount_ >= (int)END_LINES_TABLE[(int)nowTask_].size()) {
			if (KeyManager::GetIns().GetInfo(KEY_TYPE::TUTORIAL_NEXT).down) { if (NextTask()) { return true; } }
		}
	}

	if (taskConp_) {
		if (linesCount_ >= (int)(END_LINES_TABLE[(int)nowTask_].size())) {
			nextButtonCounter_++;
			return false;
		}

		if (++linesInterval_ >= LINES_INTERVAL) {
			linesInterval_ = 0;
			if (++linesCount_ >= (int)END_LINES_TABLE[(int)nowTask_].size()) {
				linesCount_ = (int)(END_LINES_TABLE[(int)nowTask_].size());
				Smng::GetIns().Stop(SOUND::SE_SYSTEM_CHARA);
			}
			else { Smng::GetIns().Play(SOUND::SE_SYSTEM_CHARA, false); }
		}

	}
	else {
		int linesSize =
			(KEY::GetIns().IsControllerConnected()) ?
			(int)(START_LINES_TABLE_CONTROLER[(int)nowTask_].size()) :
			(int)(START_LINES_TABLE_KEYBOARD[(int)nowTask_].size());

		if (linesCount_ >= linesSize) { return false; }

		if (++linesInterval_ >= LINES_INTERVAL) {
			linesInterval_ = 0;
			if (++linesCount_ >= linesSize) {
				linesCount_ = linesSize;
				Smng::GetIns().Stop(SOUND::SE_SYSTEM_CHARA);
			}
			else { Smng::GetIns().Play(SOUND::SE_SYSTEM_CHARA, false); }
		}
	}

	return false;
}

void TutorialTaskManager::Draw(void)
{
	if (taskIns_[(int)nowTask_]) { taskIns_[(int)nowTask_]->Draw(); }
}

void TutorialTaskManager::DrawUI(void)
{
	DrawRotaGraph3(1280, 768, 900, 153, 1, 1, 0, hukidashiImg_, true);

	std::wstring work = {};

	if (taskConp_) {
		work = END_LINES_TABLE[(int)nowTask_].substr(0, linesCount_);
	}
	else {
		work = (KEY::GetIns().IsControllerConnected()) ?
			START_LINES_TABLE_CONTROLER[(int)nowTask_].substr(0, linesCount_) :
			START_LINES_TABLE_KEYBOARD[(int)nowTask_].substr(0, linesCount_);
	}

	SetFontSize(23);
	AsoUtility::DrawString_W(460, 658, work.c_str(), 0x000000);
	SetFontSize(16);

	if (linesCount_ >= (int)END_LINES_TABLE[(int)nowTask_].size() && taskConp_) {
		DrawRotaGraph(Application::SCREEN_SIZE_X - 150, Application::SCREEN_SIZE_Y - 35, 0.15, 0, (KEY::GetIns().IsControllerConnected()) ? nextButtonImg_[nextButtonCounter_ / 10 % 2] : nextKeyImg_[nextButtonCounter_ / 10 % 2], true);
	}
}

void TutorialTaskManager::Release(void)
{
	DeleteGraph(hukidashiImg_);
	for (auto& id : nextButtonImg_) { DeleteGraph(id); }
	for (auto& id : nextKeyImg_) { DeleteGraph(id); }

	for (auto& ins : taskIns_) {
		if (!ins) { continue; }
		ins->Release();
		delete ins;
		ins = nullptr;
	}
}

bool TutorialTaskManager::NextTask(void)
{
	Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true);

	nowTask_ = (TASK)((int)nowTask_ + 1);

	if ((int)nowTask_ >= (int)TASK::MAX) {
		nowTask_ = (TASK)((int)nowTask_ - 1);
		SceneManager::GetIns().PushScene(std::make_shared<TitleJump>());
		return true;
	}

	linesInterval_ = 0;
	linesCount_ = 0;
	taskConp_ = false;
	nextButtonCounter_ = 0;

	return false;
}

