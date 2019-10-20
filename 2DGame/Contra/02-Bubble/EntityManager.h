#ifndef _EM_INCLUDE
#define _EM_INCLUDE

#include <map>
#include "Player.h"
#include "Projectile.h"

class EntityManager
{

public:
	EntityManager() {}

	void init(Player *p); 
	void update(int deltaTime); 
	void render(); 
	void createProjectile(); 
	void destroyProjectile(int id);

private:
	Player *player;
	//map<int, Projectile> projectiles;

};

#endif
