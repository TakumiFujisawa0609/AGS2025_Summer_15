#pragma once
#include"../Enemy/EnemyBase.h"

#include"Attack/Slash.h"
#include"Attack/Bullet.h"
#include"Attack/Blast.h"
#include"Attack/Tackle.h"


class BossTutorial : public EnemyBase
{
public:

	static constexpr int SIZE_X = 240;
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

	const std::vector<Base> GetObjAttack(const ATTACK state)const;

	void SetDamage(int dmg);

private:
	PATTERN pattaern_;
	ATTACK attackState_;

	int attackCounter_;
	int targetIndex_;

	int idolImg;

	int StartSlashtImg_;
	int EndSlashImg_;

	int frameCounter_;

	bool encount_;

	int dispHp_;
	int hpShakeTimer_;  // 揺れ時間（フレーム数）
	int prevHp_;       // 直前のHP（変化検出用）

	bool isHit_;
	int hitTimer_;
	int flashInterval_;

	void BossDraw();

	void PattaernManager(void);
	bool EnCount(void);
	void Idle(void);
	void Move();
	void Attack();
	void TargetLook(void);

	void BossDeath();
	void DrawHP();

	// 接地している時の数値の代入などをまとめた関数
	void IsGround(Collision::DIR dir)override;


	Vector2F panVec_;
	Vector2F target_;

	AttackBase::DIR bossDir_;

	DRAWPAT DrawPat_;

	Slash* slash_;
	Bullet* bullet_;
	Blast* blast_;
	Tackle* tackle_;

	
};
