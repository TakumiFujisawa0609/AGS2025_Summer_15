#pragma once

#include"SceneBase.h"

class ModeSelect : public SceneBase
{
public:
	ModeSelect();
	~ModeSelect();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:

};