#pragma once
#include "Item.h"
class SniperGun: public Item
{
	public:
		void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 pos);
		
};

