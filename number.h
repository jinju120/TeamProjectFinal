#pragma once
#include <bangtal>
#include <string>
#include "character.h"

using namespace bangtal;

class Number
{
	ObjectPtr number_image;

	int current_number;

	std::string path;

public:
	Number(int x, int y);

	void setCurrentNumber(int current_number);

	void changeImage();
};

class TreasureNumber
{
protected:
	Number* number[2];

	const int NUMBER_INDEX;

public:
	TreasureNumber();
	~TreasureNumber();
};

class CoinNumber : public TreasureNumber
{
	static int holding_coin;

public:
	CoinNumber();

	int getHoldingCoin();

	void setHoldingCoinZero();
	void holdingCoinIncrease();
	void updateNumber();
};

class GreenGemNumber : public TreasureNumber
{
	static int holding_green_gem;

public:
	GreenGemNumber();

	int getHoldingGreenGem();

	void setHoldingGreenGemZero();
	void holdingGreenGemIncrease();
	void updateNumber();
};

class RedGemNumber : public TreasureNumber
{
	static int holding_red_gem;

public:
	RedGemNumber();

	int getHoldingRedGem();

	void setHoldingRedGemZero();
	void holdingRedGemIncrease();
	void updateNumber();
};