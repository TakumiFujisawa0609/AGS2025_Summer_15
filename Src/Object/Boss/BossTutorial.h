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
};
