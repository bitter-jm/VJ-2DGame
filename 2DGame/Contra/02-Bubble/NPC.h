#pragma once
#include "Sprite.h"
#include "TileMap.h"
class NPC
{
public:
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::vec2 getPosition();


protected:
	float hp;
	float movSpeed;
	glm::ivec2 tileMapDispl, position;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};

