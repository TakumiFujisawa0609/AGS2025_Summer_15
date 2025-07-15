#include "SoundManager.h"

#include<DxLib.h>

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::Load(SOUND s)
{

}

void SoundManager::Play(SOUND s, bool loop)
{
	if (loop) {

	}
	else {
	}
}

void SoundManager::Delete(SOUND s)
{
}

void SoundManager::Init(void)
{
	for (int i = 0; i < SOUND::MAX; i++) { id_[i] = false; }
}

void SoundManager:: Release(void)
{

}