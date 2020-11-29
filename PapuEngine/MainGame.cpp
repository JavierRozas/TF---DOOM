#include <iostream>
#include <random>
#include <ctime>
#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include "ResourceManager.h"
#include "PapuEngine.h"


using namespace std;

void MainGame::run() {
	init();
	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Engine", _witdh, _height, 0);
	initShaders();
	initLevel();

}

void MainGame::initLevel() {
	_levels.push_back(new Level("Levels/level1.txt"));
	_player = new Player();
	_currentLevel = 0;
	_player->init(0.2f, 
				_levels[_currentLevel]->getPlayerPosition(), &_inputManager);
	_spriteBacth.init();

	// Zombies;
	const std::vector<glm::vec2>& zombiesPosition =
		_levels[_currentLevel]->getZombiesPosition();

	// Objects:
	const std::vector<glm::vec2>& objectPosition =
		_levels[_currentLevel]->getObjectPosition();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(1,_levels[_currentLevel]->getWidth() -2);
	std::uniform_int_distribution<int>randPosY(1, _levels[_currentLevel]->getHeight() - 2);
	/*
	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngine) * TILE_WIDTH,
			randPosY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(1.0f, pos);
	}*/

	for (size_t i = 0; i < zombiesPosition.size(); i++)
	{	
		_zombies.push_back(new Zombie());
		_zombies.back()->init(0.05f, zombiesPosition[i]);
	}

	for (size_t i = 0; i < objectPosition.size(); i++)
	{
		_objects.push_back(new PowerUp());
		_objects.back()->init(0.2f, objectPosition[i]);
	}
}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();
	_levels[_currentLevel]->draw();
	_player->draw(_spriteBacth, 0);

	/*for (size_t i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_spriteBacth, 0);
	}*/
	for (size_t i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_spriteBacth, 1);
	}
	for (size_t i = 0; i < _objects.size(); i++)
	{
		_objects[i]->draw(_spriteBacth, 2);
	}
	for (size_t i = 0; i < _proyectiles.size(); i++){
		_proyectiles[i]->draw(_spriteBacth, 3);
	}
	_spriteBacth.end();
	_spriteBacth.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	_program.unuse();
	_window.swapBuffer();
}


void MainGame::procesInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(event.motion.x,event.motion.y);
			break;
			case  SDL_KEYUP:
				_inputManager.releaseKey(event.key.keysym.sym);
				break;
			case  SDL_KEYDOWN:
				_inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(event.button.button);
				break;
		}

		/*if (_inputManager.isKeyPressed(SDLK_w)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
		}*/
		if (_inputManager.isKeyPressed(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords =  _camera.convertScreenToWorl(_inputManager.getMouseCoords());
			//cout << mouseCoords.x << " " << mouseCoords.y << endl;
		}
		if (_inputManager.isKeyPressed(SDLK_x)) {
			//CREAR BALA E INICIALIZAR
			_proyectiles.push_back(new Proyectil());
			_proyectiles.back()->init(0.5f, _player->getPosition(),_player->getlastkey());
		}
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		_camera.update();
		_time += 0.002f;
		_player->update(_levels[_currentLevel]->getLevelData(),_humans,_zombies);
		_camera.setPosition(_player->getPosition());
		/*for (size_t i = 0; i < _humans.size(); i++)
		{
			_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
			for (size_t j = i+1; j < _humans.size(); j++) {
				if (_humans[i]->collideWithAgent(_humans[j])) {
						_humans[i]->randir();
						_humans[j]->randir();
				}
			}
			if (_humans[i]->collideWithAgent(_player)) {
				_humans[i]->randir();
			}
		}*/

		for (size_t i = 0; i < _zombies.size(); i++)
		{
			//_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies, _player);
			if (_zombies[i]->collideWithAgent(_player)) {
				_player->resetposition(_levels, _currentLevel);

			}

			_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
			Human* closeHuman = _player;
			if (closeHuman != nullptr) {
				glm::vec2 direction = glm::normalize(
					closeHuman->getPosition() - _zombies[i]->getPosition()
				);
				_zombies[i]->setPosition(_zombies[i]->getPosition() += direction * _zombies[i]->getspeed());
			}
			/*for (size_t j = 0; j < _humans.size(); j++) {
				if (_zombies[i]->collideWithAgent(_humans[j])) {
					Zombie* z = new Zombie();
					z->init(1.0f, _humans[j]->getPosition());
					_zombies.push_back(z);
					_humans.erase(_humans.begin() + j);
				}
			}*/
			//CADA ZOMBIE VERIFICA SI CHOCÓ CON UN PROYECTIL
			for (size_t j = 0; j < _proyectiles.size(); j++){
				if(_zombies[i]->collideWithAgent(_proyectiles[j])){
					_proyectiles.erase(_proyectiles.begin() + j);
					_zombies.erase(_zombies.begin() + i);
				}
			}
			//CADA ZOMBIE VERIFICA SI CHOCÓ CON OTRO ZOMBIE:
			for (size_t j = i+1; j < _zombies.size(); j++) {
				if (_zombies[i]->collideWithAgent(_zombies[j])) {
						_zombies[i]->randir();
						_zombies[j]->randir();
				}
			}
		}
		for (size_t i = 0; i < _objects.size(); i++)
		{
			_objects[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
		}
		for (size_t i = 0; i < _proyectiles.size(); i++)
		{
			_proyectiles[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
			//ELIMINO PROYECTIL SI CHOCA CON LA PARED
			if(_proyectiles[i]->collideWithLevel(_levels[_currentLevel]->getLevelData())){
				_proyectiles.erase(_proyectiles.begin() + i);
			}
		}		
	}
}


MainGame::MainGame(): 
					  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0)
{
	_camera.init(_witdh, _height);
}


MainGame::~MainGame()
{
}
