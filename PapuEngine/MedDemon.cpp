#include "MedDemon.h"

MedDemon::MedDemon()
{
}

MedDemon::~MedDemon()
{
}

void MedDemon::init(float speed, glm::vec2 position)
{
	_speed = speed;
	_position = position;
	_life = 10;
	atacktime = 100;
	atackin = false;
	danio = 2;
}
