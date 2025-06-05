#pragma once
#include"../Common/Base.h"
#include"../../Utility/AsoUtility.h"
#include"../UnitBase.h"

class ArialSweep;

class Player:public UnitBase
{
public:

	static constexpr int LOAD_SIZE_X = 120;		//画像サイズ
	static constexpr int LOAD_SIZE_Y = 80;		//画像サイズ

	static constexpr float SIZE_SCALE = 2.3f;

	static constexpr int SIZE_X = 13 * SIZE_SCALE;
	static constexpr int SIZE_Y = 40 * SIZE_SCALE;


	static constexpr int IDLE_LOAD_NUM = 10;
	static constexpr int RUN_LOAD_NUM = 10;
	static constexpr int JUMP_LOAD_NUM = 3;
	static constexpr int FALL_LOAD_NUM = 3;
	static constexpr int EVASION_LOAD_NUM = 12;



	static constexpr float RADIUS = 64.0f;

	static constexpr int HP_MAX = 100;

	static constexpr float MOVE_POW = 10.0f;		//移動量

	static constexpr float MAX_JUMP_POWER = -12.0f;	//最大ジャンプ力
	static constexpr int INPUT_JUMPKEY_FRAME = 6;	//ジャンプ入力受付フレーム数

	static constexpr float GRAVITY = 0.98f;			//重力
	static constexpr float MAX_GRAVITY = 20.0f;

	static constexpr float EVASION_LENGTH = 10.0f;		//回避距離
	static constexpr int EVASION_TIME = 10;				//回避時間
	static constexpr int EVASION_INVINCIBLE = 5;		//回避無敵時間
	static constexpr int EVASION_COOLDOWN = 18;		//回避クールタイム

	static constexpr int ATTACK_TIME = 60;			//攻撃時間
	static constexpr int ATTACK_COOLDOWN = 60;

	static constexpr int MAX_ANIM_NUM = 10;		//最大アニメーションパターン
	static constexpr float ANIM_SPEED = 0.1f;	//アニメーションスピード

	static constexpr int GUARD_TIME_MAX = 180;		//最大ガード時間
	static constexpr int GUARD_PER_TIME = 10;		//前硬直時間
	static constexpr int GUARD_POST_TIME = 10;		//後硬直時間
	static constexpr int GUARD_JUST_TIME = 9;		//ジャストガード猶予時間
	static constexpr int JUST_GUARD_INVINCIBLE = 60;	//ジャストガード成功時無敵時間

	static constexpr int HIT_COOL_DOWN = 60;	//被ダメージ時無敵時間
	static constexpr float KNOCKBACK_Y_ACCEL = -2.0f;

	//モーションタイプ
	enum class MOTION_TYPE
	{
		E_MOTION_IDLE,		//待機モーション
		E_MOTION_RUN,		//走りモーション
		E_MOTION_JUMP,		//ジャンプモーション
		E_MOTION_FALL,
		E_MOTION_DAMAGE,	//被ダメージモーション
		E_MOTION_EVASION,	//回避モーション

		E_MOTION_MAX,		//モーション最大数
	};

	//攻撃ステータス
	enum class ATTACK_STAT
	{
		E_ATTACK_STAT_NON,	//通常
		E_ATTACK_STAT_ARIALSWEEP,

		E_ATTACK_STAT_MAX,
	};

	enum class GUARD_STAT
	{
		E_GUARD_NON,		//非ガード状態
		E_GUARD_PER,		//前硬直
		E_GUARD,			//ガード
		E_GUARD_POST,		//後硬直
		E_GUARD_JUST,		//ジャストガード

		E_GUARD_MAX,
	};

	Player();
	~Player();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;


	//ゲッター関数
	bool IsEvasion(void) { return isEvasion_; }
	bool IsInvincible(void) { return isEvasionInbincible_; }
	bool IsJustGuard(void) { return isJustGuard_; }
	bool IsHit(void) { return unit_.isHit_; }
	bool IsGuard(void) { return isGuard_; }
	bool IsJustGuardInbincible(void) { return isJustGuardInbincible_; }

	//セッター関数
	void SetAliveOff(void) { unit_.isAlive_ = false; }
	void SetHitOn(void) { unit_.isHit_ = true; }
	void SetXAccel(float xAccel) { unit_.xAccel_ = xAccel; }
	void SetSuccessJustGuard(void) { isSuccessJustGuard_ = true; }

private:
	//プレイヤー描画関係--------------------------------------------------
	std::vector<int> image_[(int)MOTION_TYPE::E_MOTION_MAX];

	float animCounter_;			//アニメーションカウンター

	
	MOTION_TYPE motionType_;	//モーションタイプ

	//関数達
	void LoadPlayerImage(void);		//プレイヤー画像の読み込み処理
	void DrawPlayer(std::vector<int> modelId,bool loop=true);		//プレイヤーの描画
	void SetDrawPlayer(void);		//描画するプレイヤーの設定

	//--------------------------------------------------------------------

	//移動処理--------------------------------------------------------------
	void Move(void);	
	//int playerDir_;			//プレイヤーが向いている方向
	AsoUtility::DIRECTION playerDir_;
	bool isMove_;				//移動処理用

	// 接地している時の数値の代入などをまとめた関数
	void IsGround(Collision::DIR dir)override;

	//ジャンプ-------------------------------------------------------------------------------------
	//ジャンプ発動処理
	void ProcessJump(void);
	//ジャンプ更新処理
	void Jump(void);
	bool isJump_;				//true=ジャンプ中/false=非ジャンプ
	bool firstJumpFlg_;			//一回目のジャンプ(true=ジャンプ可能/false=ジャンプしたかったなぁ)
	bool secondJumpFlg_;		//二段ジャンプ(true=ジャンプ可能/false=ジャンプしたかったなぁ)
	bool thirdJumpFlg_;
	float jumpPower_;			//ジャンプパワー
	float yAccel_;//縦方向の加速度
	int inputJumpKeyCounter_;	//ジャンプの入力時間カウンター

	//攻撃---------------------------------------------------------------
	//攻撃プロセス
	void ProcessAtatck(void);
	//攻撃更新処理
	void Attack(void);
	//特殊攻撃
	void ArialSweepAttack(void);
	bool isAttack_;
	bool isAttackCoolDown_;
	int attackCounter_;			//攻撃時間
	int attackCoolDown_;		//攻撃クールタイム
	int arialSweepCounter_;			
	//プレイヤー攻撃時のマウスの座標
	Vector2 mPos_;
	Vector2F mapMousePos_;
	//攻撃モーション
	ATTACK_STAT attackStat_;
	ArialSweep* arialSweep_;

	//回避---------------------------------------------------------------------------------------------------
	//回避発動処理
	void ProcessEvasion(void);
	//回避更新処理
	void Evasion(void);
	int evasionCounter_;		//回避時間カウンター
	int evasionCoolDown_;		//回避クールダウンカウンター
	bool isEvasion_;			//回避フラグ(true=回避中/false=非回避中)
	bool isEvasionCoolDown_;	//回避クールダウンフラグ(true=クールダウン中/false=非クールダウン中)
	bool isEvasionInbincible_;	//回避時無敵フラグ(true=無敵/false=無敵じゃないよ)
	AsoUtility::DIRECTION workDir_;	//一時退避用




	//ガード---------------------------------------------
	//ガード発動処理
	void ProcessGuard(void);
	//ガード更新処理
	void Guard(void);
	//ジャストガード更新処理
	void JustGuard(void);
	bool isGuard_;			//ガード中
	int guardMaxCounter_;	//最大ガード時間
	int perStiffness_;		//前硬直カウンター
	int postStiffness_;		//後硬直カウンター
	bool perGuardKey_;		//トリガーアップ用変数
	bool nowGuardKey_;		//トリガーアップ用変数
	int guardKeyUpBuffer_;	//後入力受付猶予カウンター
	GUARD_STAT guardStat_;	
	bool isJustGuard_;		//ジャストガード中
	bool isSuccessJustGuard_;	//ジャストガード成功
	bool isJustGuardInbincible_;	//ジャストガード成功時無敵
	int justGuardCounter_;		//ジャストガード成功時用カウンター


	//-----------------------------------------------------
	//ダメージ
	//-----------------------------------------------------
	//ダメージ処理
	void ProcessDamage(void);
	//HIT処理
	void ProcessHit(void);
	//ノックバック処理
	void ProcessKnockback(void);
	//無敵処理
	void HitCoolDown(void);
	int hitCoolDownCounter_;	//無敵時間用カウンター
	float knockBackYAccel_;		//ノックバック用Y軸方向加速度
};



