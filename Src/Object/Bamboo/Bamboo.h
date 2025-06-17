#pragma once

#include"../UnitBase.h"

class Bamboo : public UnitBase
{
public:
	static constexpr float DEFAULT_SIZE = 32;

	static constexpr float SPEED = 10.0f;
	static constexpr float ABS_DIS = 100.0f;

	Bamboo();
	~Bamboo();

	void Init(void)override;
	void Set(Vector2F pos,Vector2F* pPos,int image);
	void Set(Vector2F pos);
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void Collect(void) { unit_.isAlive_ = false; }
private:
	Vector2F* pPos_;

	int image_;

	float scale_;
};

