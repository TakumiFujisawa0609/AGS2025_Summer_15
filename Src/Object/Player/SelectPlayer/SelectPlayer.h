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

	SelectPlayer();
	~SelectPlayer();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	enum B_KINDS{
		RUNBOO,
		BAMMOON,
		TUTORIAL,
		NOKOPY,
	};
	B_KINDS nowSelect_;

	bool NullSelect(int b);

	int image_[ANIME_NUM];
	int animeCou_;
	int bambooImg_;

	Vector2F pos_;

	bool haveB_;

	Base bamboo_;

	void JoyPadInputManager(void);
	bool nowLeftKey_, prevLeftKey_, downLeftKey_, upLeftKey_;
	bool nowRightKey_, prevRightKey_, downRightKey_, upRightKey_;
	bool nowAttackKey_;
};

