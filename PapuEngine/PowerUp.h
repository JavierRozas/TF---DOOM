#pragma once
#include "Agent.h"

class PowerUp : public Agent
{
protected:
	glm::vec2 _direction;
public:
	PowerUp();
	~PowerUp();
	void update(const std::vector<std::string>& levelData);
	void setColor();
	glm::vec2 getPosition();
	void init(float speed, glm::vec2 position);
};


