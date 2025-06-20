#include "UiManager.h"
UiManager* UiManager::instance_ = nullptr;

UiManager::UiManager(void) {}
UiManager::~UiManager(void) {}

void UiManager::AddUi(std::unique_ptr<UiBase> ui)
{
	uis_.emplace_back(std::move(ui));
}

void UiManager::Init(void)
{
	for (auto& ui : uis_)
	{
		ui->Init();
	}
}

void UiManager::Update(void)
{
	for (auto& ui : uis_)
	{
		ui->Update();
	}
	uis_.erase(
		std::remove_if(uis_.begin(), uis_.end(),
			[](const std::unique_ptr<UiBase>& ui)
			{
				return !ui->GetUnit().isAlive_;
			}),
		uis_.end()
	);
}

void UiManager::Draw(void)
{
	for (auto& ui : uis_)
	{
		ui->Draw();
	}
}

void UiManager::Release(void)
{
	for (auto& ui : uis_)
	{
		ui->Release();
	}
	uis_.clear();
}

