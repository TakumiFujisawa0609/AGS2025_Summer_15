#pragma once
#include<DxLib.h>
#include"../Object/UnitBase.h"
#include"../Manager/Camera.h"

#include"SceneBase.h"

class Pause : public SceneBase
{
public:

	static constexpr float MOVE_RANGE = 240.0f;
	static constexpr float DISTANCE = 200.0f;

	enum class STATE
	{
		E_PAUSE,
		E_UPDATE,
	};


	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	STATE GetPauseState(void) { return pauseState_; }
	void SetPauseState(STATE state);

	bool GetExit(void) { return isExit; }

	void KeyInput(void);

private:


	enum SELECT
	{
		CONTINUE,
		NEWGAME,
		EXIT,

		MAX,
	};

	Base obj_[SELECT::MAX];
	int image_[SELECT::MAX];

	STATE pauseState_;
	SELECT select_;

	//‚±‚ê“®‚©‚¹‚Î‘S•”“®‚­
	Vector2F move_;
	Vector2F dispPos[SELECT::MAX];

	VECTOR startPos_;

	bool isExit;

	bool prevDecision, nowDecision, upKeyDecision, downKeyDecision;
	bool prevUp, nowUp, upKeyUp, downKeyUp;
	bool prevDown, nowDown, upKeyDown, downKeyDown;
};