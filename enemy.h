#pragma once
#include <bangtal>
#include <cstdlib>
#include <ctime>
#include "enum.h"

using namespace bangtal;

class Enemy
{
protected:
	ObjectPtr enemy;

	int x, y;
	int floor;
	int step;
	int move_img_num;
	int current_img_num;
	int current_direction;
	int current_width;
	int current_height;

	std::string move_left_path;
	std::string move_right_path;

	void moveLeft();
	void moveRight();

	bool isLeftBlocked();
	bool isRightBlocked();

public:
	Enemy(int x, int floor);

	int getX();
	int getY();
	int getFloor();
	int getCurrentWidth();
	int getCurrentHeight();

	void hide();
	void move();
};

class Spider : public Enemy
{
	int type;

public:
	Spider(int x, int floor, int type);
};

class Bee : public Enemy
{
	bool isFree;

public:
	Bee(int x, int floor);

	bool getIsFree();

	void move();
	void freed();
};

class Boss : public Enemy
{
	int life;
	
	int width[6];

	bool isExist;

public:
	Boss(int x, int floor);

	void move(int character_x, int character_floor);
	void attacked();
};