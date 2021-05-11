#include "HealthObject.h"

HealthObject::HealthObject()
{

}

HealthObject::~HealthObject()
{

}

void HealthObject::AddPos(const int& xpos)
{
    pos_list_.push_back(xpos);
}

void HealthObject::Render(SDL_Renderer* ren)
{
    if (number_ == pos_list_.size())
    {
        for (int i = 0; i < pos_list_.size(); i++)
        {
            rect_.x = pos_list_.at(i);
            Show(ren);
        }
    }
}

void HealthObject::Init(SDL_Renderer* ren)
{
    LoadImg("gfx/HP_Icon.png", ren);
    number_ = NUM_LIVES;
    if (pos_list_.size() > 0)
    {
        pos_list_.clear();
    }
    AddPos(20);
    AddPos(45);
    AddPos(70);
}

void HealthObject::Decrease()
{
    number_--;
    pos_list_.pop_back();
}

