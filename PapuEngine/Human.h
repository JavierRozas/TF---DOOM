#pragma once
#include "Agent.h"
class Human : public Agent
{
protected:
	glm::vec2 _direction;

public:
	Human();
	~Human();
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans, std::vector<Demonio*>& zombies);
	void setColor();
	glm::vec2 getPosition();
	float getspeed();
	void init(float speed, glm::vec2 position);
	void randir();
};

