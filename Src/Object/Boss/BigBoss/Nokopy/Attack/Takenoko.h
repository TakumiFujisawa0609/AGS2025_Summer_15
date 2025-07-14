#pragma once
#include"../../../../Common/Base.h"
class Takenoko 
{
public:
    Takenoko();
     ~Takenoko() ;

     void Init(Vector2F pos) ;
     void Update(void) ;
     void Draw(void) ;
     void Release(void) ;
     void SetPos(Vector2F pos) { obj_.pos_ = pos; }
    Base GetBase() const { return obj_; } 
private:
    Base obj_;
};

