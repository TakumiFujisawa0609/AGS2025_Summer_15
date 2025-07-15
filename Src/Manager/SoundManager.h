#pragma once

#include<map>

class SoundManager
{
private:
	SoundManager();
	~SoundManager();
public:
	static void CreateIns(void) { if (ins_ == nullptr) { ins_ = new SoundManager(); ins_->Init(); } }
	static SoundManager& GetIns(void) { CreateIns(); return *ins_; }
	static void DeleteIns(void) { if (ins_ != nullptr) { ins_->Release(); delete ins_; } }

	enum SOUND
	{
		NON=-1,


		MAX,
	};

	void Load(SOUND s);
	void Play(SOUND s, bool loop = false);
	void Delete(SOUND s);

private:
	static SoundManager* ins_;

	int id_[SOUND::MAX];


	void Init(void);
	void Release(void);
};