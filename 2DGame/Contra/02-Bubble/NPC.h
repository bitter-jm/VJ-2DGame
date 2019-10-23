#pragma once
#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
class NPC
{
public:
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::vec2 getPosition();
	void setPlayer(Player* p);


protected:
	float hp;
	float movSpeed;
	float dmg;
	float range;
	int stanceID;
	Player* player;
	glm::ivec2 tileMapDispl, position;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};

