#include "thing.h"

extern ScenePtr scene;
const int FLOORING_HEIGHT = 20, FLOAT_SPACE = 20;

Thing::Thing(int type, int x, int floor)
	: type(type), x(x), floor(floor)
{
	int y;

	switch (type)
	{
	case DOOR:
		width = 80;
		path = "Images1/Object/door.png";
		break;
	case TRAP:
		width = 34;
		path = "Images1/Object/trap.png";
		break;
	case LADDER:
		width = 44;
		path = "Images1/Object/ladder.png";
		break;
	case FLOORING:
		width = 20;
		path = "Images1/Object/floor.png";
		break;
	case COIN:
		width = 20;
		path = "Images1/Object/coin.png";
		break;
	case GREEN_GEM:
		width = 30;
		path = "Images1/Object/green-gem.png";
		break;
	case RED_GEM:
		width = 30;
		path = "Images1/Object/red-gem.png";
		break;
	case KEY:
		width = 12;
		path = "Images1/Object/key.png";
		break;
	case BOX:
		width = 66;
		path = "Images1/Object/box.png";
		break;
	}

	switch (type)
	{
	case DOOR:
	case LADDER:
	case TRAP:
	case BOX:
		y = floor;
		break;
	case FLOORING:
		y = floor - FLOORING_HEIGHT;
		break;
	case COIN:
	case GREEN_GEM:
	case RED_GEM:
	case KEY:
		y = floor + FLOAT_SPACE;
		break;
	}

	thing = Object::create(path, scene, x, y);
}

int Thing::getX()
{
	return x;
}

int Thing::getFloor()
{
	return floor;
}

int Thing::getWidth()
{
	return width;
}

void Thing::hide()
{
	thing->hide();
}

Ladder::Ladder(int type, int x, int floor)
	: Thing(type, x, floor)
{
	height = 150;
}

int Ladder::getHeight()
{
	return height;
}

Flooring::Flooring(int type, int x, int floor, bool isExist)
	: Thing(type, x, floor)
{
	this->isExist = isExist;
}

bool Flooring::getIsExist()
{
	return isExist;
}

void Flooring::setState()
{
	if (isExist)
	{
		thing->show();
	}
	else
	{
		thing->hide();
	}
}

Treasure::Treasure(int type, int x, int floor)
	: Thing(type, x, floor)
{
	score = 0;
	switch (type)
	{
	case COIN:
		score = 5;
		break;
	case GREEN_GEM:
		score = 10;
		break;
	case RED_GEM:
		score = 20;
		break;
	}

	isExist = true;
}

bool Treasure::getIsExist()
{
	return isExist;
}

void Treasure::obtained()
{
	isExist = false;

	thing->hide();
}

Key::Key(int type, int x, int floor)
	: Thing(type, x, floor)
{
	isExist = false;

	thing->hide();
}

bool Key::getIsExist()
{
	return isExist;
}

void Key::takenOut()
{
	isExist = true;

	thing->show();
}

void Key::obtained()
{
	isExist = false;

	thing->hide();
}

Box::Box(int type, int x, int floor, Bee* bee)
	: Thing(type, x, floor), bee(bee)
{
	isNotOpened = true;

	key = NULL;
}

Box::Box(int type, int x, int floor, Key* key)
	: Thing(type, x, floor), key(key)
{
	isNotOpened = true;

	bee = NULL;
}

bool Box::getIsNotOpened()
{
	return isNotOpened;
}

void Box::Opened()
{
	isNotOpened = false;

	thing->hide();

	if (key == NULL)
	{
		bee->freed();
	}
	else if (bee == NULL)
	{
		key->takenOut();
	}
}

