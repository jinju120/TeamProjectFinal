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