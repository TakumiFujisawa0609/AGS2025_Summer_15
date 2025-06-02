#pragma once
#include"../Enemy/EnemyBase.h"

#include"Attack/Slash.h"
#include"Attack/Bullet.h"
#include"Attack/Tackle.h"


class BossTutorial : public EnemyBase
{
public:

	static constexpr int SIZE_X = 240;
	static constexpr int SIZE_Y = 249;

	enum PATTERN
	{
		E_NON,
		E_MOVE,
		E_ATTACK,
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

	bool encount_;

	void PattaernManager(void);
	bool EnCount(void);
	void Attack();
	void Move();


	// Ú’n‚µ‚Ä‚¢‚é‚Ì”’l‚Ì‘ã“ü‚È‚Ç‚ğ‚Ü‚Æ‚ß‚½ŠÖ”
	void IsGround(Collision::DIR dir)override;


	Vector2F panVec_;
	Vector2F target_;

	AttackBase::DIR bossDir_;


	Slash* slash_;
	Bullet* bullet_;
	Tackle* tackle_;
};
