#pragma once
#include"../Common/Base.h"
#include"../../Utility/AsoUtility.h"
#include"../UnitBase.h"


#include"Attack/Default.h"


class Player:public UnitBase
{
public:

	//プレイヤー画像サイズ
	static constexpr int LOAD_SIZE_X = 120;
	static constexpr int LOAD_SIZE_Y = 80;		

	//プレイヤーを表示させる大きさ
	static constexpr float SIZE_SCALE = 2.3f;

	//プレイヤーが当たり判定などに使う大きさ		
	static constexpr int SIZE_X = 13 * SIZE_SCALE;
	static constexpr int SIZE_Y = 40 * SIZE_SCALE;
	
	//各モーションのアニメーション枚数
	static constexpr int IDLE_LOAD_NUM = 10;
	static constexpr int RUN_LOAD_NUM = 10;
	static constexpr int JUMP_LOAD_NUM = 3;
	static constexpr int FALL_LOAD_NUM = 3;
	static constexpr int FIRST_ATTACK_LOAD_NUM = 4;
	static constexpr int SECONDE_ATTACK_LOAD_NUM = 6;
	static constexpr int EVASION_LOAD_NUM = 3;
	static constexpr int GUARD_PER_LOAD_NUM = 3;
	static constexpr int GUARD_LOAD_NUM = 1;
	static constexpr int GUARD_POST_LOAD_NUM = 3;


	//何フレームに１回アニメーションを動かすか
	static constexpr int ANIMATION_SPEED = 2;

	//モーションタイプ
	enum class MOTION
	{
		IDLE,			//待機
		RUN,			//走り
		JUMP,			//ジャンプ
		FALL,			//落下状態
		FIRST_ATTACK,	//攻撃1段目
		SECOND_ATTACK,	//攻撃2段目
		THURD_ATTACK,	//攻撃3段目
		DAMAGE,			//被ダメージ
		GUARD_PER,		//ガード前
		GUARD,			//ガード
		GUARD_POST,		//ガード解除
		EVASION,		//回避

		MAX,			//モーション最大数
	};


	static constexpr int HP_MAX = 100;

	//プレイヤーの状態
	enum class STATE
	{
		MOVE,
		ATTACK,
		GUARD,
		EVASION,
		DAMAGE,
	};

	// 移動状態で使用する定数定義-------------------------------------------------------------------
	
	// 横軸の移動関係
	static constexpr float RUN_SPEED = 10.0f;			//プレイヤーの走る速度


	// ジャンプ関係
	static constexpr float MAX_JUMP_POWER = 50.0f;		//最大ジャンプ力
	static constexpr int INPUT_JUMPKEY_FRAME = 6;		//ジャンプキーを受け付けるフレーム数
	static constexpr int JUMP_NUM =10;					//ジャンプ可能回数
	
	//----------------------------------------------------------------------------------------------


	// 攻撃状態で使用する定数定義-------------------------------------------------------------------
	
	//攻撃の段数
	enum ATTACK
	{
		NON = -1,
		FIRST,
		SECONDE,

		MAX,
	};

	static constexpr int INPUT_ATTACK_FRAME = 20;		//次の段につながる時間(フレーム数)

	Base DefaultAtt(void) { return defaultAttack_->GetObj(); }

	//----------------------------------------------------------------------------------------------


	// ガード状態で使用する定数定義-----------------------------------------------------------------
	static constexpr int GUARD_FRAME = 180;				//総ガードフレーム
	static constexpr int GUARD_PER_RECOVERY_FRAME = 5;	//前硬直フレーム
	static constexpr int GUARD_POST_RECOVERY_FRAME = 10;//後硬直フレーム
	static constexpr int GUARD_JUST_FRAME = 5;			//ジャストガード猶予時間フレーム
	enum class GUARD_STATE
	{
		GUARD_PER,
		GUARD,
		GUARD_JUST,
		GUARD_POST,
	};
	//----------------------------------------------------------------------------------------------
	 
	
	// 回避状態で使用する定数定義-------------------------------------------------------------------
	
	static constexpr float EVASION_SPEED = 10.0f;		//スピード

	static constexpr int EVASION_TIME = 20;				//回避時間

	//----------------------------------------------------------------------------------------------

	// ダメージ状態で使用する定数定義---------------------------------------------------------------
	static constexpr float KNOCK_SPEED = 5.0f;
	static constexpr float KNOCK_POWER = 10.0f;
	void Hit(int damage, Vector2F bPos);
	//----------------------------------------------------------------------------------------------



	Player();
	~Player();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;


private:

	//プレイヤー描画関係-----------------------------------------------------------
	std::vector<int> image_[(int)MOTION::MAX];		//画像ハンドル

	void LoadPlayerImage(void);						//プレイヤー画像の読み込み処理

	void Animation(void);							//アニメーション更新

	void ChangeMotion(MOTION mo, bool loop = true);	//モーション変更

	void DrawPlayer(void);							//プレイヤーの描画

	MOTION motion_;									//現在のモーションタイプを格納する変数

	int animeCounter_;

	int animeInterval_;

	bool animeLoop_;

	const float GetAnimeRatio(void)const;
	//-----------------------------------------------------------------------------

	//向き
	AsoUtility::DIRECTION dir_;


	//状態管理--------------------------------------------------------------------------------------
	
	//状態変数
	STATE state_;

	/// <summary>
	/// 状態ごとに遷移可能のSTATEを振り分けて入力操作に応じてそのSTATEに遷移させる
	/// </summary>
	void StateManager(void);

	/// <summary>
	/// 指定されたSTATEに状態を変更
	/// </summary>
	/// <param name="st">変更先の状態を表すSTATE型の値</param>
	void ChangeState(STATE st);


	// 各状態の遷移する条件------------------------

	// 移動状態に遷移する条件
	void DoStateMove(void);

	// 攻撃状態に遷移する条件
	void DoStateAttack(void);

	// ガード状態に遷移する条件
	void DoStateGuard(void);

	// 回避状態に遷移する条件
	void DoStateEvasion(void);

	//---------------------------------------------


	//状態ごとの関数を呼ぶための関数ポインタ
	void(Player::*stateFuncPtr)(void);


	// 関数ポインタに格納する状態ごとの関数--------
	
	// 移動処理(ジャンプも含まれる)
	void Move(void);

	// 攻撃処理
	void Attack(void);

	// ガード処理
	void Guard(void);

	// 回避処理
	void Evasion(void);

	// ダメージ処理
	void Damage(void);

	//---------------------------------------------



	//----------------------------------------------------------------------------------------------


	// 移動処理関係--------------------------
	
	// 関数
	void Run(void);			//横移動関数
	void Jump(void);		//ジャンプ関数

	// 変数
	int isJump_[JUMP_NUM];	//ジャンプしているかの変数
	int jumpKeyCounter_[JUMP_NUM];

	//---------------------------------------


	// 攻撃処理関係--------------------------


	// 関数

	// 変数
	Default* defaultAttack_;

	bool isAttack_[ATTACK::MAX];
	ATTACK attack_;
	int attackKeyCounter_;
	//---------------------------------------


	// ガード処理関係------------------------

	// 関数
	bool IsGuard(void) { return isGuard_; }
	bool IsJustGuard(void) { return isJustGuard_; }
	// 変数
	int guardCounter_;
	bool isGuard_;
	bool isJustGuard_;
	bool perGuardKey_;
	bool nowGuardKey_;
	GUARD_STATE guardState_;
	//---------------------------------------


	// 回避処理関係--------------------------

	// 関数

	// 変数
	int evasionCounter_;
	bool evasionPossiFlg_;
	//--------------------------------------

	// ダメージ処理関係---------------------
	
	// 関数
	
	// 変数
	bool knockBack_;
	AsoUtility::DIRECTION knockBackDir_;
	//--------------------------------------


	// 接地している時の数値の代入などをまとめた関数
	void IsGround(Collision::DIR dir)override;
};



