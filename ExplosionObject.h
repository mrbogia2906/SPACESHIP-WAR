#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "BaseObject.h"
#include "CommonFunc.h"

const int EXP_WIDTH = 70;
const int EXP_HEIGHT = 140;

class ExplosionObject : public BaseObject
{
public:
  ExplosionObject();
  ~ExplosionObject();
  void set_clip();
  void SetFrame(const int& fr) {frame_ = fr;}
  void ShowEx(SDL_Renderer* ren);

private:
  int frame_;
  SDL_Rect clip_[4];
};

#endif
