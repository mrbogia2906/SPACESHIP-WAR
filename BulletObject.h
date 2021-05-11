#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_
#include "BaseObject.h"

const int BULLET_WIDTH = 26;
const int BULLET_HEIGHT= 9;

class BulletObject : public BaseObject {
public:
	BulletObject();
	~BulletObject();
	void HandleInputAction(SDL_Event events, SDL_Renderer *ren);
	void HandleMove( const int x_border, const int y_border );
	void HandleMoveRightToLeft();

	void SetIsMove(bool is_move) { is_move_ = is_move; };
	bool GetIsMove() { return is_move_; };
	void set_x_val(const int& val) {x_val_ = val;}
    void set_y_val(const int& val) {y_val_ = val;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

private:
	int x_val_;
	int y_val_;
	bool is_move_;
};

#endif // BULLET_OBJECT_H_


