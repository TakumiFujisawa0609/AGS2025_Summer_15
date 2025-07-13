#include"BattledomeScene.h"

#include<DxLib.h>

#include"../Manager/SceneManager.h"
#include"../Manager/Collision.h"
#include"../Manager/Camera.h"
#include"../Manager/Decoration/BlastEffect/BlastEffectManager.h"

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
		nokopy_ = new Nokopy();
		nokopy_->SetPlayerPosPtr(&player_->GetUnit().pos_);
		nokopy_->Init();

		break;
	case SceneManager::BOSS_KINDS::RUNBOO:
		stage_ = new TutorialStage();
		runboo_ = new Runboo();
		runboo_->SetPlayerPosPtr(&player_->GetUnit().pos_);
		runboo_->Init();
		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		stage_ = new BammoonStage();
		bammoon_ = new Bammoon();
		bammoon_->SetPlayerPosPtr(&player_->GetUnit().pos_);
		bammoon_->Init();
		break;
	}

	stage_->Init();
	sMng.SetMapNum(stage_->GetMapNum());


	bamboo_ = new BambooManager();
	bamboo_->Init();

	blastMng_ = new BlastEffectManager();
	blastMng_->Init();


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
	using M = SceneManager;
	auto& sMng = M::GetInstance();

	switch (sMng.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::NOKOPY:
		nokopy_->Update();
		if (!nokopy_->GetUnit().isAlive_) {
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:
		runboo_->Update();
		if (!runboo_->GetUnit().isAlive_) {
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
		}
		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		bammoon_->Update();
		if (!bammoon_->GetUnit().isAlive_) {
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
		}
		break;
	}

	player_->Update();
	bamboo_->Update();
	blastMng_->Update();

	UnitCollision();
	//スクロール処理は田中に任せた
	if (SceneManager::GetInstance().GetNowBoss() == SceneManager::BOSS_KINDS::RUNBOO) Scroll();
}

void BattledomeScene::Draw(void)
{
	stage_->Draw();
	bamboo_->Draw();

	using M = SceneManager;
	auto& sMng = M::GetInstance();

	switch (sMng.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::NOKOPY:
		nokopy_->Draw();
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:
		runboo_->Draw();
		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		bammoon_->Draw();
		break;
	}
	player_->Draw();
	blastMng_->Draw();
}

void BattledomeScene::Release(void)
{
	Collision::DeleteInstance();

	blastMng_->Release();
	delete blastMng_;
	blastMng_ = nullptr;

	bamboo_->Release();
	delete bamboo_;
	bamboo_ = nullptr;

	player_->Release();
	delete player_;
	player_ = nullptr;

	using M = SceneManager;
	auto& sMng = M::GetInstance();

	switch (sMng.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::NOKOPY:
		nokopy_->Release();
		delete nokopy_;
		nokopy_ = nullptr;
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:
		runboo_->Release();
		delete runboo_;
		runboo_ = nullptr;
		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		bammoon_->Release();
		delete bammoon_;
		bammoon_ = nullptr;
		break;
	}


	stage_->Release();
	delete stage_;
	stage_ = nullptr;
}

void BattledomeScene::UnitCollision(void)
{
	PlayerToBamboo();

	Collision& coll = Collision::GetInstance();
	//if (!boss_->IsInvici()) {		//ボスが無敵中早期リターン
		PlayerAttackToBossAttack();
		PlayerAttackToBoss();
	//}
	if (!player_->IsInvici()) {		//プレイヤーが無敵中早期リターン
		PlayerToBossAttack();
		PlayerToBoss();
	}

}

void BattledomeScene::Scroll(void)
{
	Camera& camera = Camera::GetInstance();

	camera.Follow(Camera::X, 1.0f);
}

void BattledomeScene::PlayerAttackToBossAttack(void)
{
	// プレイヤーの攻撃とボスの攻撃の当たり判定処理
	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();


	switch (mana.GetNowBoss())
	{
	case SceneManager::BOSS_KINDS::NOKOPY:
		for (int i = 0; i < nokopy_->GetObj().size(); i++) {

			if (!nokopy_->GetAttackIns()->IsParry()) continue;//パリィできないとき早期リターン	

			if (nokopy_->GetObj()[i].isCircle_) {
				if (ins.Circle(nokopy_->GetObj()[i], player_->DefaultAtt())) {
					mana.HitStop(SceneManager::HIT_STOP_TIME);
					nokopy_->ObjHit(i);
					bamboo_->Create(nokopy_->GetObj()[i].pos_, 1);
					player_->SetInvici(50);
				}
				for (auto& bpAtc : player_->GetBpAtt()) {
					if (ins.CircleAndRect(nokopy_->GetUnit(), bpAtc->GetObj())) {
						if (bpAtc->GetPower() >= 3) { mana.SHAKE(); }
						if (bpAtc->GetPower() >= 5) { mana.ZoomPos(bpAtc->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
						bpAtc->Off();
						nokopy_->ObjHit(i);
					}
				}
			}

			else {
				if (ins.CircleAndRect(player_->DefaultAtt(), nokopy_->GetObj()[i])) {
					mana.HitStop(SceneManager::HIT_STOP_TIME);
					nokopy_->ObjHit(i);
					//bamboo_->Create(boss_.GetAttackObj()[i].pos_, 3);
					player_->SetInvici(50);
				}
				//特殊攻撃
				for (auto& bpAtc : player_->GetBpAtt()) {
					if (ins.Rect(bpAtc->GetObj(), nokopy_->GetUnit())) {
						if (bpAtc->GetPower() >= 3) { mana.SHAKE(); }
						if (bpAtc->GetPower() >= 5) { mana.ZoomPos(bpAtc->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
						bpAtc->Off();
						nokopy_->ObjHit(i);
					}
				}
			}

		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:
		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		int i = 0;
		for (auto& bAtc : bammoon_->GetObj()) {
			if (ins.Circle(bAtc, player_->DefaultAtt())) {
				mana.HitStop(mana.HIT_STOP_TIME);
				player_->SetInvici(50);
				bamboo_->Create(bAtc.pos_, 1);
				bammoon_->ObjHit(i);
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
		if (nokopy_->GetUnit().isCircle_) {		//ボスの当たり判定が円形
			//通常攻撃
			if (ins.Circle(player_->DefaultAtt(), nokopy_->GetUnit())) {
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				nokopy_->SetDamage(0);
				bamboo_->Create(nokopy_->GetUnit().pos_, 1);
				if (nokopy_->GetAttackState() == Nokopy::ATTACK::RUSHOOT) {
					nokopy_->OnRushReflection();
				}
			}
			for (auto& bpAtc : player_->GetBpAtt()) {
				if (ins.CircleAndRect(nokopy_->GetUnit(), bpAtc->GetObj())) {
					if (bpAtc->GetPower() >= 3) { mana.SHAKE(); }
					if (bpAtc->GetPower() >= 5) { mana.ZoomPos(bpAtc->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
					bpAtc->Off();
					nokopy_->SetDamage(bpAtc->GetDamage());
					if (nokopy_->GetAttackState() == Nokopy::ATTACK::RUSHOOT) {
						nokopy_->OnRushReflection();
					}
				}
			}
		}
		else {		//ボスの当たり判定が矩形

			//通常攻撃
			if (ins.CircleAndRect(player_->DefaultAtt(), nokopy_->GetUnit())) {
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				nokopy_->SetDamage(5);
				bamboo_->Create(nokopy_->GetUnit().pos_, 1);
			}
			//特殊攻撃
			for (auto& bpAtc : player_->GetBpAtt()) {
				if (ins.Rect(bpAtc->GetObj(), nokopy_->GetUnit())) {
					if (bpAtc->GetPower() >= 3) { mana.SHAKE(); }
					if (bpAtc->GetPower() >= 5) { mana.ZoomPos(bpAtc->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
					bpAtc->Off();
					nokopy_->SetDamage(bpAtc->GetDamage());
				}
			}
		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:
		if (ins.Rect(player_->GetUnit(), runboo_->GetUnit()))
		{
			player_->Hit(10, runboo_->GetUnit().pos_);
		}
		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		if (ins.CircleAndRect(player_->DefaultAtt(), bammoon_->GetUnit())) {
			mana.HitStop(SceneManager::HIT_STOP_TIME);
			bammoon_->SetDamage(5);
			bamboo_->Create(bammoon_->GetUnit().pos_, 1, 30);
			if (bammoon_->GetAttackState() == (int)Bammoon::ATTACK::SWEEP) {
				bammoon_->SetDown(player_->GetUnit().pos_);
			}
		}
		for (auto& bpAtc : player_->GetBpAtt()) {
			if (ins.Ellipse(bpAtc->GetObj(), bammoon_->GetUnit())) {
				if (bpAtc->GetPower() >= 3) { mana.SHAKE(); }
				if (bpAtc->GetPower() >= 5) { mana.ZoomPos(bpAtc->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
				bpAtc->Off();
				bammoon_->SetDamage(bpAtc->GetDamage());
				blastMng_->On(bpAtc->GetObj().pos_);
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
		if (nokopy_->GetUnit().isCircle_) {
			if (ins.CircleAndRect(nokopy_->GetUnit(), player_->GetUnit())) {
				player_->Hit(5, nokopy_->GetUnit().pos_);

			}
		}
		else {

			if (ins.Rect(player_->GetUnit(), nokopy_->GetUnit())) {
				player_->Hit(5, nokopy_->GetUnit().pos_);
			}
		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:

		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		if (ins.Ellipse(player_->GetUnit(), bammoon_->GetUnit())) {
			player_->Hit(5, bammoon_->GetUnit().pos_);
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
		for (int i = 0; i < nokopy_->GetObj().size(); i++) {
			if (nokopy_->GetObj()[i].isCircle_) {
				if (ins.Circle(nokopy_->GetObj()[i], player_->GetUnit())) {
					player_->Hit(5, nokopy_->GetObj()[i].pos_);
					nokopy_->ObjHit(i);
				}
			}
			else {

				if (ins.CircleAndRect(player_->GetUnit(), nokopy_->GetObj()[i])) {
					player_->Hit(5, nokopy_->GetObj()[i].pos_);
					nokopy_->ObjHit(i);
				}
			}
		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:

		break;
	case SceneManager::BOSS_KINDS::BAMMOON:
		int i = 0;
		for (auto& bAtc : bammoon_->GetObj()) {
			if (ins.CircleAndRect(bAtc, player_->GetUnit())) {
				player_->Hit(5, bAtc.pos_);
				bammoon_->ObjHit(i);
			}

			for (auto& pAtc : player_->GetBpAtt()) {
				if (ins.CircleAndRect(bAtc, pAtc->GetObj())) {
					bammoon_->ObjHit(i);
					pAtc->Hit();
				}
			}
			i++;
		}
		break;
	}
}

void BattledomeScene::PlayerToBamboo(void)
{
	if (player_->GetHaveB())return;

	auto& ins = Collision::GetInstance();
	auto& mana = SceneManager::GetInstance().GetInstance();

	for (auto& b : bamboo_->GetBamboos()) {
		if (ins.CircleAndRect(b->GetUnit(), player_->GetUnit(), false)) {
			b->Collect();
			player_->BpOptain();
		}
	}


	for (auto& b : player_->GetBpAtt()) {
		if (ins.CircleAndRect(player_->DefaultAtt(), b->GetObj())) {
			mana.HitStop(SceneManager::HIT_STOP_TIME);
			b->Parry(player_->GetUnit().pos_);
		}
	}
}