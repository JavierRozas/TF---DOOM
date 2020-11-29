#include "Player.h"
#include <SDL/SDL.h>

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
	_color.set(0, 0, 185, 255);
	_inputManager = inputManager;
	_lastkey = 'w';
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {
	if (_inputManager->isKeyPressed(SDLK_w)) {
		_position.y += _speed;
		_lastkey = 'w';
	}
	if (_inputManager->isKeyPressed(SDLK_s)) {
		_position.y -= _speed;
		_lastkey = 's';
	}
	if (_inputManager->isKeyPressed(SDLK_a)) {
		_position.x -= _speed;
		_lastkey = 'a';
	}
	if (_inputManager->isKeyPressed(SDLK_d)) {
		_position.x += _speed;
		_lastkey = 'd';
	}
	collideWithLevel(levelData);
	// Agregado por mi
	//collideWithAgent(zombies.get_allocator);
}

char Player::getlastkey(){
	return _lastkey;
}