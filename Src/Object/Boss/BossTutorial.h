#pragma once
#include"../Enemy/EnemyBase.h"

class BossTutorial : public EnemyBase
{
public:

	enum PATTERN
	{
		E_NON,
		E_MOVE,
		E_ATTACK,
	};

	enum ATTACK
	{
		NON = -1,
		TACKLE,
		SLASH,
		BULLET,
		ROAR,
		BLAST,

		MAX,
	};

	const Vector2F BOSS_POINT[3] =
	{
		{3700.0f,712.0f},
		{4160.0f,712.0f},
		{4640.0f,712.0f}
	};

	BossTutorial();
	~BossTutorial();

	void Init()override;
	void Update()override;
	void Draw()override;
	void Release()override;

private:
	PATTERN pattaern_;
	ATTACK attackState_;

	int attackCounter_;
	int targetIndex_;

	bool encount_;

	void PattaernManager(void);
	bool EnCount(void);
	void Attack();
	void Move();


	// Ú’n‚µ‚Ä‚¢‚é‚Ì”’l‚Ì‘ã“ü‚È‚Ç‚ğ‚Ü‚Æ‚ß‚½ŠÖ”
	void IsGround(Collision::DIR dir)override;
};
