#pragma once

#include"SceneBase.h"

class BattledoneScene : public SceneBase
{
public:
	BattledoneScene();
	~BattledoneScene();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:

};


