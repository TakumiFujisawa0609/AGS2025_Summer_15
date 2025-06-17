#pragma once
#include"../Enemy/EnemyBase.h"
#include<map>

#include"Attack/Slash.h"
#include"Attack/Bullet.h"
#include"Attack/Blast.h"
#include"Attack/Tackle.h"


class BossTutorial : public EnemyBase
{
public:

	static constexpr int SIZE_X = 200;
	static constexpr int SIZE_Y = 249;


	static constexpr int BOSS_HP = 150;						//ボスの最大体力
	static constexpr int BOSS_HP_X = 5;					//ボスのHPゲージのX座標始点
	static constexpr int BOSS_HP_Y = 15;						//ボスのHPゲージのY座標始点と描画距離
	static constexpr int BOSS_HP_DISP_Y = 30;				//ボスのHPゲージのX座標の描画距離

	static constexpr float HP_YABAI = 0.3f;			    	// 瀕死のしきい値（30%未満）
	const int BLINK_FLAME = 60;				// 一回の点滅のフレーム（60フレーム＝1秒）

	enum PATTERN
	{
		E_NON,
		E_IDLE,
		E_MOVE,
		E_ATTACK,

	};

	enum DRAWPAT
	{
		NORMAL,
		E_SLASH_START,
		E_SLASH_END,

		DRAW_MAX,
	};
	
	enum ATTACK
	{
		NON = -1,
		SLASH,
		BULLET,
		ROAR,
		BLAST,
		TACKLE,

		MAX,
	};

	const Vector2F BOSS_POINT[3] =
	{
		{3700.0f,712.0f},
		{4160.0f,712.0f},
		{4600.0f,712.0f}
	};

	BossTutorial();
	~BossTutorial();

	void Init()override;
	void Update()override;
	void Draw()override;
	void Release()override;



	const bool GetEnCount(void)const { return encount_; }

	const ATTACK GetAttack(void)const { return attackState_; }

	const std::vector<Base> GetAttackObj()const;
	void ObjHit(int i);

	AttackBase* GetAttackIns(void);

	void SetDamage(int dmg);

	//攻撃パターンの関数ポインタ
	using AttackFunc = void(BossTutorial::*)();

private:

	//画像
	int idolImg;

	int img_[DRAWPAT::DRAW_MAX];
	int EndSlashImg_;

	//戦闘を行うか行わないか
	bool encount_;
	bool EnCount(void);

	int dispHp_;
	int hpShakeTimer_;  // 揺れ時間（フレーム数）
	int prevHp_;       // 直前のHP（変化検出用）

	bool isHit_;
	int hitTimer_;
	int flashInterval_;
	int frameCounter_;

	void BossDraw();

	//ボスの立ち位置の振り分け
	int targetIndex_;

	//状態
	PATTERN pattern_;
	ATTACK attackState_;
	Tackle::DIR tDir_;

	//状態管理
	void PattaernManager(void);

	//状態ごとの行動
	void Idle(void);
	void Move();
	void Attack();
	void HpUpdate();

	void BossDeath();
	void DrawHP();

	//Attackの状態別の関数
	void SlashUpdate(void);
	void BulletUpdate(void);
	void RoarUpdate(void);
	void BlastUpdate(void);
	void TackleUpdate(void);

	//攻撃パターンの関数ポインタをmapで管理
	std::map<ATTACK, AttackFunc> attackUpdateFuncs_;


	//便利
	int attackCounter_;

	Vector2F panVec_;
	Vector2F target_;

	//描画パターン
	DRAWPAT DrawPat_;

	AttackBase::DIR bossDir_;


	//指定した座標の方向を向く
	void TargetLook(Vector2F target);


	// 接地している時の数値の代入などをまとめた関数
	void IsGround(Collision::DIR dir)override;


	//攻撃クラスのインスタンス達----
	Slash* slash_;
	Bullet* bullet_;
	Blast* blast_;
	Tackle* tackle_;
	//------------------------------
};
