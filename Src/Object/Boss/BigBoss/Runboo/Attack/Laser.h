#pragma once
#include<DxLib.h>
#include"../../../Tutorial/Attack/AttackBase.h"

class Laser : public AttackBase
{
public:
	static constexpr int MAX_NUM = 3;
	static constexpr float ATTACK_SPEED = 10.0f;

	static constexpr float SIZE_X = 100.0f;
	static constexpr float SIZE_Y = 10.0f;

	Laser(float moveSpeed);
	~Laser();

	void Init(const Vector2F* pos)override;
	void Update(Vector2F boss);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	const std::vector<Base> Get() const override;

	void Hit(int i);

	bool End(void);

	void SetIsAlive(bool isAlive);

private:
	std::vector<Base> obj_;

	Vector2F attackStartPos_;
	int cnt_;

	void ChangeDispPos() override;
};