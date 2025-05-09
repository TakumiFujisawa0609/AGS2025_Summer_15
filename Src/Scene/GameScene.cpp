#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include"../Object/Player/Player.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	player_ = new Player();
	player_->GameInit();

	stage_ = new Stage();
	stage_->Init();

	// カメラモード：定点カメラ
	SceneManager::GetInstance().GetCamera().ChangeMode(Camera::MODE::FOLLOW);

}

void GameScene::Update(void)
{
	player_->Update();
	stage_->Update();

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}


}

void GameScene::Draw(void)
{
	stage_->Draw();
	player_->Draw();

	DrawString(0, 0, "GameScene", 0xffffff, true);

	Camera::GetInstance().DrawDebug();
	
}

void GameScene::Release(void)
{
	stage_->Release();
	delete stage_;
	stage_ = nullptr;

	player_->Release();
	delete player_;
	player_ = nullptr;
}
