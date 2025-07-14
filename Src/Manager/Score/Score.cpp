#include"Score.h"

Score::Score()
{
}

Score::~Score()
{
}

void Score::Init(void)
{
	for (auto& kinds : ranking_) { for (auto& rank : kinds) { rank = -1; } }
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

void Score::Release(void)
{
}