#pragma once
#include"../../SceneBase.h"

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

	void Load(void)override;
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	enum class SELECT { BATTLE, TUTORIAL, EXIT, MAX };
	SELECT nowSelect_;
	SELECT prevSelect_;

	int boardImg_;
	int selectImg_[(int)SELECT::MAX];
	int nowSelectFrameImg_;

	const Vector2 SELECT_POS[(int)SELECT::MAX] = { {420,384},{860,384},{640,576} };
	const float SELECT_DRAW_SCALE[(int)SELECT::MAX] = { 1.0f,1.0f,0.5f };
};
