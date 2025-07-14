#pragma once

#include<vector>

#include"../../../../../Common/Vector2.h"
#include"../../../../Common/Base.h"
#include"../../../../../Application.h"
#include"../../../../../Manager/Camera.h"

class Csphere
{
public:
	static constexpr int LOAD_SIZE = 60;
	static constexpr float DEFAULT_SCALE = 2.0f;
	static constexpr float DEFAULT_SIZE = LOAD_SIZE * DEFAULT_SCALE;

	static constexpr int ANIME_NUM = 9;

	static constexpr int ANIME_SPEED = 1;

	static constexpr float SPEED = 3.0f;

	static constexpr int ALIVE_TIME = 1000;

	Csphere();
	~Csphere();

	void Init(const Vector2F* pos);
	void Update(void);
	void Draw(void);
	void Release(void);

	Base& GetObj(void) { return obj_; }


	void CorceChange(Vector2F pPos);
	void On(Vector2F pPos);


	void Hit(void);

	bool End(void) { return end_; }

private:
	int img_[ANIME_NUM];
	int animCou_;
	int animInterval_;
	void Animation(void);

	Base obj_;

	int aliveCou_;

	const Vector2F* bossPos_;

	Vector2F moveVec_;

	Vector2F floMove_;
	int flo_;
	float scale_;

	void ChangeDispPos(void) { obj_.disppos_ = obj_.pos_ - Camera::GetInstance().GetPos(); }

	void SetScale(void);

	bool end_;
};
