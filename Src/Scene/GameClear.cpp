#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include"../Manager/Score/Score.h"
#include"../Manager/SoundManager.h"
#include "GameClear.h"

GameClear::GameClear(void):
	image_(-1),
	rankImg_(-1)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Load(void)
{
	image_ = LoadGraph("Data/Image/GameClear.png");

	auto score = Score::GetIns().GetNowScore();
	if (score.newRecord_) {
		rankImg_ = LoadGraph(("Data/Image/Rank/" + std::to_string(score.rank_ + 1) + ".png").c_str());
	}

	SoundManager::GetIns().Load(SoundManager::SOUND::CLERA);
}

void GameClear::Init(void)
{
	SoundManager::GetIns().Play(SoundManager::SOUND::CLERA);
}

void GameClear::Update(void)
{
	// ƒV[ƒ“‘JˆÚ
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	padKey_ = (((input & 0x40) == 0) && ((input & 0x20) == 0)) ? false : true;

	InputManager& ins = InputManager::GetInstance();
	if ((ins.IsTrgDown(KEY_INPUT_SPACE)) || (padKey_))
	{
		SceneManager::GetIns().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameClear::Draw(void)
{
	DrawGraph(0, 0, image_, true);
	auto score = Score::GetIns().GetNowScore();
	int fontSize = 75;
	SetFontSize(fontSize);
	DrawFormatString(160 - 4, 340 - 4, 0x000000, "TIME:%.2fs", score.score_);
	DrawFormatString(160, 340, 0xffffff, "TIME:%.2fs", score.score_);
	SetFontSize(16);

	if (score.newRecord_) {
		static size_t Blinking = 0;
		if (++Blinking > 60000) { Blinking = 0; }
		if (Blinking / 8 % 2 == 0) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150); }
		DrawRotaGraph(120, 280, 2, -AsoUtility::Deg2RadF(25.0f), rankImg_, true);
		if (Blinking / 8 % 2 == 0) { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); }
	}
}

void GameClear::Release(void)
{
	DeleteGraph(image_);
	SoundManager::GetIns().Delete(SoundManager::SOUND::CLERA);
}
