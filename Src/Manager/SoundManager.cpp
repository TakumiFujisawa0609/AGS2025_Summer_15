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
}

void SoundManager::Release()
{
	AllDeleteSound();
	m_sounds.clear();
	delete instance_;
}

void SoundManager::LoadSound(SID sid)
{
	switch (sid)
	{
	case SoundManager::SID::TITLE_BGM:
		m_sounds[SID::TITLE_BGM] = LoadSoundMem("Data/Sound/4m.rarara.mp3");
		break;
	case SoundManager::SID::JUMP_SOUND:
		m_sounds[SID::JUMP_SOUND] = LoadSoundMem("Data/Sound/jump.mp3");
		break;
	}
}

void SoundManager::DeleteSound(SID sid)
{
	DeleteSoundMem(m_sounds[sid]);
}

// 再生処理 
// サウンドID
// ループ(true = する / false = しない)
// 最初から再生(true = する / false = しない)
bool SoundManager::Play(SID sid, bool loop, bool isBegin)
{
	auto it = m_sounds.find(sid);
	if (it == m_sounds.end())return false;

	if (CheckSoundMem(it->second) == 0)
	{
		PlaySoundMem(it->second, loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK, isBegin);
	}

	return true;
}

void SoundManager::StopSound(SID sid)
{
	auto it = m_sounds.find(sid);
	if (it == m_sounds.end())return;
	
	StopSoundMem(it->second);
}

void SoundManager::AllDeleteSound()
{
	for (auto& a : m_sounds)
	{
		DeleteSoundMem(a.second);
	}
}
