#include "enemy.h"
#include <iostream>

extern ScenePtr scene;
const int START_POINT = 40, END_POINT = 1040;
const int FLOOR0 = 40, FLOOR1 = 170, FLOOR2 = 320, FLOOR3 = 470;
const int FLOAT_SPACE = 20;

Enemy::Enemy(int x, int floor)
	: x(x), floor(floor)
{
	y = floor;
	step = 0;
	move_img_num = 0;
	current_img_num = 0;
	current_direction = RIGHT;
	current_width = 0;
	current_height = 0;

	move_left_path = "";
	move_right_path = "";
}

int Enemy::getX()
{
	return x;
}

int Enemy::getY()
{
	return y;
}

int Enemy::getFloor()
{
	return floor;
}

int Enemy::getCurrentWidth()
{
	return current_width;
}

int Enemy::getCurrentHeight()
{
	return current_height;
}

void Enemy::moveLeft()
{
	std::string current_path = move_left_path + std::to_string(current_img_num++ % move_img_num + 1) + ".png";

	x -= step;

	enemy->setImage(current_path);
	enemy->locate(scene, x, y);
}

void Enemy::moveRight()
{
	std::string current_path = move_right_path + std::to_string(current_img_num++ % move_img_num + 1) + ".png";

	x += step;

	enemy->setImage(current_path);
	enemy->locate(scene, x, y);
}

void Enemy::hide()
{
	enemy->hide();
}

void Enemy::move()
{
	if (isLeftBlocked())
	{
		current_direction = RIGHT;
	}
	else if (isRightBlocked())
	{
		current_direction = LEFT;
	}

	if (current_direction == LEFT)
	{
		moveLeft();
	}
	else if (current_direction == RIGHT)
	{
		moveRight();
	}
}

bool Enemy::isLeftBlocked()
{
	if (x <= 40)
	{
		return true;
	}

	return false;
}

bool Enemy::isRightBlocked()
{
	if (x + current_width >= 1040)
	{
		return true;
	}

	return false;
}

Spider::Spider(int x, int floor, int type)
	: Enemy(x, floor), type(type)
{
	std::string current_path;

	switch (type)
	{
	case BLACK:
		step = 10;
		move_left_path = "Images1/Enemy/spider-black-left";
		move_right_path = "Images1/Enemy/spider-black-right";
		break;
	case WHITE:
		step = 15;
		move_left_path = "Images1/Enemy/spider-white-left";
		move_right_path = "Images1/Enemy/spider-white-right";
		break;
	case RED:
		step = 20;
		move_left_path = "Images1/Enemy/spider-red-left";
		move_right_path = "Images1/Enemy/spider-red-right";
		break;
	}

	move_img_num = 2;
	current_img_num = 1;

	switch (x)
	{
	case START_POINT:
		current_direction = RIGHT;
		current_path = move_right_path + std::to_string(current_img_num) + ".png";
		break;
	default:
		current_direction = LEFT;
		current_path = move_left_path + std::to_string(current_img_num) + ".png";
		break;
	}

	current_width = 39;
	current_height = 24;

	enemy = Object::create(current_path, scene, x, y);
}

Bee::Bee(int x, int floor)
	: Enemy(x, floor)
{
	std::string current_path;

	y = floor + FLOAT_SPACE;

	step = 5;
	move_img_num = 2;
	current_img_num = 1;

	current_width = 32;
	current_height = 52;

	move_left_path = "Images1/Enemy/bee-left";
	move_right_path = "Images1/Enemy/bee-right";

	if (rand() % 2 == 0)
	{
		current_direction = LEFT;

		current_path = move_left_path + std::to_string(current_img_num) + ".png";
	}
	else
	{
		current_direction = RIGHT;

		current_path = move_right_path + std::to_string(current_img_num) + ".png";
	}

	enemy = Object::create(current_path, scene, x, y, false);

	isFree = false;
}

bool Bee::getIsFree()
{
	return isFree;
}

void Bee::move()
{
	if (!isFree)
	{
		return;
	}

	if (isLeftBlocked())
	{
		current_direction = RIGHT;
	}
	else if (isRightBlocked())
	{
		current_direction = LEFT;
	}

	if (current_direction == LEFT)
	{
		moveLeft();
	}
	else if (current_direction == RIGHT)
	{
		moveRight();
	}
}

void Bee::freed()
{
	isFree = true;

	enemy->show();
}

Boss::Boss(int x, int floor)
	: Enemy(x, floor), width{ 96, 48, 72, 96, 48, 72 }
{
	std::string current_path = move_left_path + std::to_string(current_img_num) + ".png";

	step = 15;
	move_img_num = 6;
	current_img_num = 1;
	current_direction = LEFT;
	current_width = width[current_img_num - 1];

	life = 10;

	isExist = true;
}

void Boss::move(int character_x, int character_y)
{
	if (!isExist)
	{
		return;
	}

	if (character_y == FLOOR0)
	{
		if (x < character_x)
		{
			current_direction = RIGHT;
		}
		else if (x > character_x)
		{
			current_direction = LEFT;
		}
	}

	if (isLeftBlocked())
	{
		current_direction = RIGHT;
	}
	else if (isRightBlocked())
	{
		current_direction = LEFT;
	}

	if (current_direction == LEFT)
	{
		moveLeft();
	}
	else if (current_direction == RIGHT)
	{
		moveRight();
	}
}

void Boss::attacked()
{
	life--;

	if (life == 0)
	{
		isExist = false;

		enemy->hide();
	}
}

