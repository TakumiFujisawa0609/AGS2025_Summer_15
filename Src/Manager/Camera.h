#pragma once
#include<DxLib.h>
#include"../Common/Vector2.h"


class Camera
{
private:
	Camera();
	~Camera();
public:
	static void CreateInstance(void) { if (instance == nullptr)instance = new Camera(); instance->Init(); }
	static Camera& GetInstance(void) { CreateInstance(); return *instance; }
	static void DeleteInstance(void) { if (instance != nullptr)delete instance; instance = nullptr; }

	void Init();
	void Set();

	enum dir {
		X,
		Y,
	};

	Vector2F GetPos(void) { return cameraPos; }

	void Follow(dir xy, float move);
	bool BossSet(void);

	void SetMapNum(Vector2 num) { mapNum_ = num; }


private:
	static Camera* instance;
	Vector2F cameraPos;

	Vector2 mapNum_;
};

