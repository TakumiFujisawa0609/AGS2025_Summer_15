#include "UiTitle.h"

UiTitle::UiTitle()
{
}

UiTitle::~UiTitle()
{
}

void UiTitle::Init(void)
{
	Load();
	SetParam();
}

void UiTitle::Update(void)
{
	UiBase::Update();
}

void UiTitle::Draw(void)
{
	UiBase::Draw();
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1, 0, modelId, true);
}

void UiTitle::Release(void)
{
	DeleteGraph(modelId);
}

void UiTitle::Load(void)
{
	modelId = LoadGraph("Data/Image/Ui/SceneTitle/Title.png");
}

void UiTitle::SetParam(void)
{
}
