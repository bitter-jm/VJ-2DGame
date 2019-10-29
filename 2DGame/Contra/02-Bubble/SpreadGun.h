#ifndef _SPREADGUN_INCLUDE
#define _SPREADGUN_INCLUDE


#include "Item.h"

// SpreadGun is basically a Sprite that represents the spreadgun. As such it has
// all properties it needs to track its movement, jumping, and collisions.

 
class SpreadGun: public Item
{
	public:
		void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 pos);

};


#endif // _SPREADGUN_INCLUDE


