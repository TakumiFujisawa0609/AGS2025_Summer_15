#pragma once

#include"../SceneManager.h"

class Score
{
private:
	Score();
	~Score();
public:
	static void CreateInstance(void) { if (ins_ == nullptr) { ins_ = new Score(); ins_->Init(); } }
	static Score& GetIns(void) { CreateInstance(); return *ins_; }
	static void DeleteIns(void) { if (ins_ != nullptr) { ins_->Release(); delete ins_; } }

	struct ScoreInfo
	{
		float score_;
		bool newRecord_;
		int rank_;
	};
	static constexpr int RANKING_NUM = 5;

	void Init(void);

	void SetScore(const float score);
	ScoreInfo GetNowScore(void) { return nowScore_; }
	std::vector<float>GetRanking(SceneManager::BOSS_KINDS k);
	void RankingReset(void);

	void Release(void);

private:
	static Score* ins_;

	float ranking_[(int)SceneManager::BOSS_KINDS::MAX][RANKING_NUM];

	ScoreInfo nowScore_;

	bool err_;
};

