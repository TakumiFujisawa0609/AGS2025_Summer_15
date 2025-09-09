#include "GameOverScene.h"

#include<DxLib.h>

#include"../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include"../Manager/KeyManager.h"
#include"../Manager/SoundManager.h"


GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Load(void)
{
	backImage_ = LoadGraph("Data/Image/GameOver/GameOver.png");

	selectImg_[(int)SELECT::REPLAY] = AsoUtility::LoadImg("Data/Image/GameOver/Replay.png");
	selectImg_[(int)SELECT::TITLE] = AsoUtility::LoadImg("Data/Image/GameOver/Title.png");

	nowSelectFrameImg_ = AsoUtility::LoadImg("Data/Image/GameOver/NowSelectFrame.png");
}

void GameOverScene::Init(void)
{
	nowSelect_ = SELECT::REPLAY;
}

void GameOverScene::Update(void)
{
	auto& ins = KEY::GetIns();

	switch (nowSelect_)
	{
	case SELECT::REPLAY:
		if (ins.GetInfo(KEY_TYPE::ENTER).down) {
			Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true);
			SceneManager::GetIns().ChangeScene(SCENE_ID::BATTLEDONE);
			return;
		}
		if (ins.GetInfo(KEY_TYPE::MOVE_RIGHT).down) {
			Smng::GetIns().Play(SOUND::SE_SYSTEM_SELECT, true);
			nowSelect_ = SELECT::TITLE; 
		}
		break;
	case SELECT::TITLE:
		if (ins.GetInfo(KEY_TYPE::ENTER).down) {
			Smng::GetIns().Play(SOUND::SE_SYSTEM_BUTTON, true);
			SceneManager::GetIns().ChangeScene(SCENE_ID::TITLE);
			return;
		}
		if (ins.GetInfo(KEY_TYPE::MOVE_LEFT).down) {
			Smng::GetIns().Play(SOUND::SE_SYSTEM_SELECT, true);
			nowSelect_ = SELECT::REPLAY;
		}
		break;
	}
}

void GameOverScene::Draw(void)
{
	DrawGraph(0, 0, backImage_, true);
	for (int i = 0; i < (int)SELECT::MAX; i++) { DrawRotaGraph(SELECT_POS[i].x, SELECT_POS[i].y, 0.8f, 0, selectImg_[i], true); }
	DrawRotaGraph(SELECT_POS[(int)nowSelect_].x, SELECT_POS[(int)nowSelect_].y, 0.8f, 0, nowSelectFrameImg_, true);
}

void GameOverScene::Release(void)
{
	DeleteGraph(nowSelectFrameImg_);
	for (auto& id : selectImg_) { DeleteGraph(id); }
	DeleteGraph(backImage_);
}
