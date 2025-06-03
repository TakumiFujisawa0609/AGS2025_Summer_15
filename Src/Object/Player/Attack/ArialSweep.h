#pragma once
#include "PlayerAttackBase.h"

class ArialSweep :
    public PlayerAttackBase
{
public:
	ArialSweep();
	~ArialSweep();

	void Init(Vector2F* movePos, Vector2F* drawPos)override;
	void Update(Vector2*mousePos);
	void Draw(void)override;
	void Release(void)override;

	

private:


	//プレイヤー攻撃時のマウスの座標
	Vector2 mPos_;
	Vector2F worldMousePos_;
};

