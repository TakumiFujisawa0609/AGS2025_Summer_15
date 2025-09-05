#pragma once

#include"../../../../../Object/Common/Base.h"

class TutorialMasterAttack
{
public:
	static constexpr int LOAD_SIZE_X = 204;
	static constexpr int LOAD_SIZE_Y = 280;

	static constexpr float DRAW_SCALE = 0.5f;

	static constexpr int SIZE_X = LOAD_SIZE_X * DRAW_SCALE;
	static constexpr int SIZE_Y = LOAD_SIZE_Y * DRAW_SCALE;

	static constexpr int ANIME_NUM = 5;

	static constexpr float SPEED = 10.0f;

	TutorialMasterAttack(const Vector2F& pos);
	~TutorialMasterAttack();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	const Base& GetObj(void)const { return obj_; }

	void On(void);
	void Hit(void) { obj_.isAlive_ = false; }

private:
	int img_[ANIME_NUM];
	int animeCounter_;
	int animeInterval_;

	Base obj_;

	const Vector2F& masterPos_;
};
