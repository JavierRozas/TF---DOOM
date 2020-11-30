#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "GLS_Program.h"
#include "Sprite.h"
#include "Window.h"
#include "Camera2D.h"
#include <vector>
#include "SpriteBacth.h"
#include "InputManager.h"
#include "Level.h"
#include "Player.h"
#include "PowerUp.h"
#include "Proyectil.h"
#include "StrongDemon.h"
#include "MedDemon.h"
#include "LowDemon.h"

enum class GameState
{
	PLAY, EXIT
};


class MainGame
{
private:
	int _witdh;
	int _height;
	int tiempo_recarga_balas;
	bool bala_recargando;
	float _time;
	vector<Level*> _levels;
	Player* _player;
	int _currentLevel;
	Window _window;
	void init();
	void procesInput();
	GLS_Program _program;
	vector<Sprite*> _sprites;
	vector<StrongDemon*> strongdemons;
	vector<MedDemon*> meddemons;
	vector<LowDemon*> lowdemons;
	vector<PowerUp*> _objects;
	vector<Proyectil*> _proyectiles;
	Camera2D _camera;
	SpriteBacth _spriteBacth;
	InputManager _inputManager;
	void initLevel();
	
public:
	MainGame();
	~MainGame();
	GameState _gameState;
	void initShaders();
	void run();
	void draw();
	void update();
	void addMusic(const char *song);
};

