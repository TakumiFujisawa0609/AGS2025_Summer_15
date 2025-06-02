#pragma once
#include "PlayerAttackBase.h"

class ArialSweep :
    public PlayerAttackBase
{
public:
	ArialSweep();
	~ArialSweep();

	void Init(void)override;
	void Init(Vector2F* pos)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	

private:


	//プレイヤー攻撃時のマウスの座標
	Vector2 mPos_;

	Vector2F worldMousePos_;
};

