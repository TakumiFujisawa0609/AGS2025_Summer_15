#pragma once

#include"../SceneBase.h"

class TutorialPlayer;
class TutorialMaster;
class StageBase;

class BlastEffectManager;

class TutorialTaskManager;

class BambooManager;

class TutorialScene : public SceneBase
{
public:
	TutorialScene();
	~TutorialScene();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	TutorialPlayer* player_;
	TutorialMaster* master_;
	StageBase* stage_;

	BlastEffectManager* blastEffect_;

	TutorialTaskManager* task_;

	BambooManager* bamboo_;

	void Collision(void);
};

