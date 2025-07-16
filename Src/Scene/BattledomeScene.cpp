#include"BattledomeScene.h"

#include<DxLib.h>

#include"../Manager/SceneManager.h"
#include"../Manager/Collision.h"
#include"../Manager/Camera.h"
#include"../Manager/Decoration/BlastEffect/BlastEffectManager.h"
#include"../Manager/Score/Score.h"
#include"../Manager/SoundManager.h"

#include"../Object/Player/Player.h"
#include"../Object/Bamboo/BambooManager.h"

#include"../Object/Boss/Tutorial/BossTutorial.h"
#include"../Object/Stage/Tutorial/TutorialStage.h"

#include"../Object/Boss/BigBoss/Runboo/Runboo.h"
#include"../Object/Stage/BossStage/Stage1.h"

#include"../Object/Boss/BigBoss/Bammoon/Bammoon.h"
#include"../Object/Stage/BossStage/BammoonStage.h"

#include"../Object/Stage/BossStage/NokoPyStage.h"
#include"../Object/Boss/BigBoss/Nokopy/Nokopy.h"
#include"../Object/Boss/BigBoss/Runboo/Weakness.h"
#include"../Object/Boss/BigBoss/Runboo/Attack/WeakBullet.h"


BattledomeScene::BattledomeScene()
{
}

BattledomeScene::~BattledomeScene()
{
}

void BattledomeScene::Init(void)
{
	time_ = 0.0f;

	using M = SceneManager;
	auto& sMng = M::GetInstance();

	player_ = new Player();
	player_->Init();

	//種類ごとにボスとステージを読み込む
	switch (sMng.GetNowBoss())
	{
	case M::BOSS_KINDS::TUTORIAL:
		stage_ = new TutorialStage();
		tutorial_ = new BossTutorial();
		tutorial_->Init();
		tutorial_->SetPlayer(player_);
		break;
	case M::BOSS_KINDS::NOKOPY:
		stage_ = new NokoPyStage();
		nokopy_ = new Nokopy();
		nokopy_->SetPlayerPosPtr(&player_->GetUnit().pos_);
		nokopy_->Init();

		break;
	case M::BOSS_KINDS::RUNBOO:
		stage_ = new Stage1();
		runboo_ = new Runboo();
		runboo_->SetPlayerPosPtr(&player_->GetUnit().pos_);
		runboo_->Init();

		break;
	case M::BOSS_KINDS::BAMMOON:
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

	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Load(S::SOUND::BPHIT);

}

void BattledomeScene::Update(void)
{
	using M = SceneManager;
	auto& sMng = M::GetInstance();

	switch (sMng.GetNowBoss())
	{
	case M::BOSS_KINDS::TUTORIAL:
		tutorial_->Update();
		if (!tutorial_->GetUnit().isAlive_) {
			Score::GetIns().SetScore(time_);
			sMng.ChangeScene(M::SCENE_ID::CLEAR);
		}
		break;
	case M::BOSS_KINDS::NOKOPY:
		nokopy_->Update();
		if (!nokopy_->GetUnit().isAlive_) {
			Score::GetIns().SetScore(time_);
			sMng.ChangeScene(M::SCENE_ID::CLEAR);
		}
		break;
	case M::BOSS_KINDS::RUNBOO:
		runboo_->Update();
		if (!runboo_->GetUnit().isAlive_) {
			Score::GetIns().SetScore(time_);
			sMng.ChangeScene(M::SCENE_ID::CLEAR);
		}
		break;
	case M::BOSS_KINDS::BAMMOON:
		bammoon_->Update();
		if (!bammoon_->GetUnit().isAlive_) {
			Score::GetIns().SetScore(time_);
			sMng.ChangeScene(M::SCENE_ID::CLEAR);
		}
		break;
	}

	player_->Update();
	bamboo_->Update();
	blastMng_->Update();
	if (player_->GetUnit().hp_ <= 0) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
	}

	UnitCollision();
	//スクロール処理は田中に任せた
	Scroll();

	time_ += sMng.GetDeltaTime();
}

void BattledomeScene::Draw(void)
{
	stage_->BackDraw();

	bamboo_->Draw();

	using M = SceneManager;
	auto& sMng = M::GetInstance();

	switch (sMng.GetNowBoss())
	{
	case M::BOSS_KINDS::TUTORIAL:
		tutorial_->Draw();
		break;
	case M::BOSS_KINDS::NOKOPY:
		nokopy_->Draw();
		break;
	case M::BOSS_KINDS::RUNBOO:
		break;
	case M::BOSS_KINDS::BAMMOON:
		bammoon_->Draw();
		break;
	}

	stage_->Draw();

	player_->Draw();

	blastMng_->Draw();

	switch (sMng.GetNowBoss())
	{
	case M::BOSS_KINDS::TUTORIAL:
		tutorial_->DrawHP();
		break;
	case SceneManager::BOSS_KINDS::NOKOPY:
		nokopy_->DrawHp();
		break;
	case M::BOSS_KINDS::RUNBOO:
		runboo_->Draw();
		break;
	case M::BOSS_KINDS::BAMMOON:
		bammoon_->DrawHp();
		break;
	}
	player_->DrawHp();

	int fontSize = 50;
	SetFontSize(fontSize);
	DrawFormatString(0 - 2, (Application::SCREEN_SIZE_Y - fontSize) - 2, RGB(0, 0, 0), "TIME::%.2fs", time_);
	DrawFormatString(0, Application::SCREEN_SIZE_Y - fontSize, RGB(255, 255, 255), "TIME::%.2fs", time_);
	SetFontSize(16);
}

void BattledomeScene::Release(void)
{
	using S = SoundManager;
	auto& sound = S::GetIns();
	sound.Delete(S::SOUND::BPHIT);

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
	case M::BOSS_KINDS::TUTORIAL:
		tutorial_->Release();
		delete tutorial_;
		tutorial_ = nullptr;
		break;
	case M::BOSS_KINDS::NOKOPY:
		nokopy_->Release();
		delete nokopy_;
		nokopy_ = nullptr;
		break;
	case M::BOSS_KINDS::RUNBOO:
		runboo_->Release();
		delete runboo_;
		runboo_ = nullptr;
		break;
	case M::BOSS_KINDS::BAMMOON:
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

	using M = SceneManager;
	auto& sMng = M::GetInstance();

	if (sMng.GetNowBoss() == M::BOSS_KINDS::RUNBOO) {
		camera.Follow(Camera::X, 1.0f);
	}
}

void BattledomeScene::PlayerAttackToBossAttack(void)
{
	// プレイヤーの攻撃とボスの攻撃の当たり判定処理
	auto& ins = Collision::GetInstance();
	using M = SceneManager;
	auto& mana = M::GetInstance().GetInstance();


	switch (mana.GetNowBoss())
	{
	case M::BOSS_KINDS::TUTORIAL: {
		int i = 0;
		for (auto& at : tutorial_->GetAttackObj()) {
			if (ins.Circle(at, player_->DefaultAtt())) {
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				tutorial_->ObjHit(i);
				player_->SetInvici(50);
				switch (tutorial_->GetAttack())
				{
				case BossTutorial::BULLET:
					bamboo_->Create(tutorial_->GetAttackObj()[i].pos_, 1, 5);
					break;
				case BossTutorial::BLAST:
					bamboo_->Create(tutorial_->GetAttackObj()[i].pos_, 1);
					break;
				case BossTutorial::SLASH:
				case BossTutorial::ROAR:
					break;
				}
			}

			for (auto& bpAtt : player_->GetBpAtt()) {
				if (ins.CircleAndRect(at, bpAtt->GetObj())) {
					mana.HitStop(SceneManager::HIT_STOP_TIME);
					tutorial_->ObjHit(i);
					bpAtt->Hit();
				}
			}

			i++;
		}
		break;
	}
	case M::BOSS_KINDS::NOKOPY:
		for (int i = 0; i < nokopy_->GetObj().size(); i++) {

			if (!nokopy_->GetAttackIns()->IsParry()) continue;//パリィできないとき早期リターン	

			if (nokopy_->GetObj()[i].isCircle_) {
				if (ins.Circle(nokopy_->GetObj()[i], player_->DefaultAtt())) {
					mana.HitStop(M::HIT_STOP_TIME);
					nokopy_->ObjHit(i);
					bamboo_->Create(nokopy_->GetObj()[i].pos_, 1);
					player_->SetInvici(50);
				}
				for (auto& bpAtc : player_->GetBpAtt()) {
					if (ins.CircleAndRect(nokopy_->GetUnit(), bpAtc->GetObj())) {
						//if (bpAtc->GetPower() >= 3) { mana.SHAKE(); }
						//if (bpAtc->GetPower() >= 5) { mana.ZoomPos(bpAtc->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
						//bpAtc->Off();
						nokopy_->ObjHit(i);
					}
				}
			}

			else {
				if (ins.CircleAndRect(player_->DefaultAtt(), nokopy_->GetObj()[i])) {
					mana.HitStop(M::HIT_STOP_TIME);
					nokopy_->ObjHit(i);
					bamboo_->Create(nokopy_->GetObj()[i].pos_, 1);
					//bamboo_->Create(boss_.GetAttackObj()[i].pos_, 3);
					player_->SetInvici(50);
				}
				//特殊攻撃
				for (auto& bpAtc : player_->GetBpAtt()) {
					if (ins.Rect(bpAtc->GetObj(), nokopy_->GetUnit())) {
						//if (bpAtc->GetPower() >= 3) { mana.SHAKE(); }
						//if (bpAtc->GetPower() >= 5) { mana.ZoomPos(bpAtc->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
						//bpAtc->Off();
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
				bammoon_->ObjHit(i);
				bamboo_->Create(bAtc.pos_, 1,30);
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
	using M = SceneManager;
	auto& mana = M::GetInstance().GetInstance();
	switch (mana.GetNowBoss())
	{
	case M::BOSS_KINDS::TUTORIAL:
		if (ins.CircleAndRect(player_->DefaultAtt(), tutorial_->GetUnit())) {
			if ((tutorial_->GetAttack() == BossTutorial::ATTACK::SLASH && tutorial_->GetDrawpat() == BossTutorial::DRAWPAT::E_SLASH_START) ||
				tutorial_->GetAttack() == BossTutorial::ATTACK::TACKLE) {
				tutorial_->SetDown(player_->DefaultAtt().pos_);
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				player_->SetInvici(50);
				bamboo_->Create(tutorial_->GetUnit().pos_, 1);
			}
			else {
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				tutorial_->SetDamage(5);
				bamboo_->Create(tutorial_->GetUnit().pos_, 1, 30);
			}
		}

		for (auto& bpAtt : player_->GetBpAtt()) {
			if (ins.Rect(bpAtt->GetObj(), tutorial_->GetUnit())) {
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				if (bpAtt->GetPower() >= 3) { mana.SHAKE(); }
				if (bpAtt->GetPower() >= 5) { mana.ZoomPos(bpAtt->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
				bpAtt->Off();
				tutorial_->SetDamage(bpAtt->GetDamage());
				blastMng_->On(bpAtt->GetObj().pos_);
			}
		}
		break;
	case M::BOSS_KINDS::NOKOPY:
		//通常攻撃
		if (ins.Circle(player_->DefaultAtt(), nokopy_->GetUnit())) {
			mana.HitStop(SceneManager::HIT_STOP_TIME);
			nokopy_->SetDamage(5);
			bamboo_->Create(nokopy_->GetUnit().pos_, 1, 30);
			if (nokopy_->GetAttackState() == Nokopy::ATTACK::RUSHOOT) {
				nokopy_->OnRushReflection();
			}
		}
		if (nokopy_->GetDive())return;
		for (auto& bpAtc : player_->GetBpAtt()) {
			if (ins.CircleAndRect(nokopy_->GetUnit(), bpAtc->GetObj())) {
				//if (bpAtc->GetBp() >= 3)mana.SHAKE();
				mana.HitStop(SceneManager::HIT_STOP_TIME);
				if (bpAtc->GetPower() >= 3) { mana.SHAKE(); }
				if (bpAtc->GetPower() >= 5) { mana.ZoomPos(bpAtc->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
				nokopy_->SetDamage(bpAtc->GetDamage());
				blastMng_->On(bpAtc->GetObj().pos_);
				bpAtc->Off();
			}
		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:
		for (auto& weak : runboo_->GetWeakness())
		{
			int i = 0;
			//プレイヤーの通常攻撃と弱点の当たり判定
			if (ins.Circle(player_->DefaultAtt(), weak->GetUnit()))
			{
				weak->SetDamage(1.0f);
				bamboo_->Create(player_->GetUnit().pos_, 1, 30);
			}

			//プレイヤーと弱点の攻撃当たり判定
			for (auto& weakObj : weak->GetObj()) {
				if (ins.Rect(player_->DefaultAtt(), weakObj))
				{
					weak->ObjHit(i);
					bamboo_->Create(weakObj.pos_, 2, 80);
				}
				i++;
			}

			//プレイヤーの特殊攻撃と弱点の当たり判定
			for (auto& bpAtc : player_->GetBpAtt()) {
				if (ins.CircleAndRect(weak->GetUnit(), bpAtc->GetObj())) {
					if (bpAtc->GetPower() >= 4)mana.SHAKE();
					bpAtc->Off();
					mana.HitStop(SceneManager::HIT_STOP_TIME);
					weak->SetDamage(bpAtc->GetDamage());
				}
			}
		}

		//本体（壁）と通常攻撃の当たり判定
		if (ins.CircleAndRect(player_->DefaultAtt(), runboo_->GetUnit())) {
			bamboo_->Create(player_->GetUnit().pos_, 1);
			//弱点がすべて破壊されたら、本体にダメージが入る
			if (runboo_->GetWeakAllDeath()) {
				runboo_->SetDamage(5);
			}
		}
		break;
	case M::BOSS_KINDS::BAMMOON:
		if (ins.CircleAndRect(player_->DefaultAtt(), bammoon_->GetUnit())) {
			mana.HitStop(M::HIT_STOP_TIME);
			bammoon_->SetDamage(5);
			bamboo_->Create(bammoon_->GetUnit().pos_, 1, 30);
			if (bammoon_->GetAtState() == Bammoon::ATTACK::SWEEP) {
				bammoon_->SetDown(player_->GetUnit().pos_);
			}
		}
		for (auto& bpAtc : player_->GetBpAtt()) {
			if (ins.Ellipse(bpAtc->GetObj(), bammoon_->GetUnit())) {
				if (bpAtc->GetPower() >= 3) { mana.SHAKE(); }
				if (bpAtc->GetPower() >= 5) { mana.ZoomPos(bpAtc->GetObj().disppos_); mana.ZoomScale(2.0f); mana.HitStop(20); }
				SoundManager::GetIns().Play(SoundManager::SOUND::BPHIT, true, 200);
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
	using M = SceneManager;
	auto& mana = M::GetInstance().GetInstance();

	switch (mana.GetNowBoss())
	{
	case M::BOSS_KINDS::TUTORIAL:
		if (ins.Rect(player_->GetUnit(), tutorial_->GetUnit())) {
			player_->Hit(5, tutorial_->GetUnit().pos_);
		}
		break;
	case M::BOSS_KINDS::NOKOPY:
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
		if (ins.CircleAndRect(player_->GetUnit(), runboo_->GetUnit()))
		{
			player_->Hit(10, runboo_->GetUnit().pos_);
		}

		//プレイヤーと弱点の当たり判定
		for (auto& weak : runboo_->GetWeakness())
		{
			if (ins.Circle(player_->GetUnit(), weak->GetUnit()))
			{
				player_->Hit(5.0f, weak->GetUnit().pos_);
			}
		}
		break;
	case M::BOSS_KINDS::BAMMOON:
		if (ins.Ellipse(player_->GetUnit(), bammoon_->GetUnit())) {
			player_->Hit(2, bammoon_->GetUnit().pos_);
		}
		break;
	}

}

void BattledomeScene::PlayerToBossAttack(void)
{
	// プレイヤーとボスの攻撃の当たり判定処理  
	auto& ins = Collision::GetInstance();
	using M = SceneManager;
	auto& mana = M::GetInstance().GetInstance();
	switch (mana.GetNowBoss())
	{
	case M::BOSS_KINDS::TUTORIAL: {
		int i = 0;
		for (auto& at : tutorial_->GetAttackObj()) {
			if (ins.CircleAndRect(at, player_->GetUnit())) {
				player_->Hit(5, at.pos_);
				tutorial_->ObjHit(i);
			}
			i++;
		}
		break;
	}
	case M::BOSS_KINDS::NOKOPY:
		for (int i = 0; i < nokopy_->GetObj().size(); i++) {
			//if (nokopy_->GetObj()[i].isCapsule_) {
			//	if (ins.CircleAndCapsule(player_->GetUnit(), nokopy_->GetAttackIns()->Get()[i]))
			//	{
			//		player_->Hit(5, nokopy_->GetObj()[i].pos_);
			//		nokopy_->ObjHit(i);
			//	}
			//}
			if (nokopy_->GetObj()[i].isCircle_) {
				if (ins.CircleAndRect(nokopy_->GetObj()[i], player_->GetUnit())) {
					player_->Hit(5, nokopy_->GetObj()[i].pos_);
					nokopy_->ObjHit(i);
				}
			}
			else {

				if (ins.Rect(player_->GetUnit(), nokopy_->GetObj()[i])) {
					player_->Hit(5, nokopy_->GetObj()[i].pos_);
					nokopy_->ObjHit(i);
				}
			}
		}
		break;
	case SceneManager::BOSS_KINDS::RUNBOO:
	{
		for (auto& weak : runboo_->GetWeakness())
		{
			//プレイヤーと弱点の攻撃当たり判定
			for (auto& weakObj : weak->GetObj()) {
				if (ins.CircleAndRect(player_->GetUnit(), weakObj))
				{
					player_->Hit(5.0f, weakObj.pos_);
				}
			}

			for (auto& weakBull : weak->GetBulletObj())
			{
				if (ins.Circle(player_->GetUnit(), weakBull))
				{
					player_->Hit(5.0f, weakBull.pos_);
				}
			}
		}
	}
	break;
	case M::BOSS_KINDS::BAMMOON:
		int i = 0;
		for (auto& bAtc : bammoon_->GetObj()) {
			//switch (bammoon_->GetAtState())
			//{
			//case Bammoon::ATTACK::SWEEP:
			//case Bammoon::ATTACK::BLAST:
			//case Bammoon::ATTACK::PBULLET:
			//case Bammoon::ATTACK::CSPHERE:
				if (ins.CircleAndRect(bAtc, player_->GetUnit())) {
					player_->Hit(bammoon_->GetObjDamage(), bAtc.pos_);
					bammoon_->ObjHit(i);
				}
				for (auto& pAtc : player_->GetBpAtt()) {
					if (ins.CircleAndRect(bAtc, pAtc->GetObj())) {
						bammoon_->ObjHit(i);
						pAtc->Hit();
					}
				}
				//break;
			//case Bammoon::ATTACK::STRIPE:
				if (ins.Rect(bAtc, player_->GetUnit())) {
					player_->Hit(bammoon_->GetObjDamage(), bAtc.pos_);
					bammoon_->ObjHit(i);
				}

				for (auto& pAtc : player_->GetBpAtt()) {
					if (ins.Rect(bAtc, pAtc->GetObj())) {
						bammoon_->ObjHit(i);
						pAtc->Hit();
					}
				}
				//break;
			//}

			i++;
		}
		break;
	}
}

void BattledomeScene::PlayerToBamboo(void)
{
	if (player_->GetHaveB())return;

	auto& ins = Collision::GetInstance();
	using M = SceneManager;
	auto& mana = M::GetInstance().GetInstance();

	for (auto& b : bamboo_->GetBamboos()) {
		if (ins.CircleAndRect(b->GetUnit(), player_->GetUnit(), false)) {
			b->Collect();
			player_->BpOptain();
		}
	}


	for (auto& b : player_->GetBpAtt()) {
		if (ins.CircleAndRect(player_->DefaultAtt(), b->GetObj())) {
			mana.HitStop(M::HIT_STOP_TIME);
			b->Parry(player_->GetUnit().pos_);
		}
	}
}