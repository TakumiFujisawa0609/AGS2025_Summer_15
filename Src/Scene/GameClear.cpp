#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

#include "GameClear.h"

GameClear::GameClear(void)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Init(void)
{
}

void GameClear::Update(void)
{
	// ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameClear::Draw(void)
{
	DrawString(0, 0, "GameClear", 0xffffff, true);
}

void GameClear::Release(void)
{
}
