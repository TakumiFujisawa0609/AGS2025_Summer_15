#include "UnitBase.h"
#include"../Application.h"
#include"../Utility/AsoUtility.h"


UnitBase::UnitBase()
{
	unit_.modelId_ = -1;
	unit_.pos_ = { 0.0f,0.0f };
	unit_.size_ = { 0.0f,0.f };

	unit_.radius_ = 0.0f;
	unit_.speed_ = 0.0f;

}

UnitBase::~UnitBase()
{
}