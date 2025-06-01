#include<DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include"../Manager/Collision.h"
#include"../Object/Player/Player.h"
#include"../Object/Manager/EnemyManager.h"
#include"../Object/Boss/BossTutorial.h"
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
	player_->Init();

	enemy_ = new EnemyManager();
	enemy_->Init();

	boss_ = new BossTutorial();
	boss_->Init();
	boss_->SetPlayer(player_);

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
	auto& ins = InputManager::GetInstance();

	player_->Update();
	stage_->Update();
	enemy_->Update();
	boss_->Update();

	for (int ii = 0; ii < EnemyBamboo::ENEMY_MAX; ii++)
	{
		enemy_->GetBamboo(ii)->SetTargetPos(player_->GetUnit().pos_);

		if (ins.IsTrgDown(KEY_INPUT_0))
		{
			enemy_->GetBamboo(ii)->SetDmg(10);
		}
		enemy_->GetBamboo(ii)->SetTargetPos(player_->GetUnit().pos_);
	}

	// ƒV[ƒ“‘JˆÚ
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}


	auto& camera = Camera::GetInstance();
	if (!boss_->GetEnCount()) {
		if (player_->GetUnit().disppos_.x > Application::MAIN_SCREEN_SIZE_X / 7 * 4 &&
			!((camera.GetPos().x + Application::MAIN_SCREEN_SIZE_X) - ((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2) >= Stage::STAGE_CHIP_SIZE * Stage::STAGE_NUM_X)) {
			camera.Follow(Camera::dir::X, player_->GetUnit().speed_);
			if (player_->IsEvasion())camera.Follow(Camera::dir::X, Player::EVASION_LENGTH);
		}

		if (player_->GetUnit().disppos_.x < Application::MAIN_SCREEN_SIZE_X / 7 * 3 &&
			!(camera.GetPos().x <= -((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2))) {
			camera.Follow(Camera::dir::X, -(player_->GetUnit().speed_));
			if (player_->IsEvasion())camera.Follow(Camera::dir::X, -Player::EVASION_LENGTH);
		}
	}
	else {
		if (!camera.BossSet()) {
			camera.Follow(Camera::dir::X, player_->GetUnit().speed_);
		}
	}

	if (player_->IsEvasion()) {
		SceneManager::GetInstance().ZoomPos(player_->GetUnit().disppos_);
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
	boss_->Draw();

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
	boss_->Release();
	delete boss_;
	boss_ = nullptr;

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
