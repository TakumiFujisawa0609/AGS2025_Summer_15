#pragma once
#include "SceneBase.h"
class GameClear :
    public SceneBase
{
public:
	// コンストラクタ
	GameClear(void);

	// デストラクタ
	~GameClear(void);

	void Load(void)override;
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	int image_;
	bool padKey_;

	int rankImg_;
};

