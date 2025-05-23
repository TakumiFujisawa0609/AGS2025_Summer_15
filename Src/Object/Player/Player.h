#pragma once
#include"../Common/Base.h"
#include"../../Utility/AsoUtility.h"

class Stage;

class Player
{
public:
	static constexpr int SIZE_X = 96;		//画像サイズ
	static constexpr int SIZE_Y = 96;	//画像サイズ
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
	static constexpr int EVASION_COOLDOWN = 60;		//回避クールタイム

	static constexpr int ATTACK_TIME = 60;			//攻撃時間
	static constexpr int ATTACK_COOLDOWN = 60;

	static constexpr int MAX_ANIM_NUM = 10;		//最大アニメーションパターン
	static constexpr float ANIM_SPEED = 0.1f;	//アニメーションスピード

	//モーションタイプ
	enum class MOTION_TYPE
	{
		E_MOTION_IDLE,		//待機モーション
		E_MOTION_RUN,		//走りモーション
		E_MOTION_JUMP,		//ジャンプモーション
		E_MOTION_DAMAGE,	//被ダメージモーション
		E_MOTION_EVASION,	//回避モーション

		E_MOTION_MAX,		//モーション最大数
	};

	//攻撃ステータス
	enum class ATTACK_STAT
	{
		E_ATTACK_STAT_NON,	//通常
		E_ATTACK_STAT_KATTO,
		E_ATTACK_STAT_NUGRU,

		E_ATTACK_STAT_MAX,
	};




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

	//プレイヤー画像のハンドル番号
	int img[static_cast<int>(MOTION_TYPE::E_MOTION_MAX)][15];
	


	//モーションタイプ
	MOTION_TYPE motionType_;

	//攻撃モーション
	ATTACK_STAT attackStat_;


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
	void CollisionStageY(void);
	void CollisionStageX(void);

	//攻撃
	void Attack(void);

	//攻撃プロセス
	void ProcessAtatck(void);

	//重力
	float gravity_;

	bool isJump_;				//true=ジャンプ中/false=非ジャンプ
	bool firstJumpFlg_;			//一回目のジャンプ(true=ジャンプ可能/false=ジャンプしたかったなぁ)
	bool secondJumpFlg_;		//二段ジャンプ(true=ジャンプ可能/false=ジャンプしたかったなぁ)
	bool thirdJumpFlg_;
	float jumpPower_;			//ジャンプパワー
	float verticalAcceleration_;//縦方向の加速度
	int inputJumpKeyCounter_;	//ジャンプの入力時間カウンター

	//int playerDir_;			//プレイヤーが向いている方向
	AsoUtility::DIRECTION playerDir_;

	//攻撃
	bool isAttack_;
	bool isAttackCoolDown_;
	int attackCounter_;			//攻撃時間
	int attackCoolDown_;		//攻撃クールタイム

	int evasionCounter_;		//回避時間カウンター
	int evasionCoolDown_;		//回避クールダウンカウンター
	bool isEvasion_;			//回避フラグ(true=回避中/false=非回避中)
	bool isEvasionCoolDown_;	//回避クールダウンフラグ(true=クールダウン中/false=非クールダウン中)
	bool isEvasionInbincible_;	//回避時無敵フラグ(true=無敵/false=無敵じゃないよ)

	void ChangeDispPos(void);

	Stage* stage_;

	float animCounter_;			//アニメーションカウンター
	//void LoadPlayerImage(void);		//プレイヤー画像の読み込み処理
	//void DrawPlayer(int modelId);		//プレイヤーの描画
	//void SetDrawPlayer(void);		//描画するプレイヤーの設定

};



