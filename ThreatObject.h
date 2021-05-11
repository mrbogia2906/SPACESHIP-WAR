#ifndef THREATES_OBJECT_H_
#define THREATES_OBJECT_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

const int WIDTH_THREAT = 48;
const int HEIGHT_THREAT = 46;

class ThreatObject : public BaseObject
{
public:
  ThreatObject();
  ~ThreatObject();

  void HandleMove(const int& x_bordr, const int& y_border);
  void HandleMoveBoss(const int& x_bordr, const int& y_border);
  void HandleInputAction(SDL_Event events);

  void set_x_val(const int& val) {x_val_ = val;}
  void set_y_val(const int& val) {y_val_ = val;}
  int get_x_val() const {return x_val_;}
  int get_y_val() const {return y_val_;}

  void SetBulletList(std::vector<BulletObject*> bullet_list) {p_bullet_list_ = bullet_list;}
  std::vector<BulletObject*> GetBulletList() const {return p_bullet_list_;}

  void InitBullet(BulletObject* p_bullet, SDL_Renderer* ren);
  void MakeBullet(SDL_Renderer* ren, const int& x_limit, const int& y_limit);
  void Reset(const int& xboder);
  void ResetBullet(BulletObject* p_bullet);
private:
  int x_val_;
  int y_val_;

  std::vector<BulletObject*> p_bullet_list_;
};

#endif
