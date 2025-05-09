#pragma once
#include"../Common/Base.h"

class Player
{
public:
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 96;
	static constexpr float RADIUS = 64.0f;

	static constexpr int HP_MAX = 100;

	static constexpr float MOVE_POW = 10.0f;		//移動量

	static constexpr float MAX_JUMP_POWER = -50.0f;	//最大ジャンプ力
	static constexpr int INPUT_JUMPKEY_FRAME = 6;	//ジャンプ入力受付フレーム数

	static constexpr float GRAVITY = 9.8f;			//重力

	Player();
	~Player();

	bool SystemInit();
	void GameInit();
	void Update();
	void Draw();
	bool Release();


	//ゲッター関数
	Base GetPlayer(void) { return player_; }
	
	//セッター関数
	void SetAliveOff(void) { player_.isAlive_ = false; }

private:
	//構造体
	Base player_;

	//動作
	void Move();

	//重力
	void Gravity(void);

	//重力
	float gravity_;

	//Y座標の変更
	void UpdatePositionY(void);

	//ジャンプ
	void Jump(void);

	//ジャンプ発動処理
	void ProcessJump(void);

	bool isJump_;		//true=ジャンプ中/false=非ジャンプ
	bool isJumpKey_;		//true=ジャンプキーが押されている/false=非ジャンプキーが押されている

	float jumpPower_;		//ジャンプパワー

	int inputJumpKeyCounter_;		//ジャンプの入力時間カウンター

	float verticalAcceleration_;			//縦方向の加速度

	void CollisionStage(void);
};



