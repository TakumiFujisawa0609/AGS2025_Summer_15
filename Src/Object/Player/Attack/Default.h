#pragma once

#include"PlayerAttackBase.h"

class Default : public PlayerAttackBase
{
public:
	Default(Vector2F* pPos);
	~Default();

	void Init(AsoUtility::DIRECTION dir)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:

};

