#include "LowDemon.h"

LowDemon::LowDemon()
{
}

LowDemon::~LowDemon()
{
}

void LowDemon::init(float speed, glm::vec2 position)
{
	_speed = speed;
	_position = position;
	_life = 5;
	atacktime = 100;
	atackin = false;
	danio = 1;
}
