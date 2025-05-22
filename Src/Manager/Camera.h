#pragma once


class Camera
{
private:
	Camera();
	~Camera();
public:
	static void CreateInstance(void) { if (instance == nullptr)instance = new Camera(); instance->Init(); }
	static Camera& GetInstance(void) { return *instance; }
	static void DeleteInstance(void) { if (instance != nullptr)delete instance; instance = nullptr; }

	void Init();
	void Set();

	enum dir {
		X,
		Y,
		Z,
	};

	VECTOR GetPos(void) { return cameraPos; }

	void Follow(dir xyz, float move);


private:
	static Camera* instance;
	VECTOR cameraPos;
};

