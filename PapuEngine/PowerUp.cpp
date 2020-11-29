#include "PowerUp.h"
#include "Zombie.h"
#include "Human.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>

PowerUp::PowerUp()
{
}

void PowerUp::init(float speed, glm::vec2 position)
{
	_speed = speed;
	_position = position;
	// _color.set(185, 0, 0, 255);
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);

	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (_direction.length() == 0) {
		_direction = glm::vec2(1.0f, 1.0f);
	}

}

void PowerUp::setColor()
{
	_color.set(0, 255, 0, 255);
}

glm::vec2 PowerUp::getPosition()
{
	return _position;
}

void PowerUp::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	_position += _direction * _speed;
	if (collideWithLevel(levelData)) {
		_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	}

	// Colision con un 'PowerUp':
	for (size_t i = 0; i < humans.size(); i++)
	{

		// Verificar si hay colision:
		if (collideWithAgent(humans[i]))
		{
			// humans[i]->setColor();
			// Eliminar Humano del arreglo 'humans'
			humans.erase(humans.begin() + i);
		}
	}

}


PowerUp::~PowerUp()
{
}