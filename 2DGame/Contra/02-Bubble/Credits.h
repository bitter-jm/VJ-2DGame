#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE

#include "ShaderProgram.h"
#include "Sprite.h"
#include "TileMap.h"

class Credits
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
	bool buttonSound1;
	bool buttonSound2;
};


#endif // _MENU_INCLUDE
