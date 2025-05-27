#include"SoundManager.h"
#include<DxLib.h>

SoundManager* SoundManager::instance_ = nullptr;

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	Release();
}

void SoundManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager();
	}
	instance_->Init();
}

SoundManager& SoundManager::GetInstance()
{
	return *instance_;
}

void SoundManager::Init()
{
	m_sounds[SID::TITLE_BGM] = LoadSoundMem("Data/Sound/4m.rarara.mp3");
}

void SoundManager::Release()
{
	DeleteSound();
	m_sounds.clear();
	delete instance_;
}

// 再生処理(true = ループしない / false = ループする)
bool SoundManager::Play(SID sid, bool loop)
{
	auto it = m_sounds.find(sid);
	if (it == m_sounds.end())return false;

	int playType = loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;
	PlaySoundMem(it->second, playType);

	return true;
}

void SoundManager::StopSound(SID sid)
{
	auto it = m_sounds.find(sid);
	if (it == m_sounds.end())return;

	StopSoundMem(it->second);
}

void SoundManager::DeleteSound()
{
	for (auto& a : m_sounds)
	{
		DeleteSoundMem(a.second);
	}
}
