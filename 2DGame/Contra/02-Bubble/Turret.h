#pragma once
#include "NPC.h"
class Turret : public NPC
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
};

