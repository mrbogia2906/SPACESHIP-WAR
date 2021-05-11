#ifndef HEALTH_OBJECT_H_
#define HEALTH_OBJECT_H_

#include "BaseObject.h"

class HealthObject : public BaseObject
{
public:
    HealthObject();
    ~HealthObject();

    void SetNumber(const int& num) {number_ = num;}
    void AddPos(const int& xpos);
    void Render(SDL_Renderer* ren);
    void Init(SDL_Renderer* ren);
    void Decrease();

private:
    int number_;
    std::vector<int> pos_list_;
};



#endif // HEALTH_OBJECT_H_

