#pragma once
#include <string>
#include"Object/Stage/Tutorial/TutorialStage.h"

#include"Common/Vector2.h"

class Application
{

public:

	// スクリーンサイズ
	static constexpr int SCREEN_SIZE_X = 1280;
	static constexpr int SCREEN_SIZE_Y =  720;

	static constexpr int MAIN_SCREEN_SIZE_X = (int)(SCREEN_SIZE_X * 1.5f);
	static constexpr int MAIN_SCREEN_SIZE_Y = TutorialStage::STAGE_CHIP_SIZE* TutorialStage::STAGE_NUM_Y;

	static const Vector2 SCREEN_ZERO_POINT;

	// データパス関連
	//-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;
	static const std::string PATH_PLAYER;
	//-------------------------------------------

	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static Application& GetInstance(void);

	// 初期化
	void Init(void);

	// ゲームループの開始
	void Run(void);

	// リソースの破棄
	void Destroy(void);

	// 初期化成功／失敗の判定
	bool IsInitFail(void) const;

	// 解放成功／失敗の判定
	bool IsReleaseFail(void) const;

private:

	// 静的インスタンス
	static Application* instance_;

	// 初期化失敗
	bool isInitFail_;

	// 解放失敗
	bool isReleaseFail_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	Application(void);

	// コピーコンストラクタも同様
	Application(const Application&);

	// デストラクタも同様
	~Application(void) = default;
	//えふぇくしあの初期化
	void InitEffekseer(void);
};