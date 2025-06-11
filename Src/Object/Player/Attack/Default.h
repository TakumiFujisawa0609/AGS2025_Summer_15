#pragma once

#include"PlayerAttackBase.h"

class Default : public PlayerAttackBase
{
public:
	Default(Vector2F* pPos, AsoUtility::DIRECTION* dir);
	~Default();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void On(void)	{ obj_.isAlive_ = true; }
	void Off(void) { obj_.isAlive_ = false; }

private:

};

