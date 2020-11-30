#pragma once
#include <string>
#include <vector>
#include "SpriteBacth.h"
using namespace std;

const int TILE_WIDTH = 64;
class Level
{
private:
	vector<string> levelData;
	int numHumans;
	void parseLevel();
public:
	glm::vec2 playerPosition;
	vector<glm::vec2> sdemonioPosition;
	vector<glm::vec2> mdemonioPosition;
	vector<glm::vec2> ldemonioPosition;
	vector<glm::vec2> objectPosition;
	int getNumHumans()const {
		return numHumans;
	}
	int getWidth()const {
		return levelData[1].size();
	}
	int getHeight()const {
		return levelData.size();
	}
	const std::vector<std::string>& getLevelData() {
		return levelData;
	}

	glm::vec2 getPlayerPosition() const {
		return playerPosition;
	}
	std::vector<glm::vec2> getMDemoniosPosition()const {
		return mdemonioPosition;
	}
	std::vector<glm::vec2> getSDemoniosPosition()const {
		return sdemonioPosition;
	}
	std::vector<glm::vec2> getLDemoniosPosition()const {
		return ldemonioPosition;
	}
	std::vector<glm::vec2> getObjectPosition()const {
		return objectPosition;
	}
	Level(const std::string& fileName);
	void draw();
	SpriteBacth spriteBatch;
	~Level();
};

