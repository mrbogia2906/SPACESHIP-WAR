#include"BulletObject.h"

BulletObject::BulletObject() {
	x_val_ = y_val_ = 0;
	is_move_ = 0;
	rect_.x = rect_.y = 0;
	rect_.w = 26;
	rect_.h = 9;
}
BulletObject::~BulletObject()
{

}

void BulletObject::HandleInputAction(SDL_Event events, SDL_Renderer *ren)
{

}

void BulletObject::HandleMove(const int x_border, const int y_border)
{
    if (is_move_ == true)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
}

void BulletObject::HandleMoveRightToLeft()
{
  rect_.x -= x_val_;
  if (rect_.x < 0)
  {
    is_move_ = false;
  }
}

