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
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans, std::vector<Demonio*>& zombies) {
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
	case 0: _speed += 0.3; break;
	case 1: danio += 2; break;
	}
}

int Player::get_danio() {
	return danio;
}
