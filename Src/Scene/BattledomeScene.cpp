#include"BattledomeScene.h"

#include<DxLib.h>

#include"../Manager/SceneManager.h"
#include"../Manager/Collision.h"
#include"../Manager/Camera.h"

#include"../Object/Player/Player.h"
#include"../Object/Bamboo/BambooManager.h"
#include"../Object/Stage/Tutorial/TutorialStage.h"
#include"../Object/Boss/BigBoss/Runboo/Runboo.h"

#include"../Object/Boss/BigBoss/Bammoon/Bammoon.h"
#include"../Object/Stage/BossStage/BammoonStage.h"

BattledomeScene::BattledomeScene()
{
}

BattledomeScene::~BattledomeScene()
{
}

void BattledomeScene::Init(void)
{
	using M = SceneManager;
	auto& sMng = M::GetInstance();

	//種類ごとにボスとステージを読み込む
	switch (sMng.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::ONE:
		stage_ = new TutorialStage();
	
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:
		stage_ = new TutorialStage();
		boss_ = new Runboo();
		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		stage_ = new BammoonStage();
		boss_ = new Bammoon();
		break;
	}

	player_ = new Player();
	player_->Init();

	stage_->Init();
	sMng.SetMapNum(stage_->GetMapNum());

	boss_->Init();
	boss_->TakePlayerPos((Vector2F*)&player_->GetUnit().pos_);


	bamboo_ = new BambooManager();
	bamboo_->Init((Vector2F*)&player_->GetUnit().pos_, (int*)&player_->GetBp());

	Collision::CreateInstance();
	auto& colli = Collision::GetInstance();
	colli.Init();
	colli.SetStage(stage_->GetMapData());

	auto& camera = Camera::GetInstance();
	camera.Init();
	camera.SetMapNum(stage_->GetMapNum());

}

void BattledomeScene::Update(void)
{
	boss_->Update();
	player_->Update();
	bamboo_->Update();

	//スクロール処理は田中に任せた
	if (SceneManager::GetInstance().GetNowBoss() == SceneManager::BOSS_KINDS::RUNBOO) Scroll();
}

void BattledomeScene::Draw(void)
{
	stage_->Draw();
	bamboo_->Draw();
	boss_->Draw();
	player_->Draw();
}

void BattledomeScene::Release(void)
{
	Collision::DeleteInstance();

	bamboo_->Release();
	delete bamboo_;
	bamboo_ = nullptr;

	player_->Release();
	delete player_;
	player_ = nullptr;

	boss_->Release();
	delete boss_;
	boss_ = nullptr;

	stage_->Release();
	delete stage_;
	stage_ = nullptr;
}

void BattledomeScene::UnitCollision(void)
{
	Collision& coll = Collision::GetInstance();


}

void BattledomeScene::Scroll(void)
{
	Camera& camera = Camera::GetInstance();

	camera.Follow(Camera::X, 1.0f);
}
