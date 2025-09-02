#include"TutorialTaskManager.h"

#include"../../../../Utility/AsoUtility.h"


TutorialTaskManager::TutorialTaskManager():
	nowTask_(TASK::START),
	taskIns_(),
	linesCount_(0),
	linesInterval_(0)
{
}

TutorialTaskManager::~TutorialTaskManager()
{
}

void TutorialTaskManager::Load(void)
{
	for (auto& ins : taskIns_) { ins = nullptr; }

	taskIns_[(int)TASK::TASK1] = new Task1();
	taskIns_[(int)TASK::TASK3] = new Task3();
	taskIns_[(int)TASK::TASK4] = new Task4();

	AsoUtility::LoadImg(hukidashiImg_, "Data/Image/Tutorial/Task/‚«o‚µ.png");

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
}

void TutorialTaskManager::Update(void)
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
				if (CheckHitKey(KEY_INPUT_SPACE)) { NextTask(); }
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
			if (CheckHitKey(KEY_INPUT_SPACE)) { NextTask(); }
		}
	}

	if (taskConp_) {
		if (linesCount_ >= (int)(END_LINES_TABLE[(int)nowTask_].size())) { return; }

		if (++linesInterval_ >= LINES_INTERVAL) {
			linesInterval_ = 0;
			if (++linesCount_ >= (int)END_LINES_TABLE[(int)nowTask_].size()) { linesCount_ = (int)(END_LINES_TABLE[(int)nowTask_].size()); }
		}

	}
	else {
		if (linesCount_ >= (int)(START_LINES_TABLE[(int)nowTask_].size())) { return; }

		if (++linesInterval_ >= LINES_INTERVAL) {
			linesInterval_ = 0;
			if (++linesCount_ >= (int)START_LINES_TABLE[(int)nowTask_].size()) { linesCount_ = (int)(START_LINES_TABLE[(int)nowTask_].size()); }
		}
	}

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
		work = START_LINES_TABLE[(int)nowTask_].substr(0, linesCount_);
	}

	SetFontSize(23);
	AsoUtility::DrawString_W(460, 658, work.c_str(), 0x000000);
	SetFontSize(16);

	
}

void TutorialTaskManager::Release(void)
{
	for (auto& ins : taskIns_) {
		if (!ins) { continue; }
		ins->Release();
		delete ins;
		ins = nullptr;
	}
}

void TutorialTaskManager::NextTask(void)
{
	linesInterval_ = 0;
	linesCount_ = 0;
	taskConp_ = false;
	nowTask_ = (TASK)((int)nowTask_ + 1);

	if ((int)nowTask_ >= (int)TASK::MAX) { nowTask_ = (TASK)((int)nowTask_ - 1); }
}

