#pragma once

class Tree;

class DecorsManager
{
public:

    DecorsManager();
    ~DecorsManager();

    void Init();
    void Update();
    void Draw();
    void Relese();

private:
    Tree* tree_;
};