#pragma once
#include "SceneBase.h"

#include"../Application.h"

class GameOverScene :
    public SceneBase
{
public:

	// コンストラクタ
	GameOverScene(void);

	// デストラクタ
	~GameOverScene(void);

	void Load(void)override;
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	int backImage_;

	enum class SELECT { REPLAY, TITLE, MAX };
	SELECT nowSelect_;
	int selectImg_[(int)SELECT::MAX];
	int nowSelectFrameImg_;

	const Vector2 SELECT_POS[(int)SELECT::MAX] =
	{
		{Application::SCREEN_SIZE_X / 4 * 1,Application::SCREEN_SIZE_Y - 150},
		{Application::SCREEN_SIZE_X / 4 * 3,Application::SCREEN_SIZE_Y - 150}
	};
};

