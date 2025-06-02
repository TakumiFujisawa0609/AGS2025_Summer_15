#include "Tree.h"

Tree::Tree()
{
}

Tree::~Tree()
{
}

void Tree::Init()
{
	unit_.modelId_ = LoadGraph("Data/Image/Decors/Tree.png");
	if (unit_.modelId_ == -1)return;
}

void Tree::Update()
{
}

void Tree::Draw()
{
}

void Tree::Relese()
{
}
