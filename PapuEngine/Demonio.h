#pragma once
#include "Agent.h"
#include "Player.h"

class Demonio : public Agent
{
protected:
	glm::vec2 direction;
	int _life;
public:
	Demonio();
	~Demonio();
	void init(float speed, glm::vec2 position);
	void setPosition(glm::vec2 position);
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans, std::vector<Demonio*>& dominios);
	//Human* getNearestHuman(std::vector<Human*>& humans);
	void randir();
	int get_life();
	void inflict(int i);
};

