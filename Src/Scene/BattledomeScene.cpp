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

#include"../Object/Stage/BossStage/NokoPyStage.h"
#include"../Object/Boss/BigBoss/Nokopy/Nokopy.h"

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

	player_ = new Player();
	player_->Init();

	//種類ごとにボスとステージを読み込む
	switch (sMng.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::NOKOPY:
		stage_ = new NokoPyStage();
		boss_ = new Nokopy();

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

	stage_->Init();
	sMng.SetMapNum(stage_->GetMapNum());

	boss_->SetPlayerPosPtr(&player_->GetUnit().pos_);
	boss_->Init();


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

	if (!boss_->GetUnit().isAlive_) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}
	UnitCollision();
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
	PlayerToBamboo();

	Collision& coll = Collision::GetInstance();
	if (!boss_->IsInvici()) {		//ボスが無敵中早期リターン
		PlayerAttackToBossAttack();
		PlayerAttackToBoss();
	}
	if (!player_->IsInvici()) {		//プレイヤーが無敵中早期リターン
		PlayerToBossAttack();
		PlayerToBoss();
	}

}

void BattledomeScene::Scroll(void)
{
	Camera& camera = Camera::GetInstance();

	camera.Follow(Camera::X, );
}

void BattledomeScene::PlayerAttackToBossAttack(void)
{
	// プレイヤーの攻撃とボスの攻撃の当たり判定処理
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();


	switch (mana.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::NOKOPY:
		for (int i = 0; i < boss_->GetObj().size(); i++) {
			if (!boss_->GetAttackIns()->IsParry()) continue;//パリィできないとき早期リターン		
			if (boss_->GetObj()[i].isCircle_) {
				if (ins.Circle(boss_->GetObj()[i], player_->DefaultAtt())) {
					mana.HitStop(SceneManager::HIT_STOP_TIME);
					boss_->ObjHit(i);
					bamboo_->Create(boss_->GetObj()[i].pos_, 3);
					player_->SetInvici(50);
				}
			}
			else {
				if (ins.CircleAndRect(player_->DefaultAtt(), boss_->GetObj()[i])) {
					mana.HitStop(SceneManager::HIT_STOP_TIME);
					boss_->ObjHit(i);
					//bamboo_->Create(boss_.GetAttackObj()[i].pos_, 3);
					player_->SetInvici(50);
				}
			}

		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:

		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		int i = 0;
		for (auto& bAtc : boss_->GetObj()) {
			if (ins.Circle(bAtc, player_->DefaultAtt())) {
				mana.HitStop(mana.HIT_STOP_TIME);
				player_->SetInvici(50);
				bamboo_->Create(bAtc.pos_, 1);
				boss_->ObjHit(i);
			}
			i++;
		}
		break;
	}
}

void BattledomeScene::PlayerAttackToBoss(void)
{
	// プレイヤーの攻撃とボスの当たり判定処理
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();
	switch (mana.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::NOKOPY:
		if (boss_->GetUnit().isCircle_) {		//ボスの当たり判定が円形
			//通常攻撃
			if (ins.Circle(player_->DefaultAtt(), boss_->GetUnit())) {
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				boss_->SetDamage(0);
				bamboo_->Create(boss_->GetUnit().pos_, 1);
			}
			for (auto& bpAtc : player_->GetBpAtt()) {
				if (ins.CircleAndRect(boss_->GetUnit(), bpAtc->GetObj())) {
					if (bpAtc->GetBp() >= 3)mana.SHAKE();
					mana.HitStop(SceneManager::HIT_STOP_TIME);
					boss_->SetDamage(bpAtc->GetDamage());
				}
			}
		}
		else {		//ボスの当たり判定が矩形

			//通常攻撃
			if (ins.CircleAndRect(player_->DefaultAtt(), boss_->GetUnit())) {
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				boss_->SetDamage(0);
				bamboo_->Create(boss_->GetUnit().pos_, 1);
			}
			//特殊攻撃
			for (auto& bpAtc : player_->GetBpAtt()) {
				if (ins.Rect(bpAtc->GetObj(), boss_->GetUnit())) {
					if (bpAtc->GetBp() >= 3)mana.SHAKE();
					mana.HitStop(SceneManager::HIT_STOP_TIME);
					boss_->SetDamage(bpAtc->GetDamage());
				}
			}
		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:

		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		if (ins.CircleAndRect(player_->DefaultAtt(), boss_->GetUnit())) {
			mana.HitStop(SceneManager::HIT_STOP_TIME);
			boss_->SetDamage(0);
			bamboo_->Create(boss_->GetUnit().pos_, 1, 30);
			if (boss_->GetAttackState() == (int)Bammoon::ATTACK::SWEEP) {
				boss_->SetDown(player_->GetUnit().pos_);
			}
		}
		for (auto& bpAtc : player_->GetBpAtt()) {
			if (ins.Ellipse(bpAtc->GetObj(), boss_->GetUnit())) {
				if (bpAtc->GetBp() >= 3)mana.SHAKE();
				mana.HitStop(5);
				boss_->SetDamage(bpAtc->GetDamage());
			}
		}
		break;
	}

}
void BattledomeScene::PlayerToBoss(void)
{
	// プレイヤーとボスの当たり判定処理
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	switch (mana.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::NOKOPY:
		if (boss_->GetUnit().isCircle_) {
			if (ins.CircleAndRect(boss_->GetUnit(), player_->GetUnit())) {
				player_->Hit(5, boss_->GetUnit().pos_);

			}
		}
		else {

			if (ins.Rect(player_->GetUnit(), boss_->GetUnit())) {
				player_->Hit(5, boss_->GetUnit().pos_);
			}
		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:

		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		if (ins.Ellipse(player_->GetUnit(), boss_->GetUnit())) {
			player_->Hit(5, boss_->GetUnit().pos_);
		}
		break;
	}

}

void BattledomeScene::PlayerToBossAttack(void)
{
	// プレイヤーとボスの攻撃の当たり判定処理  
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();
	switch (mana.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::NOKOPY:
		for (int i = 0; i < boss_->GetObj().size(); i++) {
			if (boss_->GetObj()[i].isCircle_) {
				if (ins.Circle(boss_->GetObj()[i], player_->GetUnit())) {
					player_->Hit(5, boss_->GetObj()[i].pos_);
					boss_->ObjHit(i);
				}
			}
			else {

				if (ins.CircleAndRect(boss_->GetObj()[i], player_->GetUnit())) {
					player_->Hit(5, boss_->GetObj()[i].pos_);
					boss_->ObjHit(i);
				}
			}
		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:

		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		int i = 0;
		for (auto& bAtc : boss_->GetObj()) {
			if (ins.CircleAndRect(bAtc, player_->GetUnit())) {
				player_->Hit(5, bAtc.pos_);
				boss_->ObjHit(i);
			}
			i++;
		}
		break;
	}
}

void BattledomeScene::PlayerToBamboo(void)
{
	if (player_->GetBp() >= Player::BP_MAX)return;

	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	for (auto& b : bamboo_->GetBamboos()) {
		if (ins.CircleAndRect(b->GetUnit(), player_->GetUnit(), false)) {
			b->Collect();
			player_->BpOptain((int)b->GetScale());
		}
	}
}