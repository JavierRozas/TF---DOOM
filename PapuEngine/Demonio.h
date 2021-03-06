#pragma once
#include "Agent.h"
#include "Player.h"

class Demonio : public Agent
{
protected:
	glm::vec2 direction;
	int _life;
	bool atackin;
	int atacktime;
	int danio;
public:
	Demonio();
	~Demonio();
	virtual void init(float speed, glm::vec2 position);
	void setPosition(glm::vec2 position);
	void update(const std::vector<std::string>& levelData);
	//Human* getNearestHuman(std::vector<Human*>& humans);
	void randir();
	int get_life();
	void inflict(int i);
	bool getatackin();
	void setatackin(bool _atackin);
	void atacando();
	int getdanio();
};

