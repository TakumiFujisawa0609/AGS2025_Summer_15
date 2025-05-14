#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include"../Object/Player/Player.h"
#include"../Application.h"
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

	Camera::GetInstance().Init();
}

void GameScene::Update(void)
{
	player_->Update();
	stage_->Update();

	// ƒV[ƒ“‘JˆÚ
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}



	if (player_->GetPlayer().disppos_.x > Application::SCREEN_SIZE_X / 7 * 4) {
		if (ins.IsNew(KEY_INPUT_D)) {
			Camera::GetInstance().Follow(Camera::dir::X, player_->GetPlayer().speed_);
		}
	}
	if (player_->GetPlayer().disppos_.x < Application::SCREEN_SIZE_X / 7 * 3) {
		if (ins.IsNew(KEY_INPUT_A)) {
			Camera::GetInstance().Follow(Camera::dir::X, -(player_->GetPlayer().speed_));
		}
	}

}

void GameScene::Draw(void)
{
	stage_->Draw();
	player_->Draw();

	DrawString(0, 0, "GameScene", 0xffffff, true);

	
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
