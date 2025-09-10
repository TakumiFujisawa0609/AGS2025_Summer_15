#pragma once

#include"../SceneManager.h"

class Score
{
private:
	Score();
	~Score();
public:
	static void CreateInstance(void) { if (ins_ == nullptr) { ins_ = new Score(); ins_->Load(); } }
	static Score& GetIns(void) { CreateInstance(); return *ins_; }
	static void DeleteIns(void) { if (ins_ != nullptr) { ins_->Save(); delete ins_; } }

	struct ScoreInfo
	{
		float score_;
		bool newRecord_;
		int rank_;
	};
	static constexpr int RANKING_NUM = 5;

	void Load(void);

	void SetScore(const float score);
	ScoreInfo GetNowScore(void) { return nowScore_; }
	std::vector<float>GetRanking(SceneManager::BOSS_KINDS k);

	void Save(void);

	/// <summary>
	/// ランキングリセット
	/// </summary>
	/// <param name="k">リセットしたいランキングの種類(BOSS_KINDS::MAXを指定すると全てリセット)</param>
	void RankingReset(BOSS_KINDS k);
	void RankingReset(BOSS_KINDS k, int rank) {
		if (rank < 1 || RANKING_NUM < rank) { return; }
		for (int i = rank; i < RANKING_NUM; i++) { ranking_[(int)k][i - 1] = ranking_[(int)k][i]; ranking_[(int)k][i] = -1; }
	}

private:
	static Score* ins_;

	float ranking_[(int)SceneManager::BOSS_KINDS::MAX][RANKING_NUM];

	ScoreInfo nowScore_;

	bool err_;
};

