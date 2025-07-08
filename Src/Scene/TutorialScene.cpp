#include "TutorialScene.h"

#include<DxLib.h>
#include<EffekseerForDXLib.h>
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
#include"../Object/Bamboo/BambooManager.h"
#include"../Manager/Decoration//EffectManager.h"
#include"../Manager/Decoration/BlastEffect/BlastEffectManager.h"



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
	SceneManager::GetInstance().SetMapNum(stage_->GetMapNum());

	enemy_ = new EnemyManager();
	enemy_->Init();

	player_ = new Player();
	player_->Init();

	boss_ = new BossTutorial();
	boss_->Init();
	boss_->SetPlayer(player_);
	effect = -1;
	//effect = LoadEffekseerEffect("Data/Effect/BossDeath.efkefc");
	EffectManager::GetInstance().Add(EffectManager::EFFECT::BOSS_DEATH,effect );
	EffectManager::GetInstance().Play2D(EffectManager::EFFECT::BOSS_DEATH,
		player_->GetUnit().disppos_, 1, 1);

	Camera::GetInstance().Init();
	Camera::GetInstance().SetMapNum(stage_->GetMapNum());

	Collision::GetInstance().SetStage(stage_->GetMapData());

	bamboo_ = new BambooManager();
	bamboo_->Init();


	blast_ = new BlastEffectManager();
	blast_->Init();

	x = 0;

}

void TutorialScene::Update(void)
{
	auto& ins = InputManager::GetInstance();

	player_->Update();
	enemy_->Update();
	boss_->Update();
	bamboo_->Update();
	blast_->Update();

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
	bamboo_->Draw();
	enemy_->Draw();
	boss_->Draw();
	player_->Draw();
	blast_->Draw();

	DrawString(0, 0, "GameScene", 0xffffff, true);
}

void TutorialScene::Release(void)
{
	blast_->Release();
	delete blast_;
	blast_ = nullptr;

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



   

   Collision::DeleteInstance();  
}



void TutorialScene::Scroll(void)
{
	auto& camera = Camera::GetInstance();
	if (!boss_->GetEnCount()) {
		if (player_->GetUnit().disppos_.x > Application::SCREEN_SIZE_X / 7 * 3 &&
			!((camera.GetPos().x + Application::SCREEN_SIZE_X) >= TutorialStage::STAGE_CHIP_SIZE * stage_->GetMapNum().x)) {
			camera.Follow(Camera::dir::X, (player_->GetState() == Player::STATE::EVASION) ? Player::EVASION_SPEED : player_->GetUnit().speed_);
		}

		if (player_->GetUnit().disppos_.x < Application::SCREEN_SIZE_X / 7 * 2 &&
			!(camera.GetPos().x <= 0)) {
			camera.Follow(Camera::dir::X, -((player_->GetState() == Player::STATE::EVASION) ? Player::EVASION_SPEED : player_->GetUnit().speed_));
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

	if (boss_->GetEnCount()) PlayerToBoss();
	else					 PlayerToEnemyBamboo();
}

void TutorialScene::PlayerToBamboo(void)
{
	if (player_->GetHaveB())return;

	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	for (auto& b : bamboo_->GetBamboos()) {
		if (ins.CircleAndRect(b->GetUnit(),player_->GetUnit(),false)) {
			b->Collect();
			player_->BpOptain();
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
			mana.HitStop(SceneManager::HIT_STOP_TIME);
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
			enemy_->GetBamboo(i)->SetDmg(5);
			bamboo_->Create(enemy_->GetBamboo(i)->GetUnit().pos_, 1, 50);
		}
		for (auto& bpAtt : player_->GetBpAtt()) {
			if (ins.Rect(bpAtt->GetObj(), enemy_->GetBamboo(i)->GetUnit())) {
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				bpAtt->Hit();
				enemy_->GetBamboo(i)->SetDmg(bpAtt->GetDamage());
				blast_->On(bpAtt->GetObj().pos_);
			}
		}
	}


}




void TutorialScene::PlayerToBoss(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	if (ins.Rect(player_->GetUnit(), boss_->GetUnit())) {
		player_->Hit(5, boss_->GetUnit().pos_);
	}

	PlayerAttackToBoss();
	PlayerAttackToBossAttack();
	PlayerToBossAttack();

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
		if ((boss_->GetAttack() == BossTutorial::ATTACK::SLASH && boss_->GetDrawpat() == BossTutorial::DRAWPAT::E_SLASH_START) ||
			boss_->GetAttack() == BossTutorial::ATTACK::TACKLE) {
			boss_->SetDown(player_->DefaultAtt().pos_);
			mana.HitStop(SceneManager::HIT_STOP_TIME);
			player_->SetInvici(50);
		}
		else {
			mana.HitStop(SceneManager::HIT_STOP_TIME);
			boss_->SetDamage(5);
			bamboo_->Create(boss_->GetUnit().pos_, 1,50);
		}
	}

	for (auto& bpAtt : player_->GetBpAtt()) {
		if (ins.Rect(bpAtt->GetObj(), boss_->GetUnit())) {
			if (bpAtt->GetBounce() >= 4) mana.SHAKE();
			mana.HitStop(SceneManager::HIT_STOP_TIME);
			bpAtt->Off();
			boss_->SetDamage(bpAtt->GetDamage());
			blast_->On(bpAtt->GetObj().pos_);
		}
	}
}

void TutorialScene::PlayerAttackToBossAttack(void)
{
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();
	for (int i = 0; i < boss_->GetAttackObj().size(); i++) {
		if (ins.Circle(boss_->GetAttackObj()[i], player_->DefaultAtt())) {
			mana.HitStop(SceneManager::HIT_STOP_TIME);
			boss_->ObjHit(i);
			bamboo_->Create(boss_->GetAttackObj()[i].pos_, 1,50);
			player_->SetInvici(50);
		}
	}

	for (auto& bpAtt : player_->GetBpAtt()) {
		int i = 0;
		for (auto& bossAt : boss_->GetAttackObj()) {
			if (ins.CircleAndRect(bossAt, bpAtt->GetObj())) {
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				boss_->ObjHit(i);
				bpAtt->Hit();
			}
			i++;
		}
	}
	
}
