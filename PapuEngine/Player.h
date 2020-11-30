#pragma once
#include "Human.h"
#include "Level.h"
#include "InputManager.h"
#include "Demonio.h"
class Player : public Human
{
private:
	InputManager* _inputManager;
	char _lastkey;
	int danio;
	int vida;
public:
	Player();
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans, std::vector<Demonio*>& zombies);
	~Player();
	void init(float speed, glm::vec2 position, InputManager* inputManager);
	char getlastkey();
	void resetposition(std::vector<Level*> level, int currentLevel);
	void boost();
	int get_danio();
	int get_vida();
	void set_vida(int vida);
};

