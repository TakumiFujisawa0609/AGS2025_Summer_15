#pragma once
#include<DxLib.h>
#include"../BossBase.h"

class Runboo : public BossBase
{
public:

	Runboo();
	~Runboo();

	void Init()override;
	void Update()override;
	void Draw()override;
	void Release()override;

private:

};