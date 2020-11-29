#include <iostream>
#include "Human.h"
#include "Proyectil.h"
#include <glm\gtx\rotate_vector.hpp>

Proyectil::Proyectil(){

}
Proyectil::~Proyectil() {

}

void Proyectil::init(float speed, glm::vec2 position, char dir){
    _speed = speed;
	_position = position;
	_daño = 1;
	// _color.set(185, 0, 0, 255);
	//static std::mt19937 randomEngine(time(nullptr));
	//static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	switch(dir){
		case 'w': _direction = glm::vec2(0, 1); break;
		case 'a': _direction = glm::vec2(-1,0); break;
		case 's': _direction = glm::vec2(0,-1); break;
		case 'd': _direction = glm::vec2(1,-0); break;
	}
	//if (_direction.length() == 0) {
	//	_direction = glm::vec2(1.0f, 1.0f);
	//}
}

void Proyectil::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {

	//static std::mt19937 randomEngine(time(nullptr));
	//static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	_position += _direction * _speed;
	/*
	if (collideWithLevel(levelData)) {
		//destruir
	}
	// Colision con un 'Zombies':
	for (size_t i = 0; i < zombies.size(); i++)
	{
		// Verificar si hay colision:
		if (collideWithAgent(zombies[i]))
		{
			// humans[i]->setColor();
			// Eliminar Humano del arreglo 'humans'
			zombies.erase(zombies.begin() + i);
		}
	}*/
}

int Proyectil::get_daño(){
	return _daño;
}