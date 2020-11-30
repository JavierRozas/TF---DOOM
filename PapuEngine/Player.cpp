#include "Player.h"
#include <SDL/SDL.h>
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(float speed, glm::vec2 position,
	InputManager* inputManager)
{
	_speed = speed;
	_position = position;
	_color.set(255, 255, 255, 255);
	_inputManager = inputManager;
	_lastkey = 'w';
	danio = 1;
	vida = 10;
	skin = 0;
	bulletskin = 3;
	boosted = false;
	boosttime = 1000;
}

void Player::update(const std::vector<std::string>& levelData) {
	if (_inputManager->isKeyPressed(SDLK_w)) {
		_position.y += _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_s)) {
		_position.y -= _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_a)) {
		_position.x -= _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_d)) {
		_position.x += _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_UP)) {
		_lastkey = 'w';
	}
	if (_inputManager->isKeyPressed(SDLK_DOWN)) {
		_lastkey = 's';
	}
	if (_inputManager->isKeyPressed(SDLK_LEFT)) {
		_lastkey = 'a';
	}
	if (_inputManager->isKeyPressed(SDLK_RIGHT)) {
		_lastkey = 'd';
	}
	collideWithLevel(levelData);
	// Agregado por mi
	//collideWithAgent(zombies.get_allocator);
}

char Player::getlastkey() {
	return _lastkey;
}

void Player::resetposition(std::vector<Level*> level, int currentLevel)
{
	_position = level[currentLevel]->getPlayerPosition();
}

void Player::boost() {
	srand(time(0));
	int r = rand() % (2);
	switch (r) {
	case 0: _speed = 5.0; skin = 4; break;
	case 1: danio = 5; bulletskin = 5; skin = 4; break;
	}
	boosted = true;
}

int Player::get_danio() {
	return danio;
}

int Player::get_vida()
{
	return vida;
}

void Player::set_vida(int vida)
{
	this->vida = vida;
}

int Player::get_skin()
{
	return skin;
}

void Player::set_skin(int _skin)
{
	skin = _skin;
}

int Player::getbulletskin()
{
	return bulletskin;
}

void Player::desgastarboost()
{
	if (boosted == true) {
		boosttime = boosttime - 1;
		if (boosttime < 0) {
			boosttime = 500;
			boosted = false;
			_speed = 1.2f;
			danio = 1;
			skin = 0;
			bulletskin = 3;
		}
	}
}

