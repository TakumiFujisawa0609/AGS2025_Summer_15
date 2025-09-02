#include"TutorialMaster.h"

#include"../../../../Utility/AsoUtility.h"

TutorialMaster::TutorialMaster():
	image_(),
	animeCounter_(0),
	animeInterval_(0)
{
}

TutorialMaster::~TutorialMaster()
{
}

void TutorialMaster::Load(void)
{
	AsoUtility::LoadArrayImg("Data/Image/Tutorial/Master/Idle.png", ANIME_NUM, ANIME_NUM, 1, LOAD_SIZE, LOAD_SIZE, image_);

}

void TutorialMaster::Init(void)
{
	animeCounter_ = 0;
	animeInterval_ = 0;

}

void TutorialMaster::Update(void)
{
	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= image_.size()) { animeCounter_ = 0; }
	}
}

void TutorialMaster::Draw(void)
{
	DrawRotaGraph(1200, 545, SIZE_SCALE, 0, image_.at(animeCounter_), true, true);
}

void TutorialMaster::Release(void)
{
	for (auto& id : image_) { DeleteGraph(id); }
}

