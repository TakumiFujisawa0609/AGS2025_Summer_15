#pragma once
#include"../Enemy/EnemyBase.h"

#include"Attack/Slash.h"
#include"Attack/Bullet.h"
#include"Attack/Tackle.h"


class BossTutorial : public EnemyBase
{
public:

	enum PATTERN
	{
		E_NON,
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

private:
	PATTERN pattaern_;
	ATTACK attackState_;

	int attackCounter_;
	int targetIndex_;

	int idolImg;

	int StartSlashtImg_;
	int EndSlashImg_;

	bool encount_;

	void PattaernManager(void);
	bool EnCount(void);
	void Attack();
	void Move();


	// ê⁄ínÇµÇƒÇ¢ÇÈéûÇÃêîílÇÃë„ì¸Ç»Ç«ÇÇ‹Ç∆ÇﬂÇΩä÷êî
	void IsGround(Collision::DIR dir)override;


	Vector2F panVec_;
	Vector2F target_;

	AttackBase::DIR bossDir_;

	DRAWPAT DrawPat_;

	Slash* slash_;
	Bullet* bullet_;
	Tackle* tackle_;
};
