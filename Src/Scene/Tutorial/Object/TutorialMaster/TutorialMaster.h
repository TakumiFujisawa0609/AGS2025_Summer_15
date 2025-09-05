#pragma once

#include<vector>

#include"../TutorialTask/TutorialTaskManager.h"

#include"Attack/TutorialMasterAttack.h"

class TutorialMaster
{
public:
	enum class MOTION { NON = -1, IDLE, ATTACK, MAX };

	static constexpr int LOAD_SIZE = 96;

	static constexpr float SIZE_SCALE = 3.0f;

	static constexpr int IDLE_ANIME_NUM = 10;
	static constexpr int ATTACK_ANIME_NUM = 7;
	static constexpr int ANIME_INTERVAL = 3;

	
	static constexpr int ATTACK_INTERVAL = 240;

	TutorialMaster(const TutorialTaskManager::TASK& task,const bool& taskEnd);
	~TutorialMaster();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	const Base& GetAttack(void)const { return attack_->GetObj(); }
	void AttackHit(void) { attack_->Hit(); }

private:
	MOTION motion_;
	std::vector<int>image_[(int)MOTION::MAX];
	int animeCounter_;
	int animeInterval_;
	bool animeLoop_;

	void AttackMotion(void);

	Vector2F pos_;

	const TutorialTaskManager::TASK& nowTask_;
	const bool& taskEnd_;
	TutorialMasterAttack* attack_;
	int attackIntarval_;
	void Attack(void);
};
