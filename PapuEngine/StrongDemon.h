#pragma once
#include "Demonio.h"
class StrongDemon : public Demonio
{
public:
	StrongDemon();
	~StrongDemon();
	void init(float speed, glm::vec2 position);
};

