#pragma once
#include"../Common/Base.h"
#include"../../Utility/AsoUtility.h"
#include"../UnitBase.h"


#include"Attack/Default.h"
#include"Attack/BPAttack.h"

class Player:public UnitBase
{
public:

	//プレイヤー画像サイズ
	static constexpr int LOAD_SIZE_X = 120;
	static constexpr int LOAD_SIZE_Y = 80;		

	//バンブーパワー画像サイズ
	static constexpr int BAMBOO_SIZE_X = 64;
	static constexpr int BAMBOO_SIZE_Y = 64;

	//プレイヤーを表示させる大きさ
	static constexpr float SIZE_SCALE = 2.3f;

	//プレイヤーが当たり判定などに使う大きさ		
	static constexpr int SIZE_X = 10 * SIZE_SCALE;
	static constexpr int SIZE_Y = 40 * SIZE_SCALE;
	
	//各モーションのアニメーション枚数
	static constexpr int IDLE_LOAD_NUM = 10;
	static constexpr int RUN_LOAD_NUM = 10;
	static constexpr int JUMP_LOAD_NUM = 3;
	static constexpr int FALL_LOAD_NUM = 3;
	static constexpr int FIRST_ATTACK_LOAD_NUM = 4;
	static constexpr int SECONDE_ATTACK_LOAD_NUM = 6;
	static constexpr int EVASION_LOAD_NUM = 3;
	static constexpr int DAMAGE_LOAD_NUM = 1;


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
		SPECIAL_ATTACK,	//特殊攻撃
		DAMAGE,			//被ダメージ
		EVASION,		//回避

		MAX,			//モーション最大数
	};


	static constexpr int HP_MAX = 30;

	//プレイヤーの状態
	enum class STATE
	{
		MOVE,
		ATTACK,
		BP_ATTACK,
		EVASION,
		DAMAGE,
	};

	const STATE GetState(void)const { return state_; }

	// 移動状態で使用する～～-------------------------------------------------------------------
	// 定数
	static constexpr float RUN_SPEED = 10.0f;			//プレイヤーの走る速度

	static constexpr float MAX_JUMP_POWER = 70.0f;		//最大ジャンプ力
	static constexpr int INPUT_JUMPKEY_FRAME = 6;		//ジャンプキーを受け付けるフレーム数
	static constexpr int JUMP_NUM =3;					//ジャンプ可能回数

	static constexpr int JUMP_ANIM = 5;
	
	//----------------------------------------------------------------------------------------------


	// 攻撃状態で使用する～～-------------------------------------------------------------------
	// 定数
	enum ATTACK { NON = -1, FIRST, SECONDE, MAX, };		//攻撃の段数
	static constexpr int INPUT_ATTACK_FRAME = 20;		//次の段につながる時間(フレーム数)

	// 関数
	Base DefaultAtt(void) { return defaultAttack_->GetObj(); }
	//----------------------------------------------------------------------------------------------

	// 特殊攻撃状態で使用する～～--------------------------------------------------------------
	// 定数
	static constexpr int BP_MAX = 20;
	static constexpr int MAX_BP_CONS = 3;
	static constexpr int CHARGE_TIME = 60;

	static constexpr int CHARGE_ANIM = 5;
	static constexpr int CHARGE_ANIM_SPEED = 2;
	// 関数
	std::vector<BPAttack*> GetBpAtt(void) { return BpAtIns_; }
	const int &GetBp(void)const { return bp_; }
	void BpOptain(int bp) { this->bp_ += bp; if (this->bp_ > BP_MAX) { this->bp_ = BP_MAX; } }
	//---------------------------------------------------------------------------------------------	 
	
	// 回避状態で使用する～～-------------------------------------------------------------------
	// 定数
	static constexpr float EVASION_SPEED = 20.0f;		//スピード
	static constexpr int EVASION_TIME = 10;				//回避時間
	//----------------------------------------------------------------------------------------------

	// ダメージ状態で使用する～～---------------------------------------------------------------
	// 定数
	static constexpr float KNOCK_SPEED = 5.0f;
	static constexpr float KNOCK_POWER = 10.0f;
	// 関数
	void Hit(int damage, Vector2F bPos);
	//----------------------------------------------------------------------------------------------


	void SetInvici(int time) { unit_.inviCounter_ = time; }


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

	const float GetAnimeRatio(void)const { return ((float)animeCounter_ / (float)image_[(int)motion_].size()); }
	//-----------------------------------------------------------------------------

	//向き
	AsoUtility::DIRECTION dir_;

	// コントローラーの入力状況管理
	void JoyPadInputManager(void);
	bool nowJumpKey_, prevJumpKey_;
	bool nowLeftKey_, prevLeftKey_;
	bool nowRightKey_, prevRightKey_;
	bool nowAttackKey_, prevAttackKey_;
	bool nowBambooKey_, prevBambooKey_;
	bool nowEvasionKey_, prevEvasionKey_;

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

	// 特殊攻撃状態に遷移する条件
	void DoStateBPAttack(void);

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

	// 特殊攻撃状態
	void BambooAttack(void);

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
	bool isJump_[JUMP_NUM];	//ジャンプしているかの変数
	int jumpKeyCounter_[JUMP_NUM];
	int jumpImg_[JUMP_ANIM];
	float jumpAnim_;
	bool isJumpAnim_;
	//---------------------------------------


	// 攻撃処理関係--------------------------


	// 関数

	// 変数
	Default* defaultAttack_;

	bool isAttack_[ATTACK::MAX];
	ATTACK attack_;
	int attackKeyCounter_;
	//---------------------------------------


	// 特殊攻撃関係--------------------------

	// 関数

	// 変数
	std::vector<BPAttack*> BpAtIns_;
	int BambooImg_;
	int BambooPowerImg_;

	int chargeImg_[CHARGE_ANIM];
	int chargeAnim_;
	int bp_;
	int chargeTime_;
	int bpConsCounter_;
	//---------------------------------------

	// 回避処理関係--------------------------

	// 関数

	// 変数
	int evasionCounter_;
	bool evasionPossiFlg_;
	bool evaConpFlg_;
	//--------------------------------------

	// ダメージ処理関係---------------------
	
	// 関数
	
	// 変数
	bool knockBack_;
	AsoUtility::DIRECTION knockBackDir_;
	//--------------------------------------


	//穴に落ちた時の処理
	void Respawn(void);

	// 接地している時の数値の代入などをまとめた関数
	void IsGround(Collision::DIR dir)override;
};



