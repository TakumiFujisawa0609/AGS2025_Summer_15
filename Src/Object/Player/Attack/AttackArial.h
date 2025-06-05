#pragma once
#include "PlayerAttackBase.h"
	class AttackArial :
	public PlayerAttackBase
{
public:
	AttackArial();
	~AttackArial()override;

	void Init(Vector2F* movePos, Vector2F* drawPos, AsoUtility::DIRECTION* dir);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;
private:

};
