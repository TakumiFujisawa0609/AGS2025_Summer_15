#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

	// カメラモード：定点カメラ
	SceneManager::GetInstance().GetCamera().ChangeMode(Camera::MODE::FOLLOW);

}

void GameScene::Update(void)
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}


}

void GameScene::Draw(void)
{

	DrawString(0, 0, "GameScene", 0xffffff, true);

	Camera::GetInstance().DrawDebug();
	
}

void GameScene::Release(void)
{
}
