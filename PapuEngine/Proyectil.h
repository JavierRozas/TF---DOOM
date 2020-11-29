#pragma once
#include "Agent.h"

class Proyectil : public Agent
{
protected:
	glm::vec2 _direction;
	int _da�o;
public:
    Proyectil();
	~Proyectil();
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans, std::vector<Zombie*>& zombies);
	void setColor();
	glm::vec2 getPosition();
	void init(float speed, glm::vec2 position, char dir);
	int get_da�o();
};

