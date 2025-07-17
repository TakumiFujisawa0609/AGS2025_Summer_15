#include<DxLib.h>
#include "BamBlastEffect.h"

BamBlastEffect::BamBlastEffect(void)
{

}

BamBlastEffect::~BamBlastEffect(void)
{
}

void BamBlastEffect::Init(void)
{
    counter_ = 0;
    pos_ = { 0,0 };
    bpLv_ = 0;
}

void BamBlastEffect::Update(void)
{
    if(counter_>0)counter_--;
        
    if (isAlive_) {
        if (counter_ == 0)
        {
            isAlive_ = false;
            bpLv_ = 0;
        }
    }
}

void BamBlastEffect::Draw(void)
{
    if (!isAlive_) return;
    DrawRotaGraph(
        static_cast<int>(pos_.x), 
        static_cast<int>(pos_.y), 
        0.1+bpLv_*0.1, // Šg‘å—¦
        0.0, // Šp“x
        img_,
        TRUE // “§‰ß
    );
}

void BamBlastEffect::Relese(void)
{
}

void BamBlastEffect::On(Vector2F pos, int bp,int img)
{
	this->isAlive_ = true;
	this->pos_ = pos;
	this->bpLv_ = bp;
    counter_ = DRAW_COUNTER;
    img_ = img;
}
