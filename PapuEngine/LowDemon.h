#pragma once
#include "Demonio.h"
class LowDemon :
    public Demonio
{
public:
	LowDemon();
	~LowDemon();
	void init(float speed, glm::vec2 position);
};

