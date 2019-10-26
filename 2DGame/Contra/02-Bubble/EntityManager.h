#ifndef _EMANAGER_INCLUDE
#define _EMANAGER_INCLUDE

#include <map>
#include "Player.h"
#include "Projectile.h"
#include "ShaderProgram.h"

class EntityManager
{

public:
	//EntityManager() {}

	void init(Player *p, ShaderProgram *shaderProgram);
	void update(int deltaTime); 
	void render(); 
	void createProjectile(glm::vec2 initPos, int angle, int vel, int type, int range); //enemyProjectile
	void destroyProjectile(int id);
	bool checkCollisionEnemy(glm::vec2 posE, int xSize, int ySize);

private:
	void checkCollisionPlayer();
	int nextProjectileID = 0;
	Player *player;
	ShaderProgram *shaderProgram;
	map<int, Projectile> projectiles;
};

#endif
