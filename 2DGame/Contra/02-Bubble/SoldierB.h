#pragma once
#include "NPC.h"

class SoldierB : public NPC
{
	public:
		bool playerInRange();
		void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int pID);
		void update(int deltaTime);

	private:

};

