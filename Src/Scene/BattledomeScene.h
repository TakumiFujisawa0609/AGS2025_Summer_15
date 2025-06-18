#pragma once

#include"SceneBase.h"

class BattledomeScene : public SceneBase
{
public:
	BattledomeScene();
	~BattledomeScene();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:

};


