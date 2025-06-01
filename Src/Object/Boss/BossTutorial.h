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

	BossTutorial();
	~BossTutorial();

	void Init()override;
	void Update()override;
	void Draw()override;
	void Release()override;

private:
	PATTERN pattaern_;

	void Attack();

	void Move();

	void MoveX()override;
	void MoveY()override;

	// Ú’n‚µ‚Ä‚¢‚é‚Ì”’l‚Ì‘ã“ü‚È‚Ç‚ğ‚Ü‚Æ‚ß‚½ŠÖ”
	void IsGround(Collision::DIR dir)override;
};
