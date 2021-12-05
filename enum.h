#pragma once
enum Direction
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
};

enum JumpState
{
	STOP = 0,
	JUMP_UP,
	JUMP_DOWN,
	LAND,
};

enum ClimbState
{
	CLIMB_STOP = 0,
	CLIMB,
};

enum Stage
{
	STAGE1 = 0,
	STAGE2,
	STAGE3,
	BOSS
};

enum SpiderType
{
	BLACK = 0,
	WHITE,
	RED,
};

enum ThingType
{
	DOOR = 0,
	TRAP,
	LADDER,
	FLOORING,
	COIN,
	GREEN_GEM,
	RED_GEM,
	KEY,
	BOX,
};