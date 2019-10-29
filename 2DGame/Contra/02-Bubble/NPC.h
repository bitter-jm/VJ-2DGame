#pragma once
#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include "EntityManager.h"
#include <math.h>     

class NPC
{
public:
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap); 
	void setPosition(const glm::vec2& pos);
	void setEntityManager(EntityManager* em);
	bool is_dead();
	bool is_dying();
	glm::vec2 getPosition();
	void setPlayer(Player* p);
	void reduceHP(float dmg);


protected:
	float hp, movSpeed, dmg, range;
	int lastShoot;
	float secondsToAttack, projectileSpeed;	// attack/second
	bool dead, dying;
	float dyingStartTime, dyingTime;
	int stanceID;
	Player* player;
	glm::ivec2 tileMapDispl, position;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	EntityManager* em;

};

