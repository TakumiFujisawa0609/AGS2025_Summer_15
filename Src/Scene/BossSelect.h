#pragma once

#include"SceneBase.h"

class BossSelect : public SceneBase
{
public:
	BossSelect();
	~BossSelect();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	static void BossKind(void) {}

private:

};

