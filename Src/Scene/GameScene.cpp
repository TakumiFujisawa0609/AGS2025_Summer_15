#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include"../Manager/Collision.h"
#include"../Object/Player/Player.h"
#include"../Object/Manager/EnemyManager.h"
#include"../Object/Stage/Stage.h"
#include"../Application.h"
#include "GameScene.h"
#include"../Utility/ShapesPosition.h"



GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	stage_ = new Stage();
	stage_->Init();

	player_ = new Player();
	player_->GameInit();

	enemy_ = new EnemyManager();
	enemy_->Init();

	Camera::GetInstance().Init();
	Collision::CreateInstance();
	for (int y = 0; y < Stage::STAGE_NUM_Y; y++) {
		for (int x = 0; x < Stage::STAGE_NUM_X; x++) {
			Collision::GetInstance().SetStage(stage_->GetMapData(y, x), y, x);
		}
	}
	x = 0;
}

void GameScene::Update(void)
{


	player_->Update();
	stage_->Update();
	enemy_->Update();

	for (int ii = 0; ii < EnemyManager::ENEMY_MAX; ii++)
	{
		enemy_->GetBamboo(ii)->SetTargetPos(player_->GetPlayer());
		enemy_->GetBamboo(ii)->SetStartPos(ii);
	}

	// ƒV[ƒ“‘JˆÚ
	auto& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}



	if (player_->GetPlayer().disppos_.x > SceneManager::MAIN_SCREEN_SIZE_X / 7 * 4) {
		Camera::GetInstance().Follow(Camera::dir::X, player_->GetPlayer().speed_);
		if (player_->IsEvasion())Camera::GetInstance().Follow(Camera::dir::X, Player::EVASION_LENGTH);
	}

	if (player_->GetPlayer().disppos_.x < SceneManager::MAIN_SCREEN_SIZE_X / 7 * 3) {
		Camera::GetInstance().Follow(Camera::dir::X, -(player_->GetPlayer().speed_));
		if (player_->IsEvasion())Camera::GetInstance().Follow(Camera::dir::X, -Player::EVASION_LENGTH);
	}



	if (player_->IsEvasion()) {
		SceneManager::GetInstance().ZoomPos(player_->GetPlayer().disppos_);
		SceneManager::GetInstance().ZoomScale(1.4f);
	}

	if (ins.IsTrgDown(KEY_INPUT_Z)) {
		SceneManager::GetInstance().SHAKE();
	}

}

void GameScene::Draw(void)
{
	stage_->Draw();
	enemy_->Draw();
	player_->Draw();

	DrawString(0, 0, "GameScene", 0xffffff, true);
	
	//std::vector<Vector2F>pos = ShapesPosition::GetPositionCircle(SceneManager::MAIN_SCREEN_SIZE_X/2, SceneManager::MAIN_SCREEN_SIZE_Y/2, x, x, 12);
	//for (int i = 0; i < (int)pos.size(); i++) {
	//	DrawCircle(pos[i].x, pos[i].y, 10, 0xff0000, true);
	//}

	//
	//x += 0.05f;
	// pos=ShapesPosition::GetPositionWave(x, SceneManager::MAIN_SCREEN_SIZE_Y/2, 200.0f, 1000.0f, x, 20, 100.0f);
	//for (int i = 0; i <(int) pos.size(); i++) {
	//	DrawCircle(pos[i].x, pos[i].y,10,0x00ff00, true);
	//}
}

void GameScene::Release(void)
{
	enemy_->Relese();
	delete enemy_;
	enemy_ = nullptr;

	stage_->Release();
	delete stage_;
	stage_ = nullptr;


	player_->Release();
	delete player_;
	player_ = nullptr;
}
