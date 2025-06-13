#pragma once

#include"../UnitBase.h"

class Bamboo : public UnitBase
{
public:
	Bamboo();
	~Bamboo();

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:

};

