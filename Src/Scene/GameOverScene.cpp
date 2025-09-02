#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

#include "GameOverScene.h"

GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Load(void)
{
	image_ = LoadGraph("Data/Image/GameOver.png");
}

void GameOverScene::Init(void)
{
}

void GameOverScene::Update(void)
{
	// ÉVÅ[ÉìëJà⁄
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	padKey_ = (((input & 0x40) == 0) && ((input & 0x20) == 0)) ? false : true;

	InputManager& ins = InputManager::GetInstance();

	if ((ins.IsTrgDown(KEY_INPUT_SPACE)) || (padKey_))
	{
		SceneManager::GetIns().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameOverScene::Draw(void)
{
	DrawGraph(0, 0, image_, true);
}

void GameOverScene::Release(void)
{
	DeleteGraph(image_);
}
