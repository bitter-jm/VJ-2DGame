#pragma once
#include "NPC.h"
#include "PlayerCenital.h"
#include "EntityManagerCenital.h"

class SoldierC : public NPC
{
public:
	bool playerInRange();
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void setPlayer(PlayerCenital* playerC);
	void setEntityManager(EntityManagerCenital* em);
	void calculateAngle();

private:
	PlayerCenital* playerC;
	int angle;
	EntityManagerCenital* emc;

};

