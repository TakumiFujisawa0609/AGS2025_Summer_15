#include <chrono>
#include <DxLib.h>
#include "../Common/Fader.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/GameClear.h"
#include "../Scene/GameOverScene.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "SceneManager.h"
#include"../Application.h"

SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::GAME;
	waitSceneId_ = SCENE_ID::NONE;
	cntl_ = CNTL::NONE;

	fader_ = new Fader();
	fader_->Init();

	// カメラ
	Camera::CreateInstance();

	scene_ = new TitleScene();
	scene_->Init();

	isSceneChanging_ = false;


	//メイクスクリーン
	mainScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	// 3D用の設定
	Init3D();

	// 初期シーンの設定
	DoChangeScene(SCENE_ID::GAME);

}

void SceneManager::Init3D(void)
{

	// 背景色設定
	SetBackgroundColor(0, 0, 0);

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// ライトの設定
	SetUseLighting(true);

	// 正面から斜め下に向かったライト
	ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });

}

void SceneManager::Update(void)
{

	if (scene_ == nullptr)
	{
		return;
	}

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	fader_->Update();
	if (isSceneChanging_)
	{
		Fade();
	}
	else
	{
		//ヒットストップ-----------------
		if (hitStopCounter_ > 0) {
			hitStopCounter_--;
			return;
		}
		//スロー--------------------------
		if (slowCounter_ > 0) {
			slowCounter_--;
			if (slowCounter_ % 2 != 0) {
				return;
			}
		}
		//注視点を初期化-----------------
		zoomPos_ = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 2 };
		scale_ = 1.0f;
		//--------------------------------
		scene_->Update();
	}



}

void SceneManager::Draw(void)
{
	
	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(mainScreen_);

	// 画面を初期化
	ClearDrawScreen();

	// カメラ更新
	Camera::GetInstance().Set();

	// 描画
	scene_->Draw();

	// 暗転・明転
	fader_->Draw();

	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();


	Vector2F vPos,dPos;
	vPos = { zoomPos_.x - Application::SCREEN_SIZE_X / 2, zoomPos_.y - Application::SCREEN_SIZE_Y / 2 };
	dPos = { Application::SCREEN_SIZE_X / 2 - vPos.x,Application::SCREEN_SIZE_Y / 2 - vPos.y };

	if (shakeCounter_ > 0)shakeCounter_--;
	int shake = shakeCounter_ / 5 % 2;
	shake *= 2;
	shake -= 1;
	shake *= 5;

	DrawRotaGraph(dPos.x+shake, dPos.y-shake, scale_, 0, mainScreen_, true);

}

void SceneManager::Destroy(void)
{

	scene_->Release();

	DeleteGraph(mainScreen_);

	delete scene_;

	delete fader_;

	delete instance_;

}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// フェード処理が終わってからシーンを変える場合もあるため、
	// 遷移先シーンをメンバ変数に保持
	waitSceneId_ = nextId;

	// フェードアウト(暗転)を開始する
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
	return deltaTime_;
}

Camera& SceneManager::GetCamera(void) const
{
	return Camera::GetInstance();
}

const SceneManager::CNTL SceneManager::GetController(void) const
{
	return cntl_;
}

void SceneManager::SetController(const CNTL _cntl)
{
	cntl_ = _cntl;
}

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = nullptr;
	fader_ = nullptr;

	isSceneChanging_ = false;

	// デルタタイム
	deltaTime_ = 1.0f / 60.0f;

	
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{
	auto& resM = ResourceManager::GetInstance();

	// リソースの解放
	resM.Release();

	// シーンを変更する
	sceneId_ = sceneId;

	// 現在のシーンを解放
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = new TitleScene();
		resM.InitTitle();
		break;

	case SCENE_ID::GAME:
		scene_ = new GameScene();
		resM.InitGame();
		break;

	case SCENE_ID::CLEAR:
		scene_ = new GameClear();
		resM.InitClear();
		break;

	case SCENE_ID::GAMEOVER:
		scene_ = new GameOverScene();
		resM.InitGameOver();
		break;
	}

	scene_->Init();

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// 明転中
		if (fader_->IsEnd())
		{
			// 明転が終了したら、フェード処理終了
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// 暗転中
		if (fader_->IsEnd())
		{
			// 完全に暗転してからシーン遷移
			DoChangeScene(waitSceneId_);
			// 暗転から明転へ
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}

}


