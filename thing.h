#pragma once
#include <bangtal>
#include "enemy.h"
#include "enum.h"

using namespace bangtal;

class Thing
{
protected:
	ObjectPtr thing;

	int type;
	int x;
	int floor;
	int width;

	std::string path;

public:
	Thing(int type, int x, int floor);

	int getX();
	int getFloor();
	int getWidth();

	void hide();
};

class Ladder : public Thing
{
	int height;

public:
	Ladder(int type, int x, int floor);

	int getHeight();
};

class Flooring : public Thing
{
	bool isExist;

public:
	Flooring(int type, int x, int floor, bool isExist);

	bool getIsExist();

	void setState();
};

class Treasure : public Thing
{
	int score;

	bool isExist;

public:
	Treasure(int type, int x, int floor);

	bool getIsExist();

	void obtained();
};

class Key : public Thing
{
	bool isExist;
public:
	Key(int type, int x, int floor);

	bool getIsExist();

	void takenOut();
	void obtained();
};

class Box : public Thing
{
	bool isNotOpened;

	Bee* bee;
	Key* key;

public:
	Box(int type, int x, int floor, Bee* bee);
	Box(int type, int x, int floor, Key* key);

	bool getIsNotOpened();

	void Opened();
};