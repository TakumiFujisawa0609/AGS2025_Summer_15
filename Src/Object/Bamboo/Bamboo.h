#pragma once

#include"../UnitBase.h"

class Bamboo : public UnitBase
{
public:
	Bamboo();
	~Bamboo();

	void Init(void)override;
	void Set(Vector2F pos);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:

};

