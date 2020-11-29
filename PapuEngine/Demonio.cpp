#include "Demonio.h"
#include "Human.h"
#include <iostream>
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>

Demonio::Demonio() {

}

Demonio::~Demonio() {

}

void Demonio::setPosition(glm::vec2 position) {
	_position = position;
}



void Demonio::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans, std::vector<Demonio*>& zombies){

	collideWithLevel(levelData);
	/*
	Human* closeHuman = getNearestHuman(humans);
	if (closeHuman != nullptr) {
		glm::vec2 direction = glm::normalize(
			closeHuman->getPosition() - _position
		);
		_position += direction * _speed;
	}*/

	/*
	// Gestionar colisiones con humanos:
	for (size_t i = 0; i < humans.size(); i++)
	{

		// Verificar si hay colision:
		if (collideWithAgent(humans[i]))
		{
			// Crear nuevo objeto Zombie:
			Zombie* zom = new Zombie();
			// Iniciar Zombie con la Posicion del Humano que mato:
			zom->init(0.8888f, humans[i]->getPosition());
			// Agregar Zombie al arreglo 'zombies'
			zombies.push_back(zom);
			
			// Eliminar Humano del arreglo 'humans'
			humans.erase(humans.begin() + i);
		}
	}
	*/
}

Human* Demonio::getNearestHuman(std::vector<Human*>& humans) {
	Human* closestHuman = nullptr;
	float smallestDistance = 8888.0f;
	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 dist = humans[i]->getPosition() - _position;
		float distance = glm::length(dist);
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}
	return closestHuman;
}

void Demonio::init(float speed, glm::vec2 position) {
	_speed = speed;
	_position = position;
	_life = 1;
	// _color.set(0, 0, 0, 255);
}

void Demonio::randir(){
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
}

int Demonio::get_life(){
	return _life;
}