#include "character.h"

extern ScenePtr scene;
const int START_POINT = 40, END_POINT = 1040;
const int FLOOR0 = 40, FLOOR1 = 190, FLOOR2 = 340, FLOOR3 = 490;
const int CLIMB_UP_FLOOR = 50;
const int FLOAT_SPACE = 20;

Character::Character()
	: jump_width{ 60, 82, 52 }, move_width{ 60, 80, 64, 40, 56, 80, 56, 40 }, CLIMB_WIDTH(36), STOP_WIDTH(40), climb_height{ 108, 112 },
	CLIMB_STEP(10), MOVE_STEP(20), JUMP_STEP(60), LONG_JUMP_STEP(90), CLIMB_IMG_NUM(2), MOVE_IMG_NUM(8), JUMP_IMG_NUM(3), RIGHT_JUMP_GAP(30),
	CLIMB_PATH("Images1/Character/climb"), MOVE_LEFT_PATH("Images1/Character/move-left"), MOVE_RIGHT_PATH("Images1/Character/move-right"),
	JUMP_LEFT_PATH("Images1/Character/jump-left"), JUMP_RIGHT_PATH("Images1/Character/jump-right"), STOP_PATH("Images1/Character/stop")
{
	x = START_POINT;
	y = FLOOR0;
	life_num = 3;
	current_floor = FLOOR0;
	current_jump_state = STOP;
	current_img_num = 0;
	current_direction = RIGHT;
	current_width = STOP_WIDTH;

	isMoving = false;
	isJumping = false;
	isLongJumping = false;
	isHoldingKey = false;
	isUpBlocked = true;
	isDownBlocked = true;

	current_path = "Images1/Character/stop-right.png";

	character = Object::create(current_path, scene, x, y);
	

	for (int i = 0; i < life_num; i++)
	{
		life[i] = Object::create("Images1/Object/life.png", scene, 1250 - 30 * i, 690);
	}
	
}

void Character::setIsUpBlocked(bool isUpBlocked)
{
	this->isUpBlocked = isUpBlocked;
}

void Character::setIsDownBlocked(bool isDownBlocked)
{
	this->isDownBlocked = isDownBlocked;
}

void Character::setCurrentFloor()
{
	if (y >= FLOOR0 && y < FLOOR1)
	{
		current_floor = FLOOR0;
	}
	else if (y >= FLOOR1 && y < FLOOR2)
	{
		current_floor = FLOOR1;
	}
	else if (y >= FLOOR2 && y < FLOOR3)
	{
		current_floor = FLOOR2;
	}
	else if (y >= FLOOR3)
	{
		current_floor = FLOOR3;
	}
}

bool Character::getIsMoving()
{
	return isMoving;
}

bool Character::getIsJumping()
{
	if (isJumping || isLongJumping)
	{
		return true;
	}

	return false;
}

bool Character::getIsHoldingKey()
{
	return isHoldingKey;
}

void Character::hide()
{
	character->hide();

	for (int i = 0; i < 3; i++)
		{
			life[i]->hide();
		}

}

void Character::climbUp()
{
	y += CLIMB_STEP;

	current_width = CLIMB_WIDTH;

	current_path = CLIMB_PATH + std::to_string(current_img_num++ % CLIMB_IMG_NUM + 1) + ".png";
}

void Character::climbDown()
{
	y -= CLIMB_STEP;

	current_width = CLIMB_WIDTH;

	current_path = CLIMB_PATH + std::to_string(current_img_num++ % CLIMB_IMG_NUM + 1) + ".png";
}

void Character::climbStop()
{
	current_img_num = 0;
	current_width = CLIMB_WIDTH;

	current_path = STOP_PATH + "-climb.png";
}

void Character::moveLeft()
{
	x -= MOVE_STEP;

	current_width = move_width[current_img_num % MOVE_IMG_NUM];

	current_path = MOVE_LEFT_PATH + std::to_string(current_img_num++ % MOVE_IMG_NUM + 1) + ".png";
}

void Character::moveRight()
{
	x += MOVE_STEP;

	current_width = move_width[current_img_num % MOVE_IMG_NUM];

	current_path = MOVE_RIGHT_PATH + std::to_string(current_img_num++ % MOVE_IMG_NUM + 1) + ".png";
}

void Character::stopLeft()
{
	current_img_num = 0;
	current_width = STOP_WIDTH;

	current_path = STOP_PATH + "-left.png";
}

void Character::stopRight()
{
	current_img_num = 0;
	current_width = STOP_WIDTH;

	current_path = STOP_PATH + "-right.png";
}

void Character::jumpLeftUp()
{
	x -= JUMP_STEP;
	y += MOVE_STEP;

	current_img_num = 0;
	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_LEFT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::jumpRightUp()
{
	x += JUMP_STEP - RIGHT_JUMP_GAP / 2;
	y += MOVE_STEP;

	current_img_num = 0;
	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_RIGHT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::longJumpLeftUp()
{
	x -= LONG_JUMP_STEP;
	y += MOVE_STEP;

	current_img_num = 0;
	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_LEFT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::longJumpRightUp()
{
	x += LONG_JUMP_STEP - RIGHT_JUMP_GAP / 2;
	y += MOVE_STEP;

	current_img_num = 0;
	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_RIGHT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::jumpLeftDown()
{
	x -= JUMP_STEP;
	y -= MOVE_STEP;

	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_LEFT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::jumpRightDown()
{
	x += JUMP_STEP - RIGHT_JUMP_GAP / 2;
	y -= MOVE_STEP;

	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_RIGHT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::longJumpLeftDown()
{
	x -= LONG_JUMP_STEP;
	y -= MOVE_STEP;

	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_LEFT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::longJumpRightDown()
{
	x += LONG_JUMP_STEP - RIGHT_JUMP_GAP / 2;
	y -= MOVE_STEP;

	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_RIGHT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::landLeft()
{
	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_LEFT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::landRight()
{
	x += RIGHT_JUMP_GAP;

	current_width = jump_width[current_img_num % JUMP_IMG_NUM];

	current_path = JUMP_RIGHT_PATH + std::to_string(current_img_num++ % JUMP_IMG_NUM + 1) + ".png";
}

void Character::blocked()
{
	if (x < START_POINT)
	{
		x = START_POINT;
	}
	else if (x > END_POINT - current_width)
	{
		x = END_POINT - current_width;
	}
}

void Character::move(int direction)
{
	switch (direction)
	{
	case UP:
		if (isUpBlocked)
		{
			return;
		}
		climbUp();
		setCurrentFloor();
		break;
	case DOWN:
		if (isDownBlocked)
		{
			return;
		}
		climbDown();
		setCurrentFloor();
		break;
	case LEFT:
		if (isClimbingLadder())
		{
			return;
		}
		moveLeft();
		break;
	case RIGHT:
		if (isClimbingLadder())
		{
			return;
		}
		moveRight();
		break;
	}

	blocked();

	character->setImage(current_path);
	character->locate(scene, x, y);

	isMoving = true;

	current_direction = direction;
}

void Character::moveStop()
{
	isMoving = false;

	if (isJumping || isLongJumping)
	{
		return;
	}

	switch (current_direction)
	{
	case UP:
	case DOWN:
		climbStop();
		break;
	case LEFT:
		if (isClimbingLadder())
		{
			return;
		}
		stopLeft();
		break;
	case RIGHT:
		if (isClimbingLadder())
		{
			return;
		}
		stopRight();
		break;
	}

	character->setImage(current_path);
}

void Character::jumpUp()
{
	if (isMoving)
	{
		switch (current_direction)
		{
		case UP:
		case DOWN:
			return;
		case LEFT:
			longJumpLeftUp();
			break;
		case RIGHT:
			longJumpRightUp();
			break;
		}

		isLongJumping = true;
	}
	else if (!isMoving)
	{
		switch (current_direction)
		{
		case UP:
		case DOWN:
			return;
		case LEFT:
			jumpLeftUp();
			break;
		case RIGHT:
			jumpRightUp();
			break;
		}

		isJumping = true;
	}

	blocked();

	character->setImage(current_path);
	character->locate(scene, x, y);
}

void Character::jumpDown()
{
	if (isLongJumping)
	{
		switch (current_direction)
		{
		case LEFT:
			longJumpLeftDown();
			break;
		case RIGHT:
			longJumpRightDown();
			break;
		}
	}
	else if (isJumping)
	{
		switch (current_direction)
		{
		case LEFT:
			jumpLeftDown();
			break;
		case RIGHT:
			jumpRightDown();
			break;
		}
	}

	blocked();

	character->setImage(current_path);
	character->locate(scene, x, y);
}

void Character::land()
{
	switch (current_direction)
	{
	case LEFT:
		landLeft();
		break;
	case RIGHT:
		landRight();
		break;
	}

	blocked();

	character->setImage(current_path);
	character->locate(scene, x, y);
}

void Character::jumpStop()
{
	isJumping = false;
	isLongJumping = false;

	switch (current_direction)
	{
	case LEFT:
		stopLeft();
		break;
	case RIGHT:
		stopRight();
		break;
	}

	character->setImage(current_path);
}

void Character::fall()
{
	if (y == FLOOR1)
	{
		y = FLOOR0;
		current_floor = FLOOR0;
	}
	else if (y == FLOOR2)
	{
		y = FLOOR1;
		current_floor = FLOOR0;
	}
	else if (y == FLOOR3)
	{
		y = FLOOR2;
		current_floor = FLOOR0;
	}

	character->locate(scene, x, y);
}

void Character::lifeDecrease()
{
	life[--life_num]->hide();
	
}

void Character::blink(int counter)
{
	if (counter % 2 == 0)
	{
		character->hide();
	}
	else if (counter % 2 == 1)
	{
		character->show();
	}
}

void Character::getCoin(Treasure* coin)
{
	if (!coin->getIsExist())
	{
		return;
	}

	coin->obtained();
}

void Character::getGreenGem(Treasure* green_gem)
{
	if (!green_gem->getIsExist())
	{
		return;
	}

	green_gem->obtained();
}

void Character::getRedGem(Treasure* red_gem)
{
	if (!red_gem->getIsExist())
	{
		return;
	}

	red_gem->obtained();
}

void Character::getKey(Key* key)
{
	if (!key->getIsExist())
	{
		return;
	}

	isHoldingKey = true;

	key->obtained();
}

void Character::openBox(Box* box)
{
	if (!box->getIsNotOpened())
	{
		return;
	}

	box->Opened();
}

bool Character::isClimbingLadder()
{
	if (y == FLOOR0 || y == FLOOR1 || y == FLOOR2 || y == FLOOR3)
	{
		return false;
	}

	return true;
}

bool Character::isLifeNumZero()
{
	if (life_num == 0)
	{
		return true;
	}

	return false;
}

bool Character::isCollideEnemy(Enemy* enemy)
{
	int enemy_x = enemy->getX();
	int enemy_y = enemy->getY();
	int enemy_floor = enemy->getFloor();
	int enemy_width = enemy->getCurrentWidth();
	int enemy_height = enemy->getCurrentHeight();

	if (current_floor != enemy_floor)
	{
		return false;
	}

	if (y > enemy_y + enemy_height)
	{
		return false;
	}

	if (x >= enemy_x && x <= enemy_x + enemy_width)
	{
		return true;
	}
	else if (x + current_width >= enemy_x && x + current_width <= enemy_x + enemy_width)
	{
		return true;
	}

	return false;
}

bool Character::isCollideEnemy(Bee* enemy)
{
	int enemy_x = enemy->getX();
	int enemy_y = enemy->getY();
	int enemy_floor = enemy->getFloor();
	int enemy_width = enemy->getCurrentWidth();
	int enemy_height = enemy->getCurrentHeight();

	if (!enemy->getIsFree())
	{
		return false;
	}

	if (current_floor != enemy_floor)
	{
		return false;
	}

	if (y > enemy_y + enemy_height)
	{
		return false;
	}

	if (x >= enemy_x && x <= enemy_x + enemy_width)
	{
		return true;
	}
	else if (x + current_width >= enemy_x && x + current_width <= enemy_x + enemy_width)
	{
		return true;
	}

	return false;
}

bool Character::isEntrapped(Thing* thing)
{
	int thing_x = thing->getX();
	int thing_floor = thing->getFloor();
	int thing_width = thing->getWidth();
	int margin = 15;

	if (y != thing_floor)
	{
		return false;
	}

	if (x >= thing_x + margin && x <= thing_x + thing_width - margin)
	{
		return true;
	}
	else if (x + current_width >= thing_x + margin && x + current_width <= thing_x + thing_width - margin)
	{
		return true;
	}
	else if (thing_x + margin >= x && thing_x + margin <= x + current_width)
	{
		return true;
	}
	else if (thing_x + thing_width - margin >= x && thing_x + thing_width - margin <= x + current_width)
	{
		return true;
	}

	return false;
}

bool Character::isContactThing(Thing* thing)
{
	int thing_x = thing->getX();
	int thing_floor = thing->getFloor();
	int thing_width = thing->getWidth();
	int margin = 5;

	if (current_floor != thing_floor)
	{
		return false;
	}

	if (x >= thing_x - margin && x <= thing_x + thing_width + margin)
	{
		return true;
	}
	else if (x + current_width >= thing_x - margin && x + current_width <= thing_x + thing_width + margin)
	{
		return true;
	}
	else if (thing_x - margin >= x && thing_x - margin <= x + current_width)
	{
		return true;
	}
	else if (thing_x + thing_width + margin >= x && thing_x + thing_width + margin <= x + current_width)
	{
		return true;
	}

	return false;
}

bool Character::isContactLadder(Ladder* ladder)
{
	int ladder_x = ladder->getX();
	int ladder_y = ladder->getFloor();
	int ladder_width = ladder->getWidth();
	int ladder_height = ladder->getHeight();

	if (y <= ladder_y || y >= ladder_y + ladder_height)
	{
		return false;
	}

	if (x >= ladder_x && x <= ladder_x + ladder_width)
	{
		return true;
	}
	else if (x + current_width >= ladder_x && x + current_width <= ladder_x + ladder_width)
	{
		return true;
	}

	return false;
}

bool Character::isContactUpLadder(Ladder* ladder)
{
	int ladder_x = ladder->getX();
	int ladder_y = ladder->getFloor();
	int ladder_width = ladder->getWidth();
	int ladder_height = ladder->getHeight();

	if (y != ladder_y)
	{
		return false;
	}

	if (x >= ladder_x && x <= ladder_x + ladder_width)
	{
		return true;
	}
	else if (x + current_width >= ladder_x && x + current_width <= ladder_x + ladder_width)
	{
		return true;
	}

	return false;
}

bool Character::isContactDownLadder(Ladder* ladder)
{
	int ladder_x = ladder->getX();
	int ladder_y = ladder->getFloor();
	int ladder_width = ladder->getWidth();
	int ladder_height = ladder->getHeight();

	if (y != ladder_y + ladder_height)
	{
		return false;
	}

	if (x >= ladder_x && x <= ladder_x + ladder_width)
	{
		return true;
	}
	else if (x + current_width >= ladder_x && x + current_width <= ladder_x + ladder_width)
	{
		return true;
	}

	return false;
}

bool Character::isStepEmptyFloor(Flooring* flooring)
{
	int center = x + current_width / 2;
	int flooring_x = flooring->getX();
	int flooring_floor = flooring->getFloor();
	int flooring_width = flooring->getWidth();
	int margin = 3;

	if (flooring->getIsExist())
	{
		return false;
	}

	if (y != flooring_floor)
	{
		return false;
	}

	if ((center - margin >= flooring_x && center - margin <= flooring_x + flooring_width))
	{
		return true;
	}

	return false;
}

