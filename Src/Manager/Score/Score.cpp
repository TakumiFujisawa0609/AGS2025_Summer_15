#include"Score.h"

#include<sstream>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>

#include"../../Utility/AsoUtility.h"

Score* Score::ins_ = nullptr;

Score::Score():
	err_(false)
{
	for (auto& kinds : ranking_) { for (auto& rank : kinds) { rank = -1; } }
}

Score::~Score()
{
}

void Score::Init(void)
{
	std::ifstream ifs = std::ifstream("Data/ranking/ranking.csv");
	if (!ifs) {
		// 読み込みに失敗したので、読み込み失敗を記録して終了
		err_ = true;
		printfDx("ランキングの読み込みに失敗しました\n");
		return;
	}

	std::string line;
	std::vector<std::string> strrSplit;
	float num = 0;
	int kinds = 0;

	while (getline(ifs, line))
	{
		strrSplit = AsoUtility::Split(line, ',');
		for (int i = 0; i < RANKING_NUM; i++) {
			num = stof(strrSplit[i]);

			ranking_[kinds][i] = num;
		}
		kinds++;
	}
}

void Score::SetScore(const float score)
{
	nowScore_.score_ = score;
	nowScore_.rank_ = -1;
	nowScore_.newRecord_ = false;

	int i = -1;
	for (auto& r : ranking_[(int)SceneManager::GetInstance().GetNowBoss()]) {
		i++;

		if (r == -1) {
			r = nowScore_.score_;
			nowScore_.rank_ = i;
			nowScore_.newRecord_ = true;
			break;
		}

		if (nowScore_.score_ < r ) {
			float work = r;
			r = nowScore_.score_;

			for (int j = RANKING_NUM - 1; j > i; j--) {
				ranking_[(int)SceneManager::GetInstance().GetNowBoss()][j] = ranking_[(int)SceneManager::GetInstance().GetNowBoss()][j - 1];
			}
			if (i < RANKING_NUM - 1) { ranking_[(int)SceneManager::GetInstance().GetNowBoss()][i + 1] = work; }

			nowScore_.rank_ = i;
			nowScore_.newRecord_ = true;
			break;
		}
	}
}

std::vector<float> Score::GetRanking(SceneManager::BOSS_KINDS k)
{
	std::vector<float>ret = {};

	for (auto& s : ranking_[(int)k]) {
		ret.emplace_back(s);
	}

	return ret;
}

void Score::RankingReset(void)
{
	for (auto& kinds : ranking_) { for (auto& rank : kinds) { rank = -1; } }
}

void Score::Release(void)
{
	// ロードに失敗していたらすでにあるデータを破壊してしまう可能性があるのでセーブを行わない
	if (err_) { return; }

	std::ofstream ofs("Data/ranking/ranking.csv");
	if (!ofs) {
		printfDx("ランキングの保存に失敗しました\n");
		return;
	}

	for (int kind = 0; kind < (int)BOSS_KINDS::MAX; kind++) {
		for (int i = 0; i < RANKING_NUM; i++) {
			ofs << ranking_[kind][i];
			if (i != RANKING_NUM - 1) { ofs << ","; } //カンマで区切る
		}
		ofs << '\n'; //改行
	}
}