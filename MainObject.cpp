#include"MainObject.h"
MainObject::MainObject()
{
	rect_.x = 0  ;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}
MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* ren, Mix_Chunk* m_bullet)
{
	if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
  {
    switch (events.key.keysym.sym)
    {
    case SDLK_UP:
      y_val_ -= SPEED_MAIN_OBJECT;
      break;
    case SDLK_DOWN:
      y_val_ += SPEED_MAIN_OBJECT;
      break;
    case SDLK_RIGHT:
      x_val_ += SPEED_MAIN_OBJECT;
      break;
    case SDLK_LEFT:
      x_val_ -= SPEED_MAIN_OBJECT;
      break;;
    default:
      break;
    }
  }
  else if (events.type == SDL_KEYUP)
  {
    switch(events.key.keysym.sym )
    {
      case SDLK_UP: y_val_ += SPEED_MAIN_OBJECT; break;
      case SDLK_DOWN: y_val_ -= SPEED_MAIN_OBJECT; break;
      case SDLK_LEFT: x_val_ += SPEED_MAIN_OBJECT; break;
      case SDLK_RIGHT: x_val_ -= SPEED_MAIN_OBJECT; break;
    }
  }
  else if (events.type == SDL_MOUSEBUTTONDOWN)
  {
    BulletObject* p_bullet = new BulletObject();
    if (events.button.button == SDL_BUTTON_LEFT)
    {
      p_bullet->LoadImg("gfx/playerBullet1.png", ren);
      Mix_PlayChannel(-1, m_bullet, 0);
    }
    p_bullet->SetRect(this->rect_.x + this->rect_.w - 40, this->rect_.y + this->rect_.h*0.5);
    p_bullet->SetIsMove(true);
    p_bullet->set_x_val(SPEED_BULLET_MAIN);
    p_bullet_list_.push_back(p_bullet);
  }
  else if (events.type == SDL_MOUSEBUTTONUP)
  {

  }
  else
  {
    ;//
  }
}

void MainObject::HandleMove() {
	rect_.x += x_val_;

  if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
  {
    rect_.x -= x_val_;
  }


  rect_.y += y_val_;
  if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT)
  {
    rect_.y -= y_val_;
  }
}

void MainObject::MakeBullet(SDL_Renderer* ren)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    BulletObject* p_bullet_ = p_bullet_list_.at(i);
    if (p_bullet_ != NULL)
    {
      if (p_bullet_->GetIsMove())
      {
        p_bullet_->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        p_bullet_->Show(ren);
      }
      else
      {
        if (p_bullet_ != NULL)
        {
          p_bullet_list_.erase(p_bullet_list_.begin() + i);
          delete p_bullet_;
          p_bullet_ = NULL;
        }
      }
    }
  }
}

void MainObject::RemoveBullet(const int& idx)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    if (idx < p_bullet_list_.size())
   {
      BulletObject* p_bullet = p_bullet_list_.at(idx);
      p_bullet_list_.erase(p_bullet_list_.begin() + idx);

      if (p_bullet != NULL)
      {
        delete p_bullet;
        p_bullet = NULL;
      }
    }
  }
}







