#pragma once
#include<DxLib.h>
#include <chrono>
#include"../Common/Vector2.h"
#include"../Application.h"

class SceneBase;
class Fader;
class Pause;

class SceneManager
{

public:

	static constexpr float STICK_START_POW = 0.5f;
	static constexpr int HIT_STOP_TIME = 5;


	// シーン管理用
	enum class SCENE_ID
	{
		NONE = -1,
		TITLE,
		MODESELECT,
		TUTORIAL,
		BOSSSELECT,
		BATTLEDONE,
		GAMEOVER,
		CLEAR,
	};



	enum class CNTL
	{
		NONE,
		KEY,
		PAD,
	};
	
	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SceneManager& GetInstance(void);

	void Init(void);
	void Init3D(void);
	void Update(void);
	void Draw(void);

	// リソースの破棄
	void Destroy(void);

	// 状態遷移
	void ChangeScene(SCENE_ID nextId);

	// シーンIDの取得
	SCENE_ID GetSceneID(void);

	// デルタタイムの取得
	float GetDeltaTime(void) const;

	//操作種別の取得・設定
	const CNTL GetController(void)const;
	void SetController(const CNTL _cntl);


	void Slow(void) { if (slowCounter_ >= 0) { slowCounter_ = SLOW_TIME; } }
	void HitStop(int stopTime) { hitStopCounter_ = stopTime; }
	void SHAKE(void) { shakeCounter_ = SHAKE_TIME; }

	void ZoomPos(Vector2F pos) { zoomPos_ = pos; }
	void ZoomScale(float scale) { scale_ = scale; }

	bool GetExit(void);

	void SetMapNum(Vector2 num) { mapNum_ = num; }


	//ボスの種類
	enum class BOSS_KINDS
	{
		ONE,
		TWO,
		BAMMOON,
	};

	const BOSS_KINDS GetNowBoss(void)const { return nowBossKinds_; }
	void SetBossKinds(BOSS_KINDS k) { nowBossKinds_ = k; }

private:

	// 静的インスタンス
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;
	CNTL cntl_;

	// フェード
	Fader* fader_;

	//ポーズ画面
	Pause* pause_;

	// 各種シーン
	SceneBase* scene_;

	// シーン遷移中判定
	bool isSceneChanging_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// コピーコンストラクタも同様
	SceneManager(const SceneManager&);
	// デストラクタも同様
	~SceneManager(void) = default;

	// デルタタイムをリセットする
	void ResetDeltaTime(void);

	// シーン遷移
	void DoChangeScene(SCENE_ID sceneId);

	// フェード
	void Fade(void);


	int mainScreen_;

	const int SLOW_TIME = 40;
	int slowCounter_;

	int hitStopCounter_;

	const int SHAKE_TIME = 30;
	int shakeCounter_ = 0;

	Vector2F zoomPos_;
	float scale_ = 1.0f;

	void ZoomCtr(void);

	Vector2 mapNum_;


	BOSS_KINDS nowBossKinds_;
};