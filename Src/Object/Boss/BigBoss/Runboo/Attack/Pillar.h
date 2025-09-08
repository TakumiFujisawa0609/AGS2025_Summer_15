#pragma once

#include"../../../Tutorial/Attack/AttackBase.h"
#include"../../../../../Application.h"

class Pillar : public AttackBase
{
public:

	static constexpr float SIZE_X = 179.0f;
	static constexpr float SIZE_Y = Application::SCREEN_SIZE_Y;

	static constexpr int PILLAR_MAX = 1;

	Pillar(float moveSpeed);
	~Pillar();
	void Init(const Vector2F* pos) override;
	void Update(Vector2F boss);
	void Update() override;
	void Draw(void) override;
	void Release(void) override;

	const std::vector<Base> Get() const override;
	void Hit(int i);
	bool End(void);
	void SetTarget(const Vector2F* target) { target_ = target; }

private:
	std::vector<Base> obj_;
	const Vector2F* target_;

	int cnt_;
	float moveSpeed_;
	float ySpeed_ = 0.0f;
	bool isFalling_ = false;
	bool isFallEnd_ = false;
	Vector2F warnPos_;

	void ChangeDispPos() override;

	
};

