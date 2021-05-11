
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "CommonFunc.h"

class BaseObject
{
public:
  BaseObject();
  ~BaseObject();
  void Show(SDL_Renderer* ren);
  bool LoadImg(string path, SDL_Renderer *ren);

  void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
  SDL_Rect GetRect() const {return rect_;}
  SDL_Texture* GetObject() {return p_object_;}
protected:
  SDL_Rect rect_;
  SDL_Texture* p_object_;
};

#endif
