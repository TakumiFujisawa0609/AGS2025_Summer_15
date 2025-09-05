#include "SceneManager.h"
#include <chrono>
#include<EffekseerForDXLib.h>

#include "../Common/Fader.h"
#include "Camera.h"

#include"Loading/Loading.h"

#include"../Manager/SoundManager.h"

#include "../Scene/Title/TitleScene.h"
#include"../Scene/Tutorial/TutorialScene.h"
#include"../Scene/BossSelect.h"
#include"../Scene/Game/BattledomeScene.h"
#include "../Scene/GameClear.h"
#include "../Scene/GameOverScene.h"

SceneManager* SceneManager::ins_ = nullptr;


SceneManager::SceneManager(void):

	sceneId_(SCENE_ID::NONE),
	deltaTime_(1.0f/60)
{
}



void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;

	// ロード画面生成
	Loading::GetInstance()->CreateInstance();
	Loading::GetInstance()->Init();
	Loading::GetInstance()->Load();

	SoundManager::GetIns().Load(SoundManager::HIBIODOSI);
	SoundManager::GetIns().Load(SoundManager::SISIODOSI);
	SoundManager::GetIns().Load(SoundManager::BPHIT);

	// カメラ
	Camera::CreateInstance();
	Camera::GetInstance().Init();

	//メイクスクリーン
	mainScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	//注視点を初期化-----------------
	zoomPos_ = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 2 };
	scale_ = 1.0f;
	//--------------------------------


	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	ChangeScene(SCENE_ID::TITLE);
}


void SceneManager::Update(void)
{
	// シーンがなければ終了
	if (scenes_.empty()) { return; }

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;


	// ロード中
	if (Loading::GetInstance()->IsLoading())
	{
		// ロード更新
		Loading::GetInstance()->Update();

		// ロードの更新が終了していたら
		if (Loading::GetInstance()->IsLoading() == false)
		{
			// ロード後の初期化
			scenes_.back()->Init();
		}
	}
	// 通常の更新処理
	else
	{
		//ヒットストップ-----------------
		if (hitStopCounter_ > 0) { hitStopCounter_--; return; }
		//スロー--------------------------
		if (slowCounter_ > 0) {
			slowCounter_--;
			if (slowCounter_ % 5 != 0) { return; }
		}
		//注視点を初期化-----------------
		zoomPos_ = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 2 };
		scale_ = 1.0f;
		//--------------------------------
		
		// 現在のシーンの更新
		scenes_.back()->Update();
	}

}

void SceneManager::Draw(void)
{
	// 描画先グラフィック領域の指定
	SetDrawScreen(mainScreen_);

	// 画面を初期化
	ClearDrawScreen();

	UpdateEffekseer2D();

	// 描画
	// ロード中ならロード画面を描画
	if (Loading::GetInstance()->IsLoading())
	{
		// ロードの描画
		Loading::GetInstance()->Draw();
	}
	// 通常の更新
	else
	{
		// 積まれているもの全てを描画する
		for (auto& scene : scenes_)
		{
			scene->Draw();
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	ZoomCtr();
	Vector2F vPos,dPos;
	vPos = { zoomPos_.x - Application::SCREEN_SIZE_X / 2, zoomPos_.y - Application::SCREEN_SIZE_Y / 2 };
	dPos = { Application::SCREEN_SIZE_X / 2 - vPos.x,Application::SCREEN_SIZE_Y / 2 - vPos.y };

	Vector2 s = ShakePoint();

	DrawRotaGraph(dPos.x + s.x, dPos.y + s.y, scale_, 0, mainScreen_, true);
}

void SceneManager::Destroy(void)
{
	//全てのシーンの解放・削除
	for (auto& scene : scenes_) { scene->Release(); }
	scenes_.clear();

	SoundManager::GetIns().Delete(SoundManager::SOUND::SISIODOSI);
	SoundManager::GetIns().Delete(SoundManager::SOUND::HIBIODOSI);
	SoundManager::GetIns().Delete(SoundManager::SOUND::BPHIT);
	DeleteGraph(mainScreen_);

	// ロード画面の削除
	Loading::GetInstance()->Release();
	Loading::GetInstance()->DeleteInstance();
	
	Camera::DeleteInstance();
}


// 状態遷移関数
void SceneManager::ChangeScene(std::shared_ptr<SceneBase>scene)
{
	// シーンが空か？
	if (scenes_.empty())
	{
		//空なので新しく入れる
		scenes_.push_back(scene);
	}
	else
	{
		//末尾のものを新しい物に入れ替える
 		scenes_.back()->Release();
		scenes_.back() = scene;
	}

	// 読み込み(非同期)
	Loading::GetInstance()->StartAsyncLoad();
	scenes_.back()->Load();
	Loading::GetInstance()->EndAsyncLoad();
}

void SceneManager::ChangeScene(SCENE_ID scene)
{
	switch (scene)
	{
	case SCENE_ID::TITLE:
		ChangeScene(std::make_shared<TitleScene>());
		break;
	case SCENE_ID::TUTORIAL:
		ChangeScene(std::make_shared<TutorialScene>());
		break;
	case SCENE_ID::BOSSSELECT:
		ChangeScene(std::make_shared< BossSelect>());
		break;
	case SCENE_ID::BATTLEDONE:
		ChangeScene(std::make_shared<BattledomeScene>());
		break;
	case SCENE_ID::CLEAR:
		ChangeScene(std::make_shared<GameClear>());
		break;
	case SCENE_ID::GAMEOVER:
		ChangeScene(std::make_shared<GameOverScene>());
		break;
	default:
		break;
	}
}

void SceneManager::PushScene(std::shared_ptr<SceneBase> scene)
{
	//新しく積むのでもともと入っている奴はまだ削除されない
	scenes_.push_back(scene);
	scenes_.back()->Load();
	scenes_.back()->Init();
}

void SceneManager::PushScene(SCENE_ID scene)
{
	switch (scene)
	{
	case SCENE_ID::TITLE:
		PushScene(std::make_shared<TitleScene>());
		break;
	case SCENE_ID::TUTORIAL:
		PushScene(std::make_shared<TutorialScene>());
		break;
	case SCENE_ID::BOSSSELECT:
		PushScene(std::make_shared< BossSelect>());
		break;
	case SCENE_ID::BATTLEDONE:
		PushScene(std::make_shared<BattledomeScene>());
		break;
	case SCENE_ID::CLEAR:
		PushScene(std::make_shared<GameClear>());
		break;
	case SCENE_ID::GAMEOVER:
		PushScene(std::make_shared<GameOverScene>());
		break;
	default:
		break;
	}
}

void SceneManager::PopScene(void)
{
	//積んであるものを消して、もともとあったものを末尾にする
	if (scenes_.size() > 1)
	{
		scenes_.back()->Release();
		scenes_.pop_back();
	}
}

void SceneManager::JumpScene(std::shared_ptr<SceneBase> scene)
{
	// 全て解放
	for (auto& scene : scenes_) { scene->Release(); }
	scenes_.clear();

	// 新しく積む
	ChangeScene(scene);
}

void SceneManager::JumpScene(SCENE_ID scene)
{
	switch (scene)
	{
	case SCENE_ID::TITLE:
		JumpScene(std::make_shared<TitleScene>());
		break;
	case SCENE_ID::TUTORIAL:
		JumpScene(std::make_shared<TutorialScene>());
		break;
	case SCENE_ID::BOSSSELECT:
		JumpScene(std::make_shared< BossSelect>());
		break;
	case SCENE_ID::BATTLEDONE:
		JumpScene(std::make_shared<BattledomeScene>());
		break;
	case SCENE_ID::CLEAR:
		JumpScene(std::make_shared<GameClear>());
		break;
	case SCENE_ID::GAMEOVER:
		JumpScene(std::make_shared<GameOverScene>());
		break;
	default:
		break;
	}
}




bool SceneManager::ThatsNotRight(int classId,int i)
{
	perValues[classId] = nowValues[classId];
	nowValues[classId] = i;
	return perValues[classId] != nowValues[classId];
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}


void SceneManager::Shake(ShakeKinds kinds, ShakeSize size, int time)
{
	if ((abs(shake_ - time) > 10) || shake_ <= 0)shake_ = time;
	shakeKinds_ = kinds;
	shakeSize_ = size;
}

Vector2 SceneManager::ShakePoint(void)
{
	Vector2 ret = {};

	if (shake_ > 0) {
		int size = shake_ / 5 % 2;
		size *= 2;
		size -= 1;
		switch (shakeKinds_)
		{
		case SceneManager::WID:ret.x = size;
			break;
		case SceneManager::HIG:ret.y = size;
			break;
		case SceneManager::DIAG:ret = size;
			break;
		case SceneManager::ROUND:
			size = shake_ / 3 % 12; size++;
			ret = { (int)((shakeSize_ * 1.5f) * cos(size * 30.0f)),(int)((shakeSize_ * 1.5f) * sin(size * 30.0f)) };
			break;
		}

		if (shakeKinds_ != ShakeKinds::ROUND) { ret *= shakeSize_; }

		DrawGraph(0, 0, mainScreen_, true);

		shake_--;
	}

	return ret;
}


void SceneManager::ZoomCtr(void)
{
	bool on = true;
	if (sceneId_ == SCENE_ID::BATTLEDONE)on = false;
	if (on)return;

	auto& camera = Camera::GetInstance();

	Vector2F worldZoomPos = zoomPos_ + camera.GetPos();

	Vector2F drawRange = { (Application::SCREEN_SIZE_X / scale_) / 2,(Application::SCREEN_SIZE_Y / scale_) / 2 };

	drawRange.x -= 75.0f;
	if (worldZoomPos.x - drawRange.x < 0) {
		zoomPos_.x -= (worldZoomPos.x - drawRange.x);
	}

	if (worldZoomPos.x + drawRange.x >= StageBase::STAGE_CHIP_SIZE * mapNum_.x) {
		zoomPos_.x -= ((worldZoomPos.x + drawRange.x) - (StageBase::STAGE_CHIP_SIZE * mapNum_.x));
	}

	float zure = 45.0f;
	drawRange.y -= zure;
	if (worldZoomPos.y - drawRange.y < 0) {
		zoomPos_.y -= (worldZoomPos.y - drawRange.y);
	}
	drawRange.y += zure;

	if (worldZoomPos.y + drawRange.y >= StageBase::STAGE_CHIP_SIZE * mapNum_.y) {
		zoomPos_.y -= ((worldZoomPos.y + drawRange.y) - (StageBase::STAGE_CHIP_SIZE * mapNum_.y));
	}
}