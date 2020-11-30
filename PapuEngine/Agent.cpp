#include "Agent.h"
#include "ResourceManager.h"
#include "Level.h"
#include <random>



void Agent::checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collidePosition, float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH)
		, floor(y / (float)TILE_WIDTH));
	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].size() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size()) {
		return;
	}
	if (levelData[cornerPos.y][cornerPos.x] != '.') {
		collidePosition.push_back(cornerPos * (float)TILE_WIDTH
			+ glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

void Agent::collidWithTile(glm::vec2 tilePos)
{
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPosition - tilePos;
	float xdepth = MIN_DISTANCE - abs(distVec.x);
	float ydepth = MIN_DISTANCE - abs(distVec.y);
	if (xdepth > 0 || ydepth > 0) {
		if (std::max(xdepth, 0.0f) < std::max(ydepth, 0.0f)) {
			if (distVec.x < 0) {
				_position.x -= xdepth;
			}
			else {
				_position.x += xdepth;
			}
		}
		else {
			if (distVec.y < 0) {
				_position.y -= ydepth;
			}
			else {
				_position.y += ydepth;
			}
		}
	}
}

Agent::Agent()
{
}

Agent::~Agent()
{
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePosition;
	checkTilePosition(levelData, collideTilePosition, _position.x, _position.y);
	checkTilePosition(levelData, collideTilePosition, _position.x + AGENT_WIDTH, _position.y);
	checkTilePosition(levelData, collideTilePosition, _position.x, _position.y + AGENT_WIDTH);
	checkTilePosition(levelData, collideTilePosition, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);
	if (collideTilePosition.size() == 0) return false;
	for (size_t i = 0; i < collideTilePosition.size(); i++)
	{
		collidWithTile(collideTilePosition[i]);
	}
	return true;
}

bool Agent::collideWithAgent(Agent* agent)
{
	glm::vec2 centerPosA = _position + glm::vec2(AGENT_WIDTH / 2);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_WIDTH / 2);
	glm::vec2 dist = centerPosA - centerPosB;
	const float MIN_DISTANCE = AGENT_RADIUS * 2;
	float distance = glm::length(dist);
	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec = glm::normalize(dist) * collisionDepth;
		_position += collisionDepth / 2.0f;
		agent->getPosition() -= collisionDepth / 2.0f;
		return true;
	}
	return false;
}

void Agent::draw(SpriteBacth& spriteBatch, int type)
{

	static int textureID;
	int w = 0;
	int h = 0;
	switch (type) {
	case 0: textureID = ResourceManager::getTexture("Textures/player.png").id; break;
	case 1: textureID = ResourceManager::getTexture("Textures/strongdemon.png").id; break;
	case 2: textureID = ResourceManager::getTexture("Textures/powerup.png").id; break;
	case 3:
	{
		textureID = ResourceManager::getTexture("Textures/proyectil.png").id;
		w = h = 40;
		break;
	}
	case 4: textureID = ResourceManager::getTexture("Textures/boostp.png").id; break;
	case 5: textureID = ResourceManager::getTexture("Textures/boostb.png").id; break;
	case 6: textureID = ResourceManager::getTexture("Textures/meddemon.png").id; break;
	case 7: textureID = ResourceManager::getTexture("Textures/lowdemon.png").id; break;
	case 8: textureID = ResourceManager::getTexture("Textures/strongdemonatck.png").id; break;
	case 9: textureID = ResourceManager::getTexture("Textures/meddemonatck.png").id; break;
	case 10: textureID = ResourceManager::getTexture("Textures/lowdemonatck.png").id; break;
	case 11: break;
	}
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	if (type == 3) {
		glm::vec4 destRect(_position.x + 25, _position.y + 25, AGENT_WIDTH - w, AGENT_WIDTH - h);
		spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
	}
	else {
		glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH - w, AGENT_WIDTH - h);
		spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
	}



}

void Agent::draw_zombie(SpriteBacth& spriteBatch)
{
	static int textureID =
		ResourceManager::getTexture("Textures/demonio.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(_position.x, _position.y, AGENT_WIDTH, AGENT_WIDTH);
	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);
}

float Agent::getspeed()
{
	return _speed;
}

