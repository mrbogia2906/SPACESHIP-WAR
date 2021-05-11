#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_
#include"BaseObject.h"
#include"BulletObject.h"
#include<vector>

const int WIDTH_MAIN_OBJECT = 48;
const int HEIGHT_MAIN_OBJECT = 46;

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();
	void HandleInputAction(SDL_Event events, SDL_Renderer* ren, Mix_Chunk* m_bullet);
	void HandleMove();
    void SetBulletList(std::vector<BulletObject*> _bullet_list_){p_bullet_list_ = _bullet_list_ ;}
	std::vector <BulletObject*> GetBulletList() { return p_bullet_list_;}
	void MakeBullet(SDL_Renderer* ren);
    void RemoveBullet(const int& idx);

private:
	std::vector <BulletObject*> p_bullet_list_;
	int x_val_;
	int y_val_;
};

#endif  // MAINOBJECT_H_

