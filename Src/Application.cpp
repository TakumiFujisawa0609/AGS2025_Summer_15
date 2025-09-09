#include <DxLib.h>
#include<EffekseerForDXLib.h>

#include "Manager/InputManager.h"
#include"Manager/KeyManager.h"
#include "Manager/SceneManager.h"
#include"Manager/FPS/FPS.h"
#include"Manager/Score/Score.h"
#include "Application.h"
#include"Manager/Decoration/EffectManager.h"

#include"Manager/SoundManager.h"

Application* Application::instance_ = nullptr;

const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_EFFECT = "Data/Effect/";
const std::string Application::PATH_PLAYER = "Data/Image/Player/";

Application::Application(void):
	gameEnd_(false)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
}

void Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::Init(void)
{

	// アプリケーションの初期設定
	SetWindowText("THE BAMBOOOOO");

	// ウィンドウサイズ
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(false);

	// DxLibの初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}
	InitEffekseer();

	// キー制御初期化
	SetUseDirectInputFlag(true);
	KEY::CreateIns();
	InputManager::CreateInstance();

	// リソース管理初期化
	EffectManager::CreateInstance();

	// シーン管理初期化
	SceneManager::CreateIns();

	// FPS初期化
	fps_ = new FPS;
	fps_->Init();

	// サウンド初期化
	SoundManager::CreateIns();

	Score::CreateInstance();

	gameEnd_ = false;
}

void Application::Run(void)
{

	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetIns();
	// ゲームループ
	while (ProcessMessage() == 0 && !gameEnd_)
	{
		if (!fps_->UpdateFrameRate()) continue;

		inputManager.Update();
		KEY::GetIns().Update();
		sceneManager.Update();
		fps_->CalcFrameRate();	// フレームレート計算

		sceneManager.Draw();

		ScreenFlip();
	}

}

void Application::Destroy(void)
{
	Score::DeleteIns();
	SoundManager::DeleteIns();

	KEY::DeleteIns();
	InputManager::GetInstance().Destroy();
	SceneManager::DeleteIns();
	
	Effkseer_End();

	// DxLib終了
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}

	delete instance_;

}

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}



void Application::InitEffekseer(void)
{
	if (Effekseer_Init(8000) == -1) {
		DxLib_End();
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	Effekseer_Set2DSetting(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}
