#ifndef _TUTORIAL_INCLUDE
#define _TUTORIAL_INCLUDE

#include "ShaderProgram.h"
#include "Sprite.h"
#include "TileMap.h"

class Tutorial
{

public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void render();
	void update();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;

	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite* sprite;
};


#endif // _TUTORIAL_INCLUDE
