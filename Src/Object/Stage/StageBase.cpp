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
	this->Release();

	Load();
	if (!LoadMapData()) {
		return;
	}
}

void StageBase::BackDraw(void)
{
}

void StageBase::Draw(void)
{
	//マップチップ画像を表示
	int start = (Camera::GetInstance().GetPos().x / STAGE_CHIP_SIZE);
	int end = start + (Application::SCREEN_SIZE_X / STAGE_CHIP_SIZE) + 1;

	for (int yy = 0; yy < mapData_.size(); yy++) {
		for (int xx = start; xx < end; xx++) {
			int chip = mapData_[yy][xx % mapData_.at(yy).size()];
			if (chip == -1)continue;

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

	for (auto& i : chipId_) {
		DeleteGraph(i);
	}
	chipId_.clear();

	DeleteGraph(haikei_);

	AddRelease();
}

Vector2 StageBase::GetMapNum(void)
{
	return{ (int)mapData_[0].size(),(int)mapData_.size() };
}

