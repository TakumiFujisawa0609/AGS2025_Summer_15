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

void GameOverScene::Init(void)
{
}

void GameOverScene::Update(void)
{
	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameOverScene::Draw(void)
{
	DrawString(0, 0, "GameOver", 0xffffff, true);
}

void GameOverScene::Release(void)
{
}
