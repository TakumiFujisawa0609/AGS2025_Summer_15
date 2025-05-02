#include "UnitBase.h"
#include"../Application.h"
#include"../Utility/AsoUtility.h"


UnitBase::UnitBase()
{
	modelId_ = -1;
	pos_ = { 0.0f,0.0f };
	size_ = { 0.0f,0.f };

	radius_ = 0.0f;
	speed_ = 0.0f;

}

UnitBase::~UnitBase()
{
}