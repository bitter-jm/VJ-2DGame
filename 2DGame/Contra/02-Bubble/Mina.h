#pragma once
#include "NPC.h"
#include "PlayerCenital.h"

class Mina : public NPC
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void setPlayer(PlayerCenital* p);

private:
	void setExploding();
	PlayerCenital* playerC;
	int timeExplosion;

};

