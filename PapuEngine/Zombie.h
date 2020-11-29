#pragma once
#include "Agent.h"
#include "Player.h"

class Zombie : public Agent
{
protected:
	glm::vec2 direction;
	int _life;
public:
	Zombie();
	~Zombie();
	void init(float speed, glm::vec2 position);
	void setPosition(glm::vec2 position);
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans, std::vector<Zombie*>& zombies);
	Human* getNearestHuman(std::vector<Human*>& humans);
	void randir();
	int get_life();
};

