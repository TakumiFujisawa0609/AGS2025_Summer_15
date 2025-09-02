#pragma once

#include"../../TutorialObject.h"

class Kakashi : public TutorialObject
{
public:
	static constexpr int HP_MAX = 6;

	Kakashi();
	~Kakashi()override;

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void Action(void)override;

private:
	int image_;
};