#pragma once
#include"../Common/Base.h"
#include"../../Utility/AsoUtility.h"

class Player
{
public:
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 96;
	static constexpr float RADIUS = 64.0f;

	static constexpr int HP_MAX = 100;

	static constexpr float MOVE_POW = 10.0f;		//移動量

	static constexpr float MAX_JUMP_POWER = -12.0f;	//最大ジャンプ力
	static constexpr int INPUT_JUMPKEY_FRAME = 6;	//ジャンプ入力受付フレーム数

	static constexpr float GRAVITY = 0.98f;			//重力

	static constexpr float EVASION_LENGTH = 10.0f;		//回避距離
	static constexpr int EVASION_TIME = 10;				//回避時間
	static constexpr int EVASION_INVINCIBLE = 5;		//回避無敵時間
	static constexpr int EVASION_COOLDOWN = 60;		//回避クールタイム

	Player();
	~Player();

	bool SystemInit();
	void GameInit();
	void Update();
	void Draw();
	bool Release();


	//ゲッター関数
	Base GetPlayer(void) { return player_; }
	bool IsEvasion(void) { return isEvasion_; }
	bool IsInvincible(void) { return isEvasionInbincible_; }
	
	//セッター関数
	void SetAliveOff(void) { player_.isAlive_ = false; }

private:
	//構造体
	Base player_;

	//動作
	void Move(void);

	//回避
	void Evasion(void);

	//回避発動処理
	void ProcessEvasion(void);

	//重力
	void Gravity(void);

	//Y座標の変更
	void UpdatePositionY(void);

	//ジャンプ
	void Jump(void);

	//ジャンプ発動処理
	void ProcessJump(void);

	//ステージとの当たり判定
	void CollisionStage(void);		

	//重力
	float gravity_;

	bool isJump_;		//true=ジャンプ中/false=非ジャンプ
	bool firstJumpFlg_;			//一回目のジャンプ(true=ジャンプ可能/false=ジャンプしたかったなぁ)
	bool secondJumpFlg_;		//二段ジャンプ(true=ジャンプ可能/false=ジャンプしたかったなぁ)
	bool thirdJumpFlg_;
	float jumpPower_;		//ジャンプパワー
	float verticalAcceleration_;			//縦方向の加速度
	int inputJumpKeyCounter_;		//ジャンプの入力時間カウンター

	//int playerDir_		;//プレイヤーが向いている方向
	AsoUtility::DIRECTION playerDir_;

	int evasionCounter_;		//回避時間カウンター
	int evasionCoolDown_;		//回避クールダウンカウンター
	bool isEvasion_;			//回避フラグ(true=回避中/false=非回避中)
	bool isEvasionCoolDown_;	//回避クールダウンフラグ(true=クールダウン中/false=非クールダウン中)
	bool isEvasionInbincible_;	//回避時無敵フラグ(true=無敵/false=無敵じゃないよ)
};



