#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include"../Manager/Score/Score.h"

#include "GameClear.h"

GameClear::GameClear(void)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Init(void)
{
	image_ = LoadGraph("Data/Image/GameClear.png");
}

void GameClear::Update(void)
{
	// ÉVÅ[ÉìëJà⁄
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	padKey_= (((input & 0x40) == 0) && ((input & 0x20) == 0)) ? false : true;

	InputManager& ins = InputManager::GetInstance();
	if ((ins.IsTrgDown(KEY_INPUT_SPACE)) || (padKey_))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameClear::Draw(void)
{
	DrawGraph(0, 0, image_, true);
	auto& score = Score::GetIns();
	int fontSize = 75;
	SetFontSize(fontSize);
	DrawFormatString(180-4, 340-4, RGB(0, 0, 0, ), "TIME:%.2fs", score.GetNowScore().score_);
	DrawFormatString(180, 340, RGB(255, 255, 255, ), "TIME:%.2fs", score.GetNowScore().score_);
	SetFontSize(16);
}

void GameClear::Release(void)
{
	DeleteGraph(image_);
}
