#pragma once
#include<DxLib.h>
#include"../../../Tutorial/Attack/AttackBase.h"
#include"../../../../../Application.h"

class Laser : public AttackBase
{
public:
	static constexpr int MAX_NUM = 3;
	static constexpr float ATTACK_SPEED = 10.0f;
	static constexpr int INTERVAL = 30;

	static constexpr float SIZE_X = 100.0f;
	static constexpr float SIZE_Y = 10.0f;

	// 弾の初期速度（ななめ）
	static constexpr float LASER_SPEED = 10.0f;

	// 画面の上下端（反射ライン）
	static constexpr float UPPER_BOUND = 0.0f;
	static constexpr float LOWER_BOUND = Application::SCREEN_SIZE_Y;

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

	void SetTarget(Vector2F target) { target_ = target; }

private:
	std::vector<Base> obj_;

	Vector2F attackStartPos_;
	Vector2F target_;
	int cnt_;

	int shootTimer_ = 0;
	int nextIndex_ = 0;

	void ChangeDispPos() override;
};