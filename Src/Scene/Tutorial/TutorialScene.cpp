#include"TutorialScene.h"

#include<DxLib.h>

#include"../../Manager/SceneManager.h"
#include"../../Manager/Collision.h"
#include"../../Manager/KeyManager.h"

#include"../../Manager/Decoration/BlastEffect/BlastEffectManager.h"

#include"Object/TutorialPlayer/TutorialPlayer.h"
#include"Object/TutorialMaster/TutorialMaster.h"
#include"../../Object/Stage/Tutorial/TutorialStage.h"
#include"../../Object/Bamboo/BambooManager.h"

#include"Object/TutorialTask/TutorialTaskManager.h"

#include"../Event/TitleJump/TitleJump.h"

TutorialScene::TutorialScene():
	player_(nullptr),
	master_(nullptr),
	stage_(nullptr),
	blastEffect_(nullptr),
	task_(nullptr),
	bamboo_(nullptr)
{
}

TutorialScene::~TutorialScene() {}

void TutorialScene::Load(void)
{
	Collision::CreateInstance();

	task_ = new TutorialTaskManager();
	task_->Load();

	player_ = new TutorialPlayer();
	player_->Init();

	master_ = new TutorialMaster(task_->GetNowTask(), task_->GetTaskConp());
	master_->Load();

	stage_ = new TutorialStage();
	stage_->Init();
	Collision::GetInstance().SetStage(stage_->GetMapData());

	blastEffect_ = new BlastEffectManager();
	blastEffect_->Init();

	bamboo_ = new BambooManager();
	bamboo_->Init();
}

void TutorialScene::Init(void)
{
	master_->Init();
	task_->Init();

}

void TutorialScene::Update(void)
{
	player_->Update();
	master_->Update();

	if (task_->Update()) { return; }

	Collision();

	blastEffect_->Update();
	bamboo_->Update();

	if (KeyManager::GetIns().GetInfo(KEY_TYPE::PAUSE).down) {
		SceneManager::GetIns().PushScene(std::make_shared<TitleJump>());
		return;
	}
}

void TutorialScene::Draw(void)
{
	stage_->BackDraw();

	master_->Draw();

	task_->Draw();

	bamboo_->Draw();

	stage_->Draw();

	player_->Draw();

	task_->DrawUI();

	blastEffect_->Draw();

}

void TutorialScene::Release(void)
{
	if (player_) {
		player_->Release();
		delete player_;
		player_ = nullptr;
	}

	if (master_) {
		master_->Release();
		delete master_;
		master_ = nullptr;
	}

	if (stage_) {
		stage_->Release();
		delete stage_;
		stage_ = nullptr;
	}

	if (blastEffect_) {
		blastEffect_->Release();
		delete blastEffect_;
		blastEffect_ = nullptr;
	}

	if (bamboo_) {
		bamboo_->Release();
		delete bamboo_;
		bamboo_ = nullptr;
	}

	if (task_) {
		task_->Release();
		delete task_;
		task_ = nullptr;
	}

	Collision::DeleteInstance();
}



void TutorialScene::Collision(void)
{
	auto& colli = Collision::GetInstance();
	auto& sMng = SceneManager::GetIns();

	bool bpParry = false;

	if (!player_->GetHaveB()) {
		for (auto& b : bamboo_->GetBamboos()) {
			if (Collision::GetInstance().CircleAndRect(player_->GetUnit(), b->GetUnit(), false)) {
				player_->BpOptain();
				b->Collect();
				break;
			}
		}

		for (auto& b : player_->GetBpAtt()) {
			if (Collision::GetInstance().Circle(player_->DefaultAtt(), b->GetObj())) {
				b->Parry(player_->GetUnit().pos_);
				SceneManager::GetIns().HitStop();
				bpParry = true;
			}
		}
	}

	switch (task_->GetNowTask())
	{
	case TutorialTaskManager::TASK::TASK1:
		for (auto& obj : task_->GetTask()->GetTutorialObject()) {
			if (colli.CircleAndRect(player_->DefaultAtt(), obj->GetUnit())) {

				obj->Action();
				if (!obj->GetUnit().isAlive_) { blastEffect_->On(obj->GetUnit().pos_); }

				bamboo_->Create(obj->GetUnit().pos_, 1);

				sMng.HitStop();
			}
			for (auto& bp : player_->GetBpAtt()) {
				if (colli.CircleAndRect(bp->GetObj(), obj->GetUnit())) {

					blastEffect_->On(bp->GetObj().pos_);

					bp->Off();

					sMng.HitStop();
				}
			}
		}
		break;
	case TutorialTaskManager::TASK::TASK2:
		if (colli.CircleAndRect(player_->DefaultAtt(), master_->GetAttack())) {
			sMng.HitStop();

			master_->AttackHit();
			task_->GetTask()->PowerEnd();
		}
		else if (colli.Rect(player_->GetUnit(), master_->GetAttack())) {
			sMng.HitStop();

			player_->Hit(0, master_->GetAttack().pos_);
			master_->AttackHit();
		}

		break;
	case TutorialTaskManager::TASK::TASK3:
		for (auto& obj : task_->GetTask()->GetTutorialObject()) {
			if (dynamic_cast<Mato*>(obj)) {
				for (auto& bp : player_->GetBpAtt()) {
					if (colli.Circle(bp->GetObj(), obj->GetUnit())) {

						obj->Action();

						bp->Off();

						blastEffect_->On(obj->GetUnit().pos_);

						sMng.HitStop();
					}
				}
			}
			if (dynamic_cast<Kakashi3*>(obj)) {
				if (colli.CircleAndRect(player_->DefaultAtt(), obj->GetUnit())) {

					obj->Action();
					if (!obj->GetUnit().isAlive_) { blastEffect_->On(obj->GetUnit().pos_); }

					bamboo_->Create(obj->GetUnit().pos_, 1);

					sMng.HitStop();
				}
			}
		}
		break;
	case TutorialTaskManager::TASK::TASK4:
		for (auto& obj : task_->GetTask()->GetTutorialObject()) {
			if (colli.CircleAndRect(player_->DefaultAtt(), obj->GetUnit())) {

				obj->Action();
				if (!obj->GetUnit().isAlive_) { blastEffect_->On(obj->GetUnit().pos_); }

				bamboo_->Create(obj->GetUnit().pos_, 1);

				sMng.HitStop();
			}
		}
		if (bpParry) { task_->GetTask()->PowerEnd(); }
		break;
	case TutorialTaskManager::TASK::TASK5:
		if (colli.Rect(player_->GetUnit(), master_->GetAttack())) {
			if (player_->GetState() == TutorialPlayer::STATE::EVASION) {
				sMng.HitStop();

				master_->AttackHit();
				task_->GetTask()->PowerEnd();
			}
			else {
				sMng.HitStop();

				player_->Hit(0, master_->GetAttack().pos_);
				master_->AttackHit();
			}
		}
		if (colli.CircleAndRect(player_->DefaultAtt(), master_->GetAttack())) {
			sMng.HitStop();
			master_->AttackHit();
		}
		break;
	default:break;
	}


}