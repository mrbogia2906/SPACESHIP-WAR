#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
  rect_.x = SCREEN_WIDTH;
  rect_.y = SCREEN_HEIGHT*0.5;
  rect_.w = WIDTH_THREAT;
  rect_.h = HEIGHT_THREAT;

  x_val_ = 0;
  y_val_ = 0;
}

ThreatObject::~ThreatObject()
{
  if (p_bullet_list_.size() > 0)
  {
    for (int i = 0; i < p_bullet_list_.size(); i++)
    {
      BulletObject* p_bullet = p_bullet_list_.at(i);
      if (p_bullet != NULL)
      {
        delete p_bullet;
        p_bullet = NULL;
      }
    }
    p_bullet_list_.clear();
  }
}


void ThreatObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* ren)
{
  if (p_bullet)
  {
    bool ret = p_bullet->LoadImg("gfx/alienBullet.png", ren);
    if (ret)
    {
      p_bullet->SetIsMove(true);
      p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
      p_bullet->set_x_val(SPEED_BULLET_THREATS);
      p_bullet_list_.push_back(p_bullet);
    }
  }
}


void ThreatObject::MakeBullet(SDL_Renderer* ren, const int& x_limit, const int& y_limit)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    BulletObject* p_bullet = p_bullet_list_.at(i);
    if (p_bullet)
    {
      if (p_bullet->GetIsMove())
      {
        p_bullet->Show(ren);
        p_bullet->HandleMoveRightToLeft();
      }
      else
      {
        p_bullet->SetIsMove(true);
        p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
      }
    }
  }
}

void ThreatObject::HandleMove(const int& x_bordr, const int& y_border)
{
  rect_.x -= x_val_;
  if (rect_.x < 0)
  {
    rect_.x  = SCREEN_WIDTH;
    rect_.y = rand() % (SCREEN_HEIGHT - 50);
  }
}

void ThreatObject::HandleMoveBoss(const int& x_bordr, const int& y_border)
{
    rect_.y += y_val_;
    if (rect_.y > SCREEN_HEIGHT)
    {
        rect_.y = 0;
        int rand_x = SCREEN_WIDTH-200;
        if (rand_x > SCREEN_WIDTH)
        {
            rand_x = SCREEN_WIDTH * 0.3;
        }
        rect_.x = rand_x;
    }
}

void ThreatObject::HandleInputAction(SDL_Event events)
{
  //Todo
}


void ThreatObject::Reset(const int& xboder)
{
  rect_.x = xboder;
  rect_.y = rand() % SCREEN_HEIGHT;

  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    BulletObject* p_bullet = p_bullet_list_.at(i);
    if (p_bullet)
    {
      ResetBullet(p_bullet);
    }
  }
}

void ThreatObject::ResetBullet(BulletObject* p_bullet)
{
   p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
}
