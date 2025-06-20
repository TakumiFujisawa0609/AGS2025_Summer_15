#include "TutorialScene.h"

#include<DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include"../Manager/Collision.h"

#include"../Application.h"
#include"../Utility/ShapesPosition.h"

#include"../Object/Player/Player.h"
#include"../Object/Manager/EnemyManager.h"
#include"../Object/Boss/Tutorial/BossTutorial.h"
#include"../Object/Stage/Tutorial/TutorialStage.h"
#include"../Application.h"
#include"../Utility/ShapesPosition.h"
#include"../Object/Manager/EffectManager.h"
#include"../Object/Effect/EffectBase.h"
#include"../Object/Effect/EffectTakeDrop.h"
#include"../Object/Bamboo/BambooManager.h"




TutorialScene::TutorialScene(void)
{
}

TutorialScene::~TutorialScene(void)
{
}

void TutorialScene::Init(void)
{
	Collision::CreateInstance();

	stage_ = new TutorialStage();
	stage_->Init();

	enemy_ = new EnemyManager();
	enemy_->Init();

	player_ = new Player();
	player_->Init();

	boss_ = new BossTutorial();
	boss_->Init();
	boss_->SetPlayer(player_);

	EffectManager::CreateInstance();
	EffectManager::GetInstance()->Init();

	Camera::GetInstance().Init();
	Collision::GetInstance().SetStage(stage_->GetMapData());

	bamboo_ = new BambooManager();
	bamboo_->Init((Vector2F*)&player_->GetUnit().pos_);


	x = 0;

}

void TutorialScene::Update(void)
{
	auto& ins = InputManager::GetInstance();

	player_->Update();
	enemy_->Update();
	boss_->Update();
	bamboo_->Update();
	EffectManager::GetInstance()->Update();

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
	/*if (!boss_->GetUnit().isAlive_)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}*/
	if (!player_->GetUnit().isAlive_) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
	}


	Scroll();

}

void TutorialScene::Draw(void)
{
	stage_->Draw();
	enemy_->Draw();
	boss_->Draw();
	player_->Draw();
	bamboo_->Draw();
	EffectManager::GetInstance()->Draw();

	DrawString(0, 0, "GameScene", 0xffffff, true);
}

void TutorialScene::Release(void)
{
	bamboo_->Release();
	delete bamboo_;
	bamboo_ = nullptr;

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

   EffectManager::GetInstance()->Release();
   EffectManager::DeleteInstance();

   

   Collision::DeleteInstance();  
}



void TutorialScene::Scroll(void)
{
	auto& camera = Camera::GetInstance();
	if (!boss_->GetEnCount()) {
		if (player_->GetUnit().disppos_.x > Application::MAIN_SCREEN_SIZE_X / 7 * 4 &&
			!((camera.GetPos().x + Application::MAIN_SCREEN_SIZE_X) - ((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2) >= TutorialStage::STAGE_CHIP_SIZE * TutorialStage::STAGE_NUM_X)) {
			camera.Follow(Camera::dir::X, player_->GetUnit().speed_);
		}

		if (player_->GetUnit().disppos_.x < Application::MAIN_SCREEN_SIZE_X / 7 * 3 &&
			!(camera.GetPos().x <= -((Application::MAIN_SCREEN_SIZE_X - Application::SCREEN_SIZE_X) / 2))) {
			camera.Follow(Camera::dir::X, -(player_->GetUnit().speed_));
		}
	}
	else {
		if (!camera.BossSet()) {
			camera.Follow(Camera::dir::X, player_->GetUnit().speed_);
		}
	}
}

void TutorialScene::ObjCollision(void)
{
	PlayerToBamboo();

	PlayerToEnemyBamboo();

	if (boss_->GetEnCount()) PlayerToBoss();
}

void TutorialScene::PlayerToBamboo(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	for (auto& b : bamboo_->GetBamboos()) {
		if (ins.CircleAndRect(b->GetUnit(),player_->GetUnit(),false)) {
			b->Collect();
			player_->BpOptain((int)b->GetScale());
		}
	}
}



void TutorialScene::PlayerToEnemyBamboo(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	for (int i = 0; i < EnemyBamboo::ENEMY_MAX; i++) {
		if (ins.Ellipse(player_->GetUnit(), enemy_->GetBamboo(i)->GetUnit())) {
			player_->Hit(5, enemy_->GetBamboo(i)->GetUnit().pos_);
			mana.HitStop();
		}
	}

	PlayerAttackToEnemyBamboo();
}

void TutorialScene::PlayerAttackToEnemyBamboo(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	for (int i = 0; i < EnemyBamboo::ENEMY_MAX; i++) {
		if (ins.CircleAndRect(player_->DefaultAtt(), enemy_->GetBamboo(i)->GetUnit())) {
			enemy_->GetBamboo(i)->SetDmg(0);
			bamboo_->Create(enemy_->GetBamboo(i)->GetUnit().pos_, 1);
		}
		for (auto& bpAtt : player_->GetBpAtt()) {
			if (ins.Rect(bpAtt->GetObj(), enemy_->GetBamboo(i)->GetUnit())) {
				if (bpAtt->GetBp() > 25) {
					mana.SHAKE();
					mana.Slow();
				}
				else {
					mana.HitStop();
				}
				enemy_->GetBamboo(i)->SetDmg(5);
			}
		}
	}


}




void TutorialScene::PlayerToBoss(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	if (ins.Rect(player_->GetUnit(), boss_->GetUnit())) {
		if (boss_->GetAttack() == BossTutorial::ATTACK::SLASH || boss_->GetAttack() == BossTutorial::ATTACK::TACKLE) {
			player_->Hit(5, boss_->GetUnit().pos_);
		}
	}

	PlayerToBossAttack();

	PlayerAttackToBoss();

	PlayerAttackToBossAttack();
}

void TutorialScene::PlayerToBossAttack(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();


	for (int i = 0; i < boss_->GetAttackObj().size(); i++) {
		if (ins.CircleAndRect(boss_->GetAttackObj()[i], player_->GetUnit())) {
			player_->Hit(5, boss_->GetAttackObj()[i].pos_);
			boss_->ObjHit(i);
		}
	}
}



void TutorialScene::PlayerAttackToBoss(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();
	if (ins.CircleAndRect(player_->DefaultAtt(), boss_->GetUnit())) {
		if (boss_->GetAttack() == BossTutorial::ATTACK::SLASH || boss_->GetAttack() == BossTutorial::ATTACK::TACKLE) {
			boss_->SetDown(player_->DefaultAtt().pos_);
			mana.HitStop();
			player_->SetInvici(50);
		}
		else {
			mana.HitStop();
			boss_->SetDamage(0);
			bamboo_->Create(boss_->GetUnit().pos_, 1);
		}
	}

	for (auto& bpAtt : player_->GetBpAtt()) {
		if (ins.Rect(bpAtt->GetObj(), boss_->GetUnit())) {
			if (bpAtt->GetBp() > 25) {
				mana.SHAKE();
				mana.Slow();
			}
			else {
				mana.HitStop();
			}
			boss_->SetDamage(bpAtt->GetDamage());
		}
	}
}

void TutorialScene::PlayerAttackToBossAttack(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();
	for (int i = 0; i < boss_->GetAttackObj().size(); i++) {
		if (ins.Circle(boss_->GetAttackObj()[i], player_->DefaultAtt())) {
			mana.HitStop();
			boss_->ObjHit(i);
			bamboo_->Create(boss_->GetAttackObj()[i].pos_, 3);
			if (boss_->GetAttack() == BossTutorial::ATTACK::SLASH || boss_->GetAttack() == BossTutorial::ATTACK::TACKLE) {
				boss_->SetDown(player_->DefaultAtt().pos_);
			}
			player_->SetInvici(50);
		}
	}


	
	
}
