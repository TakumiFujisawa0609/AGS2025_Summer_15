#pragma once

#include<vector>

class TutorialMaster
{
public:
	static constexpr int LOAD_SIZE = 96;

	static constexpr float SIZE_SCALE = 3.0f;



	static constexpr int ANIME_NUM = 10;
	static constexpr int ANIME_INTERVAL = 3;

	
	TutorialMaster();
	~TutorialMaster();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	std::vector<int>image_;
	int animeCounter_;
	int animeInterval_;
};
