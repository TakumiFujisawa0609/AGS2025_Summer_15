#pragma once
#include "../SceneBase.h"

#include "../../Application.h"

class TitleScene : public SceneBase
{
public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Load(void)override;
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	int image_;
	int playImg_;
	int exitImg_;
	int selectFrameImg_;

	enum class SELECT { PLAY, EXIT, MAX };
	SELECT nowSelect_;

	const Vector2F SELECT_POS[(int)SELECT::MAX] =
	{
		{Application::SCREEN_SIZE_X / 4.0f * 1, Application::SCREEN_SIZE_Y - 100},
		{Application::SCREEN_SIZE_X / 4.0f * 3,	Application::SCREEN_SIZE_Y - 100}
	};
};
