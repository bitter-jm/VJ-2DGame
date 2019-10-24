#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "ShaderProgram.h"
#include "Sprite.h"
#include "TileMap.h"

class Menu
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


#endif // _MENU_INCLUDE
