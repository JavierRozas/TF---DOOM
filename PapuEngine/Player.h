#pragma once
#include "Human.h"
#include "InputManager.h"
class Player : public Human
{
private:
	InputManager* _inputManager;
	char _lastkey;
public:
	Player();
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans, std::vector<Zombie*>& zombies);
	~Player();
	void init(float speed, glm::vec2 position, InputManager* inputManager);
	char getlastkey();
};

