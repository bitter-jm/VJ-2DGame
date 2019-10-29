#ifndef _EMANAGERCENITAL_INCLUDE
#define _EMANAGERCENITAL_INCLUDE

#include <map>
#include "PlayerCenital.h"
#include "Projectile.h"
#include "ShaderProgram.h"

class EntityManagerCenital
{

public:
	//EntityManager() {}

	void init(PlayerCenital* p, ShaderProgram* shaderProgram);
	void update(int deltaTime);
	void render();
	void createProjectile(glm::vec2 initPos, int angle, int vel, int type, int range); //enemyProjectile
	void destroyProjectile(int id);
	bool checkCollisionEnemy(glm::vec2 posE, int xSize, int ySize);

private:
	void checkCollisionPlayer();
	int nextProjectileID = 0;
	PlayerCenital* player;
	ShaderProgram* shaderProgram;
	map<int, Projectile> projectiles;
};

#endif
