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

	const std::vector<Base> GetAttackObj()const;

private:
	//画像
	int idolImg;

	int StartSlashtImg_;
	int EndSlashImg_;

	//戦闘を行うか行わないか
	bool encount_;
	bool EnCount(void);

	//ボスの立ち位置の振り分け
	int targetIndex_;

	//状態
	PATTERN pattaern_;
	ATTACK attackState_;

	//状態管理
	void PattaernManager(void);

	//状態ごとの行動
	void Idle(void);
	void Move();
	void Attack();


	//便利
	int attackCounter_;

	Vector2F panVec_;
	Vector2F target_;

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
