#pragma once
#include "Sprite.h"
#include "TileMap.h"

class Item
{
	public:
		//void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, glm::vec2 pos);
		void update(int deltaTime);
		void render();
		void setHidden(bool b); 
		bool is_Hidden();
		glm::vec2 getPosition();

	protected:
		glm::ivec2 tileMapDispl, pos;
		Texture spritesheet;
		Sprite* sprite;
		bool hidden;
};

