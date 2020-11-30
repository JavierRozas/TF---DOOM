#pragma once
#include "Demonio.h"
class MedDemon :
    public Demonio
{
public:
	MedDemon();
	~MedDemon();
	void init(float speed, glm::vec2 position);
};

