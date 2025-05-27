#pragma once
#include<map>

class SoundManager
{
public:

	// リソースの定義
	enum class SID 
	{
		// BGM
		TITLE_BGM,

		// 効果音


		//ゲームシーンの効果音
	};

	SoundManager();
	~SoundManager();

	static void CreateInstance();

	static SoundManager& GetInstance(void);

	// 初期化
	void Init();
	// 解放処理
	void Release();
	
	void DeleteSound();

	bool Play(SID sid, bool loop = false);

	void StopSound(SID sid);

private:

	// 静的インスタンス
	static SoundManager* instance_;

	std::map<SID, int> m_sounds;
};