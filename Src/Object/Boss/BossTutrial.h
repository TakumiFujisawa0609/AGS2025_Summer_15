#pragma once
#include"../Enemy/EnemyBase.h"

class BossTutrial : public EnemyBase
{
public:

	BossTutrial();
	~BossTutrial();

	void Init()override;
	void Update()override;
	void Draw()override;
	void Release()override;


	
private:

	void Move();

	void MoveX()override;
	void MoveY()override;

	// Ú’n‚µ‚Ä‚¢‚é‚Ì”’l‚Ì‘ã“ü‚È‚Ç‚ğ‚Ü‚Æ‚ß‚½ŠÖ”
	void IsGround(Collision::DIR dir)override;
};
