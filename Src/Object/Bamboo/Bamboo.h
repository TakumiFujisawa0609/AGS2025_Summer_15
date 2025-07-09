#pragma once

#include"../UnitBase.h"

class Bamboo : public UnitBase
{
public:
	static constexpr float DEFAULT_SIZE = 64;

	static constexpr float SPEED = 10.0f;
	static constexpr float ABS_DIS = 100.0f;

	static constexpr int ALIVE_TIME = 600;

	Bamboo();
	~Bamboo();

	void Init(void)override;
	void Set(Vector2F pos, int image);
	void Set(Vector2F pos);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	float GetScale(void) { return scale_; }

	void Collect(void) { unit_.isAlive_ = false; }
private:
	int image_;

	float scale_;
	const float scaleTb[4] = { 0.0f,1.0f,1.5f,2.0f };

	int aliveTime_;
};

