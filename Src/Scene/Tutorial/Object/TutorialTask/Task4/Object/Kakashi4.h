#pragma once

#include"../../TutorialObject.h"

class Kakashi4 : public TutorialObject
{
public:
	Kakashi4();
	~Kakashi4()override;

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void Action(void)override;

private:
	int image_;
};