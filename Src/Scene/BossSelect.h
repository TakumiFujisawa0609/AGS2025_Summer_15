#pragma once

#include"SceneBase.h"

#include"../Manager/SceneManager.h"

class SelectStage;
class SelectPlayer;
class BlastEffectManager;

class BossSelect : public SceneBase
{
public:
	BossSelect();
	~BossSelect();

	void Load(void)override;
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:
	SelectStage* stage_;
	SelectPlayer* player_;
	BlastEffectManager* blast_;


	int scoreImage_;

	struct INFO
	{
		SceneManager::BOSS_KINDS type_;
		int image_;
		int thum_;
		Vector2F pos_;
	};

	INFO bossInfo_[(int)SceneManager::BOSS_KINDS::MAX];

	int nowSelectImage_;
	Vector2F nowSelectPos_;
	int nowSelectCount_;

	bool Collision(void);

	int comingSoon_;
};

