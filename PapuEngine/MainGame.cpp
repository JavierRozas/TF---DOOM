#include <iostream>
#include <random>
#include <ctime>
#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include "ResourceManager.h"
#include "PapuEngine.h"

// Para Agregar Sonido:
#include <Windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

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

void MainGame::addMusic(const char *song) {
	PlaySound(song, NULL, SND_ASYNC);
}

void MainGame::initLevel() {
	_levels.push_back(new Level("Levels/level1.txt"));
	_player = new Player();
	_currentLevel = 0;
	tiempo_recarga_balas = 30;
	bala_recargando = false;
	_player->init(1.2f,
		_levels[_currentLevel]->getPlayerPosition(), &_inputManager);
	_spriteBacth.init();

	// Demonios Fuertes;
	const std::vector<glm::vec2>& strongdemonsPosition =
		_levels[_currentLevel]->getSDemoniosPosition();

	// Demonios Medios;
	const std::vector<glm::vec2>& meddemonsPosition =
		_levels[_currentLevel]->getMDemoniosPosition();

	// Demonios Debiles;
	const std::vector<glm::vec2>& lowdemonsPosition =
		_levels[_currentLevel]->getLDemoniosPosition();

	// Objects:
	const std::vector<glm::vec2>& objectPosition =
		_levels[_currentLevel]->getObjectPosition();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(1, _levels[_currentLevel]->getWidth() - 2);
	std::uniform_int_distribution<int>randPosY(1, _levels[_currentLevel]->getHeight() - 2);
	/*
	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngine) * TILE_WIDTH,
			randPosY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(1.0f, pos);
	}*/

	for (size_t i = 0; i < strongdemonsPosition.size(); i++)
	{
		strongdemons.push_back(new StrongDemon());
		strongdemons.back()->init(1.0f, strongdemonsPosition[i]);
	}

	for (size_t i = 0; i < meddemonsPosition.size(); i++)
	{
		meddemons.push_back(new MedDemon());
		meddemons.back()->init(1.0f, meddemonsPosition[i]);
	}

	for (size_t i = 0; i < lowdemonsPosition.size(); i++)
	{
		lowdemons.push_back(new LowDemon());
		lowdemons.back()->init(1.0f, lowdemonsPosition[i]);
	}

	for (size_t i = 0; i < objectPosition.size(); i++)
	{
		_objects.push_back(new PowerUp());
		_objects.back()->init(0.5f, objectPosition[i]);
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
	_player->draw(_spriteBacth, _player->get_skin());

	/*for (size_t i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_spriteBacth, 0);
	}*/
	for (size_t i = 0; i < strongdemons.size(); i++)
	{
		strongdemons[i]->draw(_spriteBacth, 1);
	}
	for (size_t i = 0; i < meddemons.size(); i++)
	{
		meddemons[i]->draw(_spriteBacth, 6);
	}
	for (size_t i = 0; i < lowdemons.size(); i++)
	{
		lowdemons[i]->draw(_spriteBacth, 7);
	}
	for (size_t i = 0; i < _objects.size(); i++)
	{
		_objects[i]->draw(_spriteBacth, 2);
	}
	for (size_t i = 0; i < _proyectiles.size(); i++) {
		_proyectiles[i]->draw(_spriteBacth, _player->getbulletskin());
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
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case  SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			//PlaySound("disparo_1.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
			break;
		case  SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			//PlaySound("disparo_1.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
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
			glm::vec2 mouseCoords = _camera.convertScreenToWorl(_inputManager.getMouseCoords());
			//cout << mouseCoords.x << " " << mouseCoords.y << endl;
		}
		if (_inputManager.isKeyPressed(SDLK_UP) || _inputManager.isKeyPressed(SDLK_DOWN) || _inputManager.isKeyPressed(SDLK_LEFT) || _inputManager.isKeyPressed(SDLK_RIGHT)) {
			//CREAR BALA E INICIALIZAR
			if (bala_recargando == false) {
				_proyectiles.push_back(new Proyectil());
				_player->update(_levels[_currentLevel]->getLevelData());
				_proyectiles.back()->init(2.0f, _player->getPosition(), _player->getlastkey());
				bala_recargando = true;

				// Agregar Sonido:
				addMusic("disparo_1.wav");
			}
		}
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		_camera.update();
		_time += 0.002f;
		_player->update(_levels[_currentLevel]->getLevelData());
		_camera.setPosition(_player->getPosition());
		/*for (size_t i = 0; i < _humans.size(); i++)
		{
			_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, strongdemons);
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

		//Validaciones de Demonio Fuerte
		for (size_t i = 0; i < strongdemons.size(); i++)
		{
			//strongdemons[i]->update(_levels[_currentLevel]->getLevelData(), _humans, strongdemons, _player);
			if (strongdemons[i]->collideWithAgent(_player)) {
				addMusic("ataque.wav");
				if (_player->get_vida() == 0) {
					this->initLevel();
					_player->set_vida(500);
				}
				else {
					_player->set_vida(_player->get_vida() - 1);
				}
			}

			strongdemons[i]->update(_levels[_currentLevel]->getLevelData());
			Player* closeHuman = _player;
			float smallestDistance = 400.0f;
			if (closeHuman != nullptr) {
				glm::vec2 direction = glm::normalize(
					closeHuman->getPosition() - strongdemons[i]->getPosition()
				);
				glm::vec2 dist = _player->getPosition() - strongdemons[i]->getPosition();
				float distance = glm::length(dist);
				if (distance < smallestDistance) {
					strongdemons[i]->setPosition(strongdemons[i]->getPosition() += direction * strongdemons[i]->getspeed());
				}
			}
			/*for (size_t j = 0; j < _humans.size(); j++) {
				if (strongdemons[i]->collideWithAgent(_humans[j])) {
					Zombie* z = new Zombie();
					z->init(1.0f, _humans[j]->getPosition());
					strongdemons.push_back(z);
					_humans.erase(_humans.begin() + j);
				}
			}*/
			//CADA DEMONIO VERIFICA SI CHOCÓ CON UN PROYECTIL
			for (size_t j = 0; j < _proyectiles.size(); j++) {
				if (strongdemons[i]->collideWithAgent(_proyectiles[j])) {
					strongdemons[i]->inflict(_player->get_danio());
					if (strongdemons[i]->get_life() <= 0) {
						strongdemons.erase(strongdemons.begin() + i);
					}
					_proyectiles.erase(_proyectiles.begin() + j);
				}
			}
			//CADA DEMONIO VERIFICA SI CHOCÓ CON OTRO DEMONIO:
			for (size_t j = i + 1; j < strongdemons.size(); j++) {
				if (strongdemons[i]->collideWithAgent(strongdemons[j])) {
					strongdemons[i]->randir();
					strongdemons[j]->randir();
				}
			}
			for (size_t j = 0; j < lowdemons.size(); j++) {
				if (strongdemons[i]->collideWithAgent(lowdemons[j])) {
					strongdemons[i]->randir();
					lowdemons[j]->randir();
				}
			}
			for (size_t j = 0; j < meddemons.size(); j++) {
				if (strongdemons[i]->collideWithAgent(meddemons[j])) {
					strongdemons[i]->randir();
					meddemons[j]->randir();
				}
			}
		}

		//Validaciones de Demonio Medio
		for (size_t i = 0; i < meddemons.size(); i++)
		{
			//strongdemons[i]->update(_levels[_currentLevel]->getLevelData(), _humans, strongdemons, _player);
			if (meddemons[i]->collideWithAgent(_player)) {
				addMusic("ataque.wav");
				if (_player->get_vida() == 0) {
					this->initLevel();
					_player->set_vida(500);
				}
				else {
					_player->set_vida(_player->get_vida() - 1);
				}
			}

			meddemons[i]->update(_levels[_currentLevel]->getLevelData());
			Player* closeHuman = _player;
			float smallestDistance = 400.0f;
			if (closeHuman != nullptr) {
				glm::vec2 direction = glm::normalize(
					closeHuman->getPosition() - meddemons[i]->getPosition()
				);
				glm::vec2 dist = _player->getPosition() - meddemons[i]->getPosition();
				float distance = glm::length(dist);
				if (distance < smallestDistance) {
					meddemons[i]->setPosition(meddemons[i]->getPosition() += direction * meddemons[i]->getspeed());
				}
			}
			/*for (size_t j = 0; j < _humans.size(); j++) {
				if (meddemons[i]->collideWithAgent(_humans[j])) {
					Zombie* z = new Zombie();
					z->init(1.0f, _humans[j]->getPosition());
					meddemons.push_back(z);
					_humans.erase(_humans.begin() + j);
				}
			}*/
			//CADA DEMONIO VERIFICA SI CHOCÓ CON UN PROYECTIL
			for (size_t j = 0; j < _proyectiles.size(); j++) {
				if (meddemons[i]->collideWithAgent(_proyectiles[j])) {
					meddemons[i]->inflict(_player->get_danio());
					if (meddemons[i]->get_life() <= 0) {
						meddemons.erase(meddemons.begin() + i);
						break;
					}
					_proyectiles.erase(_proyectiles.begin() + j);
				}
			}
			//CADA DEMONIO VERIFICA SI CHOCÓ CON OTRO DEMONIO:
			for (size_t j = i + 1; j < meddemons.size(); j++) {
				if (meddemons[i]->collideWithAgent(meddemons[j])) {
					meddemons[i]->randir();
					meddemons[j]->randir();
				}
			}
			for (size_t j = 0; j < strongdemons.size(); j++) {
				if (meddemons[i]->collideWithAgent(strongdemons[j])) {
					meddemons[i]->randir();
					strongdemons[j]->randir();
				}
			}
			for (size_t j = 0; j < lowdemons.size(); j++) {
				if (meddemons[i]->collideWithAgent(lowdemons[j])) {
					meddemons[i]->randir();
					lowdemons[j]->randir();
				}
			}
		}

		//Validaciones de Demonio Debiles
		for (size_t i = 0; i < lowdemons.size(); i++)
		{
			//strongdemons[i]->update(_levels[_currentLevel]->getLevelData(), _humans, strongdemons, _player);
			if (lowdemons[i]->collideWithAgent(_player)) {
				addMusic("ataque.wav");
				if (_player->get_vida() == 0) {
					this->initLevel();
					_player->set_vida(500);
				}
				else {
					_player->set_vida(_player->get_vida() - 1);
				}
			}

			lowdemons[i]->update(_levels[_currentLevel]->getLevelData());
			Player* closeHuman = _player;
			float smallestDistance = 400.0f;
			if (closeHuman != nullptr) {
				glm::vec2 direction = glm::normalize(
					closeHuman->getPosition() - lowdemons[i]->getPosition()
				);
				glm::vec2 dist = _player->getPosition() - lowdemons[i]->getPosition();
				float distance = glm::length(dist);
				if (distance < smallestDistance) {
					lowdemons[i]->setPosition(lowdemons[i]->getPosition() += direction * lowdemons[i]->getspeed());
				}
			}
			/*for (size_t j = 0; j < _humans.size(); j++) {
				if (lowdemons[i]->collideWithAgent(_humans[j])) {
					Zombie* z = new Zombie();
					z->init(1.0f, _humans[j]->getPosition());
					lowdemons.push_back(z);
					_humans.erase(_humans.begin() + j);
				}
			}*/
			//CADA DEMONIO VERIFICA SI CHOCÓ CON UN PROYECTIL
			for (size_t j = 0; j < _proyectiles.size(); j++) {
				if (lowdemons[i]->collideWithAgent(_proyectiles[j])) {
					lowdemons[i]->inflict(_player->get_danio());
					if (lowdemons[i]->get_life() <= 0) {
						lowdemons.erase(lowdemons.begin() + i);
						break;
					}
					_proyectiles.erase(_proyectiles.begin() + j);
				}
			}
			//CADA DEMONIO VERIFICA SI CHOCÓ CON OTRO DEMONIO:
			for (size_t j = i + 1; j < lowdemons.size(); j++) {
				if (lowdemons[i]->collideWithAgent(lowdemons[j])) {
					lowdemons[i]->randir();
					lowdemons[j]->randir();
				}
			}
			for (size_t j = 0; j < meddemons.size(); j++) {
				if (lowdemons[i]->collideWithAgent(meddemons[j])) {
					lowdemons[i]->randir();
					meddemons[j]->randir();
				}
			}
			for (size_t j = 0; j < strongdemons.size(); j++) {
				if (lowdemons[i]->collideWithAgent(strongdemons[j])) {
					lowdemons[i]->randir();
					strongdemons[j]->randir();
				}
			}
		}


		for (size_t i = 0; i < _objects.size(); i++)
		{
			_objects[i]->update(_levels[_currentLevel]->getLevelData());
			if (_objects[i]->collideWithAgent(_player)) {
				_objects.erase(_objects.begin() + i);
				_player->boost();
				addMusic("power.wav");
			}
		}
		for (size_t i = 0; i < _proyectiles.size(); i++)
		{
			_proyectiles[i]->update(_levels[_currentLevel]->getLevelData());
			//ELIMINO PROYECTIL SI CHOCA CON LA PARED
			if (_proyectiles[i]->specialcollide(_levels[_currentLevel]->getLevelData())) {
				_proyectiles.erase(_proyectiles.begin() + i);
			}
		}

		//RECARGA DE BALA
		if (bala_recargando == true) {
			tiempo_recarga_balas = tiempo_recarga_balas - 1;
			if (tiempo_recarga_balas < 0) {
				tiempo_recarga_balas = 30;
				bala_recargando = false;
			}
		}

		//GASTAR BOOST DEL PLAYER
		_player->desgastarboost();
	}
}


MainGame::MainGame() :
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
