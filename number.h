#pragma once
//#include <bangtal>
//#include <string>
//#include "character.h"
//
//using namespace bangtal;
//
//class Number
//{
//	ObjectPtr number_image;
//
//	int current_number;
//
//	std::string path;
//
//public:
//	Number(ScenePtr scene, int x, int y);
//
//	void setCurrentNumber(int current_number);
//
//	void changeImage();
//};
//
//class Score
//{
//	Number* number[4];
//
//	const int NUMBER_INDEX;
//
//	static int score;
//
//public:
//	Score(ScenePtr scene);
//
//	void setScoreZero();
//	void updateNumber();
//	void increase(int score);
//};
//
//class TreasureNumber
//{
//	Number* number[2];
//
//	const int NUMBER_INDEX;
//
//public:
//	TreasureNumber();
//
//	void updateNumber();
//};
//
//class CoinNumber : public TreasureNumber
//// coin, gem은 scene1에만 존재합니다
//{
//	static int holding_coin;
//
//public:
//	CoinNumber();
//
//	int getHoldingCoin();
//
//	void setHoldingCoinZero();
//	void holdingCoinIncrease();
//};
//
//class GreenGemNumber : public TreasureNumber
//{
//	static int holding_green_gem;
//
//public:
//	GreenGemNumber();
//
//	void getHoldingGreenGem();
//
//	void setHoldingGreenGemZero();
//	void holdingGreenGemIncrease();
//};
//
//class RedGemNumber : public TreasureNumber
//{
//	static int holding_coin;
//
//public:
//	RedGemNumber();
//
//	void getHoldingRedGem();
//
//	void setHoldingRedGemZero();
//	void holdingRedGemIncrease();
//};