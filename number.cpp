#include "number.h"

extern ScenePtr scene;
const int NUMBER_WIDTH = 29;
const int INTERVAL = 3;

Number::Number(int x, int y)
{
	current_number = 0;

	path = "Images2/Text/";

	number_image = Object::create("Images2/Text/0.png", scene, x, y, true);
}

void Number::setCurrentNumber(int current_number)
{
	this->current_number = current_number;
}

void Number::changeImage()
{
	std::string current_path = path + std::to_string(current_number) + ".png";

	number_image->setImage(current_path);
}

TreasureNumber::TreasureNumber()
	:NUMBER_INDEX(2)
{
	for (int i = 0; i < NUMBER_INDEX; i++)
	{
		number[i] = NULL;
	}
}

TreasureNumber::~TreasureNumber()
{
	for (int i = 0; i < NUMBER_INDEX; i++)
	{
		delete number[i];
	}
}

CoinNumber::CoinNumber()
{
	for (int i = 0; i < NUMBER_INDEX; i++)
	{
		number[i] = new Number(1190 + NUMBER_WIDTH * i + INTERVAL, 150);
	}
}

int CoinNumber::getHoldingCoin()
{
	return holding_coin;
}

void CoinNumber::setHoldingCoinZero()
{
	holding_coin = 0;
}

void CoinNumber::holdingCoinIncrease()
{
	holding_coin++;
}

void CoinNumber::updateNumber()
{
	number[0]->setCurrentNumber(holding_coin / 10);
	number[1]->setCurrentNumber(holding_coin % 10);
	
	for (int i = 0; i < NUMBER_INDEX; i++)
	{
		number[i]->changeImage();
	}
}

GreenGemNumber::GreenGemNumber()
{
	for (int i = 0; i < NUMBER_INDEX; i++)
	{
		number[i] = new Number(1190 + NUMBER_WIDTH * i + INTERVAL, 210);
	}
}

int GreenGemNumber::getHoldingGreenGem()
{
	return holding_green_gem;
}

void GreenGemNumber::setHoldingGreenGemZero()
{
	holding_green_gem = 0;
}

void GreenGemNumber::holdingGreenGemIncrease()
{
	holding_green_gem++;
}

void GreenGemNumber::updateNumber()
{
	number[0]->setCurrentNumber(holding_green_gem / 10);
	number[1]->setCurrentNumber(holding_green_gem % 10);

	for (int i = 0; i < NUMBER_INDEX; i++)
	{
		number[i]->changeImage();
	}
}

RedGemNumber::RedGemNumber()
{
	for (int i = 0; i < NUMBER_INDEX; i++)
	{
		number[i] = new Number(1190 + NUMBER_WIDTH * i + INTERVAL, 270);
	}
}

int RedGemNumber::getHoldingRedGem()
{
	return holding_red_gem;
}

void RedGemNumber::setHoldingRedGemZero()
{
	holding_red_gem = 0;
}

void RedGemNumber::holdingRedGemIncrease()
{
	holding_red_gem++;
}

void RedGemNumber::updateNumber()
{
	number[0]->setCurrentNumber(holding_red_gem / 10);
	number[1]->setCurrentNumber(holding_red_gem % 10);

	for (int i = 0; i < NUMBER_INDEX; i++)
	{
		number[i]->changeImage();
	}
}
//#include "number.h"
//
//extern ScenePtr scene;
//ScenePtr play_scene = scene;
//
//Number::Number(ScenePtr scene, int x, int y)
//{
//	current_number = 0;
//
//	path = "Images2/Text";
//
//	number_image = Object::create("Images2/Text/0.png", scene, x, y, true);
//}
//
//void Number::setCurrentNumber(int current_number)
//{
//	this->current_number = current_number;
//}
//
//void Number::changeImage()
//{
//	std::string current_path = path + std::to_string(current_number) + ".png";
//
//	number_image->setImage(current_path);
//}
//
///*
//Score::Score(ScenePtr scene)
//	: NUMBER_INDEX(4)
//{
//	for (int i = 0; i < NUMBER_INDEX; i++)
//	{
//		if (scene == play_scene)
//		{
//			number[i] = new Number(scene, );
//		}
//		else if (scene == )
//		{
//			number[i] = new Number(scene, );
//		}
//	}
//}
//*/
//
//void Score::setScoreZero()
//{
//	score = 0;
//
//	updateNumber();
//}
//
//void Score::updateNumber()
//{
//	std::string str_score = std::to_string(score);
//
//	for (int i = 0; i < NUMBER_INDEX; i++)
//	{
//		number[i]->setCurrentNumber(str_score[i] - '0');
//		number[i]->changeImage();
//	}
//}
//
//void Score::increase(int score)
//{
//	this->score += score;
//}