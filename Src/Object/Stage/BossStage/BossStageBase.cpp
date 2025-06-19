#include"BossStageBase.h"

#include<DxLib.h>

#include"../../../Manager/Camera.h"

BossStageBase::BossStageBase()
{
}

BossStageBase::~BossStageBase()
{
}

void BossStageBase::Init(void)
{
	Load();
}

void BossStageBase::Draw(void)
{
	//マップチップ画像を表示
	for (int yy = 0; yy < mapData_.size(); yy++) {
		for (int xx = 0; xx < mapData_[yy].size(); xx++) {

			int chip = mapData_[yy][xx];

			int dx = STAGE_CHIP_SIZE * xx - Camera::GetInstance().GetPos().x;
			int dy = STAGE_CHIP_SIZE * yy - Camera::GetInstance().GetPos().y;

			DrawGraph(dx, dy, chipId_[chip], true);
		}
	}
}

void BossStageBase::Release(void)
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
