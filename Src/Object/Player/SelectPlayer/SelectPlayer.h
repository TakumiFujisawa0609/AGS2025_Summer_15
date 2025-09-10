#pragma once

#include"../../../Common/Vector2.h"
#include"../../Common/Base.h"

#include"../../../Manager/SceneManager.h"

class SelectPlayer
{
public:
	static constexpr int LOAD_SIZE_X = 128;
	static constexpr int LOAD_SIZE_Y = 64;

	static constexpr int ANIME_NUM = 8;
	static constexpr int ANIME_SPEED = 2;

	static constexpr float BAMBOO_SPEED = 15.0f;

	enum B_KINDS{
		RUNBOO,
		BAMMOON,
		TUTORIAL,
		NOKOPY,
	};

	SelectPlayer();
	~SelectPlayer();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	SceneManager::BOSS_KINDS NowSelect(void) { return nowSelect_; }

	void SetVec(Vector2F target);

	Vector2F Pos(void) { return this->pos_; }

	Base GetBamboo(void) { return bamboo_; }

private:
	SceneManager::BOSS_KINDS nowSelect_;

	int image_[ANIME_NUM];
	int animeInterval_;
	int animeCou_;
	int bambooImg_;

	Vector2F pos_;
	Vector2F vec_;

	bool haveB_;
	int arrowImg_[4];
	int arrowAnime_;

	Base bamboo_;


	enum NUMBER_NAME { ONE, TWO, THREE, FOUR, FIVE, MAX };
	struct { bool prev = false, now = false, down = false, up = false; } numberKey_[NUMBER_NAME::MAX];
	static constexpr int NUMBERS_KEY[NUMBER_NAME::MAX] = { 2,3,4,5,6 };

	void RankingReset(void);
};

