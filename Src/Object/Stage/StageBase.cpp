#include"StageBase.h"

#include<DxLib.h>

#include"../../Manager/Camera.h"
#include"../../Application.h"

StageBase::StageBase()
{
}

StageBase::~StageBase()
{
}

void StageBase::Init(void)
{
	Load();
}

void StageBase::Draw(void)
{
	//マップチップ画像を表示
	int start = (Camera::GetInstance().GetPos().x / STAGE_CHIP_SIZE);
	int end = start + (Application::MAIN_SCREEN_SIZE_X / STAGE_CHIP_SIZE);

	for (int yy = 0; yy < mapData_.size(); yy++) {
		for (int xx = start; xx < end; xx++) {
			int chip = mapData_[yy][xx];

			int dx = STAGE_CHIP_SIZE * xx - Camera::GetInstance().GetPos().x;
			int dy = STAGE_CHIP_SIZE * yy - Camera::GetInstance().GetPos().y;
			
			DrawGraph(dx, dy, chipId_[chip], true);
		}
	}
}

void StageBase::Release(void)
{
	for (int i = 0; i < mapData_.size(); i++) {
		mapData_[i].clear();
	}
	mapData_.clear();

	for (auto i : chipId_) {
		DeleteGraph(i);
	}
	chipId_.clear();

	DeleteGraph(haikei_);
}

Vector2 StageBase::GetMapNum(void)
{
	return{ (int)mapData_[0].size(),(int)mapData_.size() };
}

