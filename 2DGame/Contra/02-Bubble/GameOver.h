#ifndef _GAMEOVER_INCLUDE
#define _GAMEOVER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class GameOver
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::ivec2 posPlayer);
	void render();
	void update();

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	glm::ivec2 posPlayer;

	int timeAction;
	int action = 0;

};


#endif // _GAMEOVER_INCLUDE


