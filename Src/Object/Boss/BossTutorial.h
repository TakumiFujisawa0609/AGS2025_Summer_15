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

	BossTutorial();
	~BossTutorial();

	void Init()override;
	void Update()override;
	void Draw()override;
	void Release()override;

private:
	PATTERN pattaern_;
	ATTACK attackState_;

	bool movereturn;
	int attackCounter_;
	Vector2F target_;

	void ChangeState(void);
	bool EnCount(void);
	void Attack();
	void Move();


	// Ú’n‚µ‚Ä‚¢‚é‚Ì”’l‚Ì‘ã“ü‚È‚Ç‚ğ‚Ü‚Æ‚ß‚½ŠÖ”
	void IsGround(Collision::DIR dir)override;
};
