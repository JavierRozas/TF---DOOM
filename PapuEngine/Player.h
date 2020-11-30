#pragma once
#include "Level.h"
#include "InputManager.h"
#include "Demonio.h"
class Player : public Agent
{
private:
	InputManager* _inputManager;
	char _lastkey;
	int danio;
	int vida;
	int skin;
	int bulletskin;
	bool boosted;
	int boosttime;
public:
	Player();
	void update(const std::vector<std::string>& levelData);
	~Player();
	void init(float speed, glm::vec2 position, InputManager* inputManager);
	char getlastkey();
	void resetposition(std::vector<Level*> level, int currentLevel);
	void boost();
	int get_danio();
	int get_vida();
	void set_vida(int vida);
	int get_skin();
	void set_skin(int _skin);
	int getbulletskin();
	void desgastarboost();
};

