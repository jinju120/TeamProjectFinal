﻿#include "character.h"
#include "enemy.h"
#include "thing.h"
/*
	TODO
	보스전이 추가될 것입니다(공격 이미지가 필요합니다.).
	점수 계산이 필요합니다.
*/

ScenePtr none = Scene::create("GameStart", "Images1/none.png");
ScenePtr scene = Scene::create("TeamProject", "Images1/background.png");
SoundPtr background_music;
TimerPtr check_timer, damaged_check_timer;
TimerPtr blink_timer, climb_timer, move_timer, jump_down_timer, land_timer, stop_timer;
TimerPtr enemy_timer;
ObjectPtr start_button;
ObjectPtr quit_button;
ObjectPtr explanation;
ObjectPtr stage;

Character* main_char;
Spider* spider[2];
Bee* bee[2];
Thing* door;
Thing* trap[10];
Ladder* ladder[10];
Flooring* floor1[50];
Flooring* floor2[50];
Flooring* floor3[50];
Treasure* coin[5];
Treasure* green_gem[2];
Treasure* red_gem[2];
Key* key;
Box* box[3];

int Character::holding_coin = 0;
int Character::holding_green_gem = 0;
int Character::holding_red_gem = 0;

int ladder_num;
int trap_num;
int blink_counter = 0;
int current_code;
int current_stage = STAGE1;

const int START_POINT = 40, END_POINT = 1040;
const int FLOOR0 = 40, FLOOR1 = 190, FLOOR2 = 340, FLOOR3 = 490;
const int FLOORING_NUM = 50;
const int FLOORING_WIDTH = 20;
const int COIN_NUM = 5, GEM_NUM = 2, BOX_NUM = 3;
const int SPIDER_NUM = 2;
const int BEE_NUM = 2;
const float CHECK_TIME = 0.2f;
const float CLIMB_TIME = 0.2f, MOVE_TIME = 0.1f, JUMP_TIME = 0.15f, LAND_TIME = 0.2f, STOP_TIME = 0.1f, BLINK_TIME = 0.2f;
const float ENEMY_TIME = 0.1f;

bool isPlaying;
bool isKeyPressed;

void initGame();
void stageOne();
void stageTwo();
void stageThree();
void bossStage();
void deletePtr();
void nextStage();
void gameOver();

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	initGame();
	startGame(none);
}

void initGame()
{
	background_music = Sound::create("Sounds/background-music.mp3");
	background_music->play();

	scene->setOnKeyboardCallback([&](ScenePtr scene, KeyCode code, bool pressed)->bool {
		if (!isPlaying)
		{
			return true;
		}

		if (pressed)
		{
			if (main_char->getIsJumping())
			{
				return true;
			}
		}

		if (code == KeyCode::KEY_UP_ARROW)
		{
			if (pressed)
			{
				current_code = UP;
				main_char->move(current_code);

				climb_timer->set(CLIMB_TIME);
				climb_timer->start();
			}
			else
			{
				main_char->moveStop();

				climb_timer->stop();
			}
		}
		else if (code == KeyCode::KEY_DOWN_ARROW)
		{
			if (pressed)
			{
				current_code = DOWN;
				main_char->move(current_code);

				climb_timer->set(CLIMB_TIME);
				climb_timer->start();
			}
			else
			{
				main_char->moveStop();

				climb_timer->stop();
			}
		}
		else if (code == KeyCode::KEY_LEFT_ARROW)
		{
			if (pressed)
			{
				current_code = LEFT;
				main_char->move(current_code);

				move_timer->set(MOVE_TIME);
				move_timer->start();
			}
			else
			{
				main_char->moveStop();

				move_timer->stop();
			}
		}
		else if (code == KeyCode::KEY_RIGHT_ARROW)
		{
			if (pressed)
			{
				current_code = RIGHT;
				main_char->move(current_code);

				move_timer->set(MOVE_TIME);
				move_timer->start();
			}
			else
			{
				main_char->moveStop();

				move_timer->stop();
			}
		}
		else if (code == KeyCode::KEY_SPACE)
		{
			if (pressed)
			{
				move_timer->stop();

				main_char->jumpUp();

				jump_down_timer->set(JUMP_TIME);
				jump_down_timer->start();
			}
		}

		return true;
		});

	none->setOnKeyboardCallback([&](ScenePtr none, KeyCode code, bool pressed)->bool {
		if (code == KeyCode::KEY_ENTER)
		{
			if (current_stage == STAGE1)
			{
				current_stage = STAGE2;
				scene->enter();
				stageTwo();
			}
			else if (current_stage == STAGE2)
			{
				current_stage = STAGE3;
				scene->enter();
				stageThree();
			}
		}

		return true;
		});

	check_timer = Timer::create(CHECK_TIME);
	check_timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		bool isCharacterContactLadder[10];

		for (int i = 0; i < ladder_num; i++)
		{
			if (main_char->isContactLadder(ladder[i]))
			{
				main_char->setIsUpBlocked(false);
				main_char->setIsDownBlocked(false);

				isCharacterContactLadder[i] = true;
			}
			else if (main_char->isContactUpLadder(ladder[i]))
			{
				main_char->setIsUpBlocked(false);
				main_char->setIsDownBlocked(true);

				isCharacterContactLadder[i] = true;
			}
			else if (main_char->isContactDownLadder(ladder[i]))
			{
				main_char->setIsUpBlocked(true);
				main_char->setIsDownBlocked(false);

				isCharacterContactLadder[i] = true;
			}
			else
			{
				isCharacterContactLadder[i] = false;
			}
		}

		for (int i = 0; i < ladder_num; i++)
		{
			if (isCharacterContactLadder[i])
			{
				break;
			}

			if (i == ladder_num - 1)
			{
				main_char->setIsUpBlocked(true);
				main_char->setIsDownBlocked(true);
			}
		}

		if (main_char->isContactThing(door))
		{
			if (main_char->getIsHoldingKey())
			{
				nextStage();
			}
		}

		for (int i = 0; i < COIN_NUM; i++)
		{
			if (main_char->isContactThing(coin[i]))
			{
				main_char->getCoin(coin[i]);
			}
		}

		for (int i = 0; i < GEM_NUM; i++)
		{
			if (main_char->isContactThing(green_gem[i]))
			{
				main_char->getGreenGem(green_gem[i]);
			}
		}

		for (int i = 0; i < GEM_NUM; i++)
		{
			if (main_char->isContactThing(red_gem[i]))
			{
				main_char->getGreenGem(red_gem[i]);
			}
		}

		for (int i = 0; i < BOX_NUM; i++)
		{
			if (main_char->isContactThing(box[i]))
			{
				main_char->openBox(box[i]);
			}
		}

		if (main_char->isContactThing(key))
		{
			main_char->getKey(key);
		}

		if (main_char->isLifeNumZero())
		{
			gameOver();
		}

		timer->set(CHECK_TIME);
		timer->start();

		return true;
		});

	damaged_check_timer = Timer::create(CHECK_TIME);
	damaged_check_timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		for (int i = 0; i < FLOORING_NUM; i++)
		{
			if (main_char->isStepEmptyFloor(floor1[i]))
			{
				main_char->fall();

				main_char->lifeDecrease();

				blink_timer->set(BLINK_TIME);
				blink_timer->start();

				return true;
			}

			if (main_char->isStepEmptyFloor(floor2[i]))
			{
				main_char->fall();

				main_char->lifeDecrease();

				blink_timer->set(BLINK_TIME);
				blink_timer->start();

				return true;
			}

			if (main_char->isStepEmptyFloor(floor3[i]))
			{
				main_char->fall();

				main_char->lifeDecrease();

				blink_timer->set(BLINK_TIME);
				blink_timer->start();

				return true;
			}
		}

		for (int i = 0; i < SPIDER_NUM; i++)
		{
			if (main_char->isCollideEnemy(spider[i]))
			{
				main_char->lifeDecrease();
				
				blink_timer->set(BLINK_TIME);
				blink_timer->start();

				return true;
			}
		}

		for (int i = 0; i < BEE_NUM; i++)
		{
			if (main_char->isCollideEnemy(bee[i]))
			{
				main_char->lifeDecrease();

				blink_timer->set(BLINK_TIME);
				blink_timer->start();

				return true;
			}
		}

		for (int i = 0; i < trap_num; i++)
		{
			if (main_char->isEntrapped(trap[i]))
			{
				main_char->lifeDecrease();

				blink_timer->set(BLINK_TIME);
				blink_timer->start();

				return true;
			}
		}

		damaged_check_timer->set(CHECK_TIME);
		damaged_check_timer->start();

		return true;
		});

	blink_timer = Timer::create(BLINK_TIME);
	blink_timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		main_char->blink(blink_counter);

		if (blink_counter == 3)
		{
			blink_counter = 0;

			damaged_check_timer->set(CHECK_TIME);
			damaged_check_timer->start();
		}
		else
		{
			blink_counter++;

			blink_timer->set(BLINK_TIME);
			blink_timer->start();
		}

		return true;
		});

	climb_timer = Timer::create(CLIMB_TIME);
	climb_timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		main_char->move(current_code);

		timer->set(CLIMB_TIME);
		timer->start();

		return true;
		});

	move_timer = Timer::create(MOVE_TIME);
	move_timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		main_char->move(current_code);

		timer->set(MOVE_TIME);
		timer->start();

		return true;
		});

	jump_down_timer = Timer::create(JUMP_TIME);
	jump_down_timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		main_char->jumpDown();

		land_timer->set(JUMP_TIME);
		land_timer->start();

		return true;
		});

	land_timer = Timer::create(LAND_TIME);
	land_timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		main_char->land();

		stop_timer->set(STOP_TIME);
		stop_timer->start();

		return true;
		});

	stop_timer = Timer::create(STOP_TIME);
	stop_timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		main_char->jumpStop();

		if (main_char->getIsMoving())
		{
			move_timer->start();
		}

		return true;
		});

	enemy_timer = Timer::create(ENEMY_TIME);
	enemy_timer->setOnTimerCallback([&](TimerPtr timer)->bool {
		for (int i = 0; i < SPIDER_NUM; i++)
		{
			spider[i]->move();
		}

		for (int i = 0; i < BEE_NUM; i++)
		{
			bee[i]->move();
		}

		enemy_timer->set(ENEMY_TIME);
		enemy_timer->start();

		return true;
		});

	explanation = Object::create("Images2/Text/explanation.png", none);

	start_button = Object::create("Images2/Text/start.png", none, 450, 150);

	start_button->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		isPlaying = true;

		scene->enter();

		stageOne();

		check_timer->set(CHECK_TIME);
		check_timer->start();

		damaged_check_timer->set(CHECK_TIME);
		damaged_check_timer->start();

		enemy_timer->set(ENEMY_TIME);
		enemy_timer->start();

		return true;
		});

	quit_button = Object::create("Images2/Text/quit.png", none, 770, 150);

	quit_button->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		endGame();

		return true;
		});

	stage = Object::create("Images2/Text/stage1.png", scene, 10, 690);

	current_stage = STAGE1;
}

void stageOne()
{
	bool isFloor1Exist[FLOORING_NUM] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	bool isFloor2Exist[FLOORING_NUM] = {
		1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	bool isFloor3Exist[FLOORING_NUM] = {
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
	};

	for (int i = 0; i < FLOORING_NUM; i++)
	{
		floor1[i] = new Flooring(FLOORING, i * FLOORING_WIDTH + START_POINT, FLOOR1, isFloor1Exist[i]);
		floor2[i] = new Flooring(FLOORING, i * FLOORING_WIDTH + START_POINT, FLOOR2, isFloor2Exist[i]);
		floor3[i] = new Flooring(FLOORING, i * FLOORING_WIDTH + START_POINT, FLOOR3, isFloor3Exist[i]);
	}

	for (int i = 0; i < FLOORING_NUM; i++)
	{
		floor1[i]->setState();
		floor2[i]->setState();
		floor3[i]->setState();
	}

	door = new Thing(DOOR, 960, FLOOR3);

	ladder_num = 4;
	ladder[0] = new Ladder(LADDER, 600, FLOOR0);
	ladder[1] = new Ladder(LADDER, 260, FLOOR1);
	ladder[2] = new Ladder(LADDER, 880, FLOOR1);
	ladder[3] = new Ladder(LADDER, 500, FLOOR2);

	trap_num = 5;
	trap[0] = new Thing(TRAP, 450, FLOOR0);
	trap[1] = new Thing(TRAP, 700, FLOOR0);
	trap[2] = new Thing(TRAP, 540, FLOOR1);
	trap[3] = new Thing(TRAP, 800, FLOOR2);
	trap[4] = new Thing(TRAP, 60, FLOOR3);

	coin[0] = new Treasure(COIN, 550, FLOOR0);
	coin[1] = new Treasure(COIN, 100, FLOOR1);
	coin[2] = new Treasure(COIN, 580, FLOOR2);
	coin[3] = new Treasure(COIN, 140, FLOOR3);
	coin[4] = new Treasure(COIN, 560, FLOOR3);

	green_gem[0] = new Treasure(GREEN_GEM, 800, FLOOR0);
	green_gem[1] = new Treasure(GREEN_GEM, 820, FLOOR3);

	red_gem[0] = new Treasure(RED_GEM, 460, FLOOR1);
	red_gem[1] = new Treasure(RED_GEM, 70, FLOOR2);

	key = new Key(KEY, 420, FLOOR2);

	bee[0] = new Bee(160, FLOOR1);
	bee[1] = new Bee(640, FLOOR3);

	box[0] = new Box(BOX, 160, FLOOR1, bee[0]);
	box[1] = new Box(BOX, 420, FLOOR2, key);
	box[2] = new Box(BOX, 640, FLOOR3, bee[1]);

	spider[0] = new Spider(START_POINT, FLOOR1, BLACK);
	spider[1] = new Spider(1000, FLOOR2, BLACK);

	main_char = new Character();
}

void stageTwo()
{
	stage->setImage("Images2/Text/stage2.png");

	bool isFloor1Exist[FLOORING_NUM] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	bool isFloor2Exist[FLOORING_NUM] = {
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
	};
	bool isFloor3Exist[FLOORING_NUM] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
	};

	for (int i = 0; i < FLOORING_NUM; i++)
	{
		floor1[i] = new Flooring(FLOORING, i * FLOORING_WIDTH + START_POINT, FLOOR1, isFloor1Exist[i]);
		floor2[i] = new Flooring(FLOORING, i * FLOORING_WIDTH + START_POINT, FLOOR2, isFloor2Exist[i]);
		floor3[i] = new Flooring(FLOORING, i * FLOORING_WIDTH + START_POINT, FLOOR3, isFloor3Exist[i]);
	}

	for (int i = 0; i < FLOORING_NUM; i++)
	{
		floor1[i]->setState();
		floor2[i]->setState();
		floor3[i]->setState();
	}

	door = new Thing(DOOR, 20, FLOOR3);

	ladder_num = 6;
	ladder[0] = new Ladder(LADDER, 240, FLOOR0);
	ladder[1] = new Ladder(LADDER, 780, FLOOR0);
	ladder[2] = new Ladder(LADDER, 100, FLOOR1);
	ladder[3] = new Ladder(LADDER, 920, FLOOR1);
	ladder[4] = new Ladder(LADDER, 330, FLOOR2);
	ladder[5] = new Ladder(LADDER, 980, FLOOR2);

	trap_num = 5;
	trap[0] = new Thing(TRAP, 400, FLOOR0);
	trap[1] = new Thing(TRAP, 680, FLOOR0);
	trap[2] = new Thing(TRAP, 160, FLOOR1);
	trap[3] = new Thing(TRAP, 840, FLOOR1);
	trap[4] = new Thing(TRAP, 700, FLOOR3);

	coin[0] = new Treasure(COIN, 560, FLOOR0);
	coin[1] = new Treasure(COIN, 300, FLOOR1);
	coin[2] = new Treasure(COIN, 60, FLOOR2);
	coin[3] = new Treasure(COIN, 440, FLOOR2);
	coin[4] = new Treasure(COIN, 180, FLOOR3);

	green_gem[0] = new Treasure(GREEN_GEM, 950, FLOOR0);
	green_gem[1] = new Treasure(GREEN_GEM, 760, FLOOR2);

	red_gem[0] = new Treasure(RED_GEM, 620, FLOOR1);
	red_gem[1] = new Treasure(RED_GEM, 630, FLOOR3);

	key = new Key(KEY, 280, FLOOR2);

	bee[0] = new Bee(980, FLOOR1);
	bee[1] = new Bee(780, FLOOR3);

	box[0] = new Box(BOX, 980, FLOOR1, bee[0]);
	box[1] = new Box(BOX, 280, FLOOR2, key);
	box[2] = new Box(BOX, 780, FLOOR3, bee[1]);

	spider[0] = new Spider(START_POINT, FLOOR1, BLACK);
	spider[1] = new Spider(1000, FLOOR3, BLACK);

	main_char = new Character();
}

void stageThree()
{
	stage->setImage("Images2/Text/stage3.png");

	bool isFloor1Exist[FLOORING_NUM] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	bool isFloor2Exist[FLOORING_NUM] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 0, 1,
		1, 1, 0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
		1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
	};
	bool isFloor3Exist[FLOORING_NUM] = {
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 1, 1, 1,
	};

	for (int i = 0; i < FLOORING_NUM; i++)
	{
		floor1[i] = new Flooring(FLOORING, i * FLOORING_WIDTH + START_POINT, FLOOR1, isFloor1Exist[i]);
		floor2[i] = new Flooring(FLOORING, i * FLOORING_WIDTH + START_POINT, FLOOR2, isFloor2Exist[i]);
		floor3[i] = new Flooring(FLOORING, i * FLOORING_WIDTH + START_POINT, FLOOR3, isFloor3Exist[i]);
	}

	for (int i = 0; i < FLOORING_NUM; i++)
	{
		floor1[i]->setState();
		floor2[i]->setState();
		floor3[i]->setState();
	}

	door = new Thing(DOOR, 960, FLOOR0);

	ladder_num = 4;
	ladder[0] = new Ladder(LADDER, 590, FLOOR0);
	ladder[1] = new Ladder(LADDER, 300, FLOOR1);
	ladder[2] = new Ladder(LADDER, 80, FLOOR2);
	ladder[3] = new Ladder(LADDER, 830, FLOOR2);

	trap_num = 8;
	trap[0] = new Thing(TRAP, 160, FLOOR0);
	trap[1] = new Thing(TRAP, 300, FLOOR0);
	trap[2] = new Thing(TRAP, 440, FLOOR0);
	trap[3] = new Thing(TRAP, 750, FLOOR1);
	trap[4] = new Thing(TRAP, 930, FLOOR1);
	trap[5] = new Thing(TRAP, 220, FLOOR2);
	trap[6] = new Thing(TRAP, 320, FLOOR3);
	trap[7] = new Thing(TRAP, 460, FLOOR3);

	coin[0] = new Treasure(COIN, 240, FLOOR0);
	coin[1] = new Treasure(COIN, 800, FLOOR0);
	coin[2] = new Treasure(COIN, 80, FLOOR1);
	coin[3] = new Treasure(COIN, 480, FLOOR1);
	coin[4] = new Treasure(COIN, 700, FLOOR2);

	green_gem[0] = new Treasure(GREEN_GEM, 990, FLOOR1);
	green_gem[1] = new Treasure(GREEN_GEM, 150, FLOOR2);

	red_gem[0] = new Treasure(RED_GEM, 370, FLOOR0);
	red_gem[1] = new Treasure(RED_GEM, 990, FLOOR3);

	// 주석이 있는 것이 처음 기획했던 것이 맞습니다. 에러를 피하기 위해 중복된 코드가 존재합니다.
	//key = new Key(KEY, 400, FLOOR3);

	//box[0] = new Box(BOX, 700, FLOOR0);
	//box[1] = new Box(BOX, 560, FLOOR2);
	//box[2] = new Box(BOX, 900, FLOOR3);

	key = new Key(KEY, 280, FLOOR2);

	bee[0] = new Bee(980, FLOOR1);
	bee[1] = new Bee(780, FLOOR3);

	box[0] = new Box(BOX, 980, FLOOR1, bee[0]);
	box[1] = new Box(BOX, 280, FLOOR2, key);
	box[2] = new Box(BOX, 780, FLOOR3, bee[1]);

	spider[0] = new Spider(1000, FLOOR1, BLACK);
	spider[1] = new Spider(START_POINT, FLOOR3, BLACK);

	main_char = new Character();
}

void bossStage()
{

}

void deletePtr()
{
	for (int i = 0; i < FLOORING_NUM; i++)
	{
		floor1[i]->hide();
		floor2[i]->hide();
		floor3[i]->hide();

		delete floor1[i];
		delete floor2[i];
		delete floor3[i];
	}

	door->hide();
	delete door;

	for (int i = 0; i < ladder_num; i++)
	{
		ladder[i]->hide();
		delete ladder[i];
	}

	for (int i = 0; i < trap_num; i++)
	{
		trap[i]->hide();
		delete trap[i];
	}

	for (int i = 0; i < COIN_NUM; i++)
	{
		coin[i]->hide();
		delete coin[i];
	}

	for (int i = 0; i < GEM_NUM; i++)
	{
		green_gem[i]->hide();
		delete green_gem[i];
	}

	for (int i = 0; i < GEM_NUM; i++)
	{
		red_gem[i]->hide();
		delete red_gem[i];
	}

	key->hide();
	delete key;

	for (int i = 0; i < BOX_NUM; i++)
	{
		box[i]->hide();
		delete box[i];
	}

	for (int i = 0; i < SPIDER_NUM; i++)
	{
		spider[i]->hide();
		delete spider[i];
	}

	for (int i = 0; i < BEE_NUM; i++)
	{
		bee[i]->hide();
		delete bee[i];
	}

	main_char->hide();
	delete main_char;
}

void nextStage()
{
	check_timer->stop();
	damaged_check_timer->stop();
	blink_timer->stop();
	climb_timer->stop();
	move_timer->stop();
	jump_down_timer->stop();
	land_timer->stop();
	stop_timer->stop();
	enemy_timer->stop();

	deletePtr();

	none->enter();

	explanation->setImage("Images2/Text/next_stage.png");
	explanation->show();
	start_button->hide();
	quit_button->hide();
}

void gameOver()
{
	check_timer->stop();
	damaged_check_timer->stop();
	blink_timer->stop();
	climb_timer->stop();
	move_timer->stop();
	jump_down_timer->stop();
	land_timer->stop();
	stop_timer->stop();
	enemy_timer->stop();

	deletePtr();

	none->enter();

	explanation->setImage("Images2/Text/game_over.png");
	start_button->setImage("Images2/Text/restart.png");

	explanation->show();
	start_button->show();
	quit_button->show();
}