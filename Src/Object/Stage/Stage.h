#pragma once
class Stage
{
public:

	Stage();
	~Stage();
	void Init();
	void Update();
	void Draw();
	void Release();

private:
	int stageId;

};
