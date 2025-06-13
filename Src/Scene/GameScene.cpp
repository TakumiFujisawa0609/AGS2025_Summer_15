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
#include"../Object/Manager/EffectManager.h"
#include"../Object/Effect/EffectBase.h"
#include"../Object/Effect/EffectTakeDrop.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	Collision::CreateInstance();

	stage_ = new Stage();
	stage_->Init();


	enemy_ = new EnemyManager();
	enemy_->Init();
	player_ = new Player();
	player_->Init();

	boss_ = new BossTutorial();
	boss_->Init();
	boss_->SetPlayer(player_);

	efctMng_ = new EffectManager();

	Camera::GetInstance().Init();
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
	efctMng_->Update();

	for (int ii = 0; ii < EnemyBamboo::ENEMY_MAX; ii++)
	{
		enemy_->GetBamboo(ii)->SetTargetPos(player_->GetUnit().pos_);

		if (ins.IsTrgDown(KEY_INPUT_0))
		{
			enemy_->GetBamboo(ii)->SetDmg(10);
		}
		enemy_->GetBamboo(ii)->SetTargetPos(player_->GetUnit().pos_);
	}

	//オブジェクト同士の当たり判定
	ObjCollision();

	//シーン遷移
	if (!boss_->GetUnit().isAlive_)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}
	if (!player_->GetUnit().isAlive_) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
	}


	Scroll();

}

void GameScene::Draw(void)
{
	stage_->Draw();
	enemy_->Draw();
	player_->Draw();
	boss_->Draw();
	efctMng_->Draw();

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

   player_->Release();  
   delete player_;  
   player_ = nullptr;  

   stage_->Release();  
   delete stage_;  
   stage_ = nullptr;  

   efctMng_->Release();  
   delete efctMng_;  
   efctMng_ = nullptr;  

   // efects_ の delete  
   for (auto& effect : effects_) {  
       effect.reset(); 
   }  
   effects_.clear();  

   Collision::DeleteInstance();  
}



void GameScene::Scroll(void)
{
	auto& camera = Camera::GetInstance();
	if (!boss_->GetEnCount()) {
		if (player_->GetUnit().disppos_.x > Application::MAIN_SCREEN_SIZE_X / 7 * 4 &&
			!((camera.GetPos().x + Application::MAIN_SCREEN_SIZE_X) - ((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2) >= Stage::STAGE_CHIP_SIZE * Stage::STAGE_NUM_X)) {
			camera.Follow(Camera::dir::X, player_->GetUnit().speed_);
			//if (player_->IsEvasion())camera.Follow(Camera::dir::X, Player::EVASION_LENGTH);
		}

		if (player_->GetUnit().disppos_.x < Application::MAIN_SCREEN_SIZE_X / 7 * 3 &&
			!(camera.GetPos().x <= -((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2))) {
			camera.Follow(Camera::dir::X, -(player_->GetUnit().speed_));
			//if (player_->IsEvasion())camera.Follow(Camera::dir::X, -Player::EVASION_LENGTH);
		}
	}
	else {
		if (!camera.BossSet()) {
			camera.Follow(Camera::dir::X, player_->GetUnit().speed_);
		}
	}
}

void GameScene::ObjCollision(void)
{
	PlayerToBoss();
	PlayerToEnemyBamboo();
	PlayerAttackToBoss();
}

void GameScene::PlayerToBoss(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	if (ins.Rect(player_->GetUnit(), boss_->GetUnit())) {
		player_->Hit(5,boss_->GetUnit().pos_);
		/*mana.HitStop();
		mana.SHAKE();*/
	}

	//if (ins.Rect(player_->GetUnit(), boss_->GetUnit())) {
	//	if ((player_->IsInvincible() || player_->IsJustGuard())
	//		&& !player_->IsHit()) {
	//		mana.Slow();
	//	}
	//	else {
	//		player_->SetHitOn();
	//		player_->SetXAccel(20.0f);
	//		mana.SHAKE();
	//	}
	//	//mana.HitStop();
	//}

	PlayerToBossAttack();
}

void GameScene::PlayerToBossAttack(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	for (auto obj : boss_->GetAttackObj())
	{
		if (ins.CircleAndRect(obj, player_->GetUnit())) {
			player_->Hit(5, obj.pos_);
			mana.HitStop();
			mana.SHAKE();
			//if ((player_->IsInvincible() || player_->IsJustGuard())
			//	&& !player_->IsHit()) {
			//	mana.Slow();
			//}
			//else {
			//	player_->SetHitOn();
			//	//player_->SetXAccel(20.0f);
			//	mana.SHAKE();
			//}
		}
	}
}

void GameScene::PlayerToEnemyBamboo(void)
{
	//auto& ins = Collision::GetInstance();
	//auto& mana = SceneManager::GetInstance().GetInstance();

	//for (int i = 0; i < EnemyBamboo::ENEMY_MAX; i++) {
	//	if (ins.Ellipse(player_->GetUnit(), enemy_->GetBamboo(i)->GetUnit()) && !player_->Muteki()) {
	//		player_->Damage(5, enemy_->GetBamboo(i)->GetUnit().pos_);
	//		mana.HitStop();
	//		mana.SHAKE();
	//	}
	//}

}

void GameScene::PlayerAttackToBoss(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();
	if (ins.CircleAndRect(player_->DefaultAtt(), boss_->GetUnit())) {
		mana.HitStop();
		boss_->SetDamage(1);
        effects_.push_back(std::make_shared<EffectTakeDrop>());
		efctMng_->Init();
		efctMng_->AddEffect(1, effects_.back());
	}
}
