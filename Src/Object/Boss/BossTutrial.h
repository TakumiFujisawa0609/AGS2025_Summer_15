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


protected:

	
private:

	void Move();
};
