#include "StrongDemon.h"

StrongDemon::StrongDemon()
{
}

StrongDemon::~StrongDemon()
{
}

void StrongDemon::init(float speed, glm::vec2 position)
{
	_speed = speed;
	_position = position;
	_life = 15;
}
