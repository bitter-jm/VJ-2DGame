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
	void createProjectile(); 
	void destroyProjectile(int id);

private:
	int nextProjectileID = 0;
	Player *player;
	ShaderProgram *shaderProgram;
	map<int, Projectile> projectiles;
};

#endif
