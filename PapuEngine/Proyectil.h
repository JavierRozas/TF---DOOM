#pragma once
#include "Agent.h"

class Proyectil : public Agent
{
protected:
	glm::vec2 _direction;
public:
	Proyectil();
	~Proyectil();
	void update(const std::vector<std::string>& levelData);
	void setColor();
	glm::vec2 getPosition();
	void init(float speed, glm::vec2 position, char dir);
	bool specialcollide(const std::vector<std::string>& levelData);
};

