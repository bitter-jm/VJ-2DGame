#ifndef _Projectile_INCLUDE
#define _Projectile_INCLUDE

#include "Sprite.h"
#include "EntityManager.h"

class Projectile
{

public:
	void init(int id, int x, int y, int angle, int velocity, int type, bool enemy, EntityManager *EM, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	glm::vec2 getPosition();
	void collisioned();

private:
	Texture spritesheet;
	Sprite* sprite;

	//EntityManager* em;

	glm::ivec2 posProjectile;
	int initialX, initialY;
	int angle;
	int velocity;
	int type;
	int collisionTime;
	int id;
	bool enemy;
};


#endif 


