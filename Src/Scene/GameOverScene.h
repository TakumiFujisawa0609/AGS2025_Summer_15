#pragma once
#include "SceneBase.h"
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
	int image_;
	bool padKey_;
};

