#pragma once
#include <bangtal>
#include <iostream>
#include <string>
#include <cstdio>
#include "enemy.h"
#include "enum.h"
#include "thing.h"

using namespace bangtal;

class Character
{
	ObjectPtr character;
	ObjectPtr life[3];

	int x, y;
	int life_num;
	int current_floor;
	int current_jump_state;
	int current_img_num;
	int current_direction;
	int current_width;

	int jump_width[3];
	int move_width[8];
	int climb_height[2];

	const int CLIMB_WIDTH;
	const int STOP_WIDTH;
	const int CLIMB_STEP;
	const int MOVE_STEP;
	const int JUMP_STEP;
	const int LONG_JUMP_STEP;
	const int CLIMB_IMG_NUM;
	const int MOVE_IMG_NUM;
	const int JUMP_IMG_NUM;
	const int RIGHT_JUMP_GAP;

	bool isMoving;
	bool isJumping;
	bool isLongJumping;
	bool isClimbing;
	bool isHoldingKey;
	bool isUpBlocked;
	bool isDownBlocked;

	std::string current_path;

	const std::string CLIMB_PATH;
	const std::string MOVE_LEFT_PATH;
	const std::string MOVE_RIGHT_PATH;
	const std::string JUMP_LEFT_PATH;
	const std::string JUMP_RIGHT_PATH;
	const std::string STOP_PATH;

	static int holding_coin;
	static int holding_green_gem;
	static int holding_red_gem;

	void climbUp();
	void climbDown();
	void climbStop();
	void moveLeft();
	void moveRight();
	void jumpLeftUp();
	void jumpRightUp();
	void longJumpLeftUp();
	void longJumpRightUp();
	void jumpLeftDown();
	void jumpRightDown();	
	void longJumpLeftDown();
	void longJumpRightDown();
	void landLeft();
	void landRight();
	void stopLeft();
	void stopRight();
	void blocked();

public:
	Character();

	void setIsUpBlocked(bool isUpBlocked);
	void setIsDownBlocked(bool isDownBlocked);

	bool getIsMoving();
	bool getIsJumping();
	bool getIsHoldingKey();
	bool getIsUpBlocked();
	bool getIsDownBlocked();
	
	void setCurrentFloor();

	void hide();
	void move(int direction);
	void moveStop();
	void jumpUp();
	void jumpDown();
	void land();
	void jumpStop();
	void attack();
	void fall();
	void lifeDecrease();
	void blink(int counter);
	void getCoin(Treasure* coin);
	void getGreenGem(Treasure* green_gem);
	void getRedGem(Treasure* red_gem);
	void getKey(Key* key);
	void openBox(Box* box);

	bool isClimbingLadder();
	bool isLifeNumZero();
	bool isCollideEnemy(Enemy* enemy);
	bool isCollideEnemy(Bee* enemy);
	bool isEntrapped(Thing* thing);
	bool isContactThing(Thing* thing);
	bool isContactUpLadder(Ladder* ladder);
	bool isContactDownLadder(Ladder* ladder);
	bool isContactLadder(Ladder* ladder);
	bool isStepEmptyFloor(Flooring* flooring);
};