#include "NPC.h"


void NPC::update(int deltaTime)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

void NPC::render()
{
	sprite->render();
}

void NPC::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void NPC::setPosition(const glm::vec2& pos)
{
	position = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

glm::vec2 NPC::getPosition()
{
	return position;
}

void NPC::setPlayer(Player* p) {
	player = p;
}