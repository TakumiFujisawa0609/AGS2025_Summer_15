#pragma once

#include".././../TutorialObject.h"

class Mato : public TutorialObject
{
public:
	static constexpr float RADIUS = 64.0f;

	Mato();
	~Mato();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void Action(void)override { unit_.isAlive_ = false; };

	void SetPos(Vector2F pos) { unit_.pos_ = pos; }

private:
	int image_;
};
