#ifndef _SPREADGUN_INCLUDE
#define _SPREADGUN_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// SpreadGun is basically a Sprite that represents the spreadgun. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class SpreadGun
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 pos);
	void update(int deltaTime);
	void render();

	void setPos(glm::vec2 pos);

private:
	glm::ivec2 tileMapDispl, pos;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _SPREADGUN_INCLUDE


