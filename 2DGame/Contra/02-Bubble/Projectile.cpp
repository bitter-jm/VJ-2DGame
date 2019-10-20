#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Projectile.h"

# define M_PI 3.14159265358979323846  /* pi */
#define MAX_DISTANCE 1000
#define EXPLODING_TIME 1000


enum ProjectileAnims
{
	FLYING, EXPLODING
};

void Projectile::init(int ID, int x, int y, int a, int v, int t, bool e, EntityManager *EM, ShaderProgram& shaderProgram)
{
	posProjectile.x = x;
	posProjectile.y = y;
	initialX = x;
	initialY = y;
	angle = a;
	velocity = v;
	type = t;
	enemy = e;
	id = ID;
	//em = EM;
	spritesheet.loadFromFile("images/projectiles.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.1, 0.1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	if (type == 1) {
		sprite->setAnimationSpeed(FLYING, 10);
		sprite->addKeyframe(FLYING, glm::vec2(0.0f, 0.f));
		sprite->addKeyframe(FLYING, glm::vec2(0.1f, 0.f));
		sprite->addKeyframe(FLYING, glm::vec2(0.2f, 0.f));
		sprite->addKeyframe(FLYING, glm::vec2(0.3f, 0.f));
	} 
	else if (type == 2) {
		sprite->setAnimationSpeed(FLYING, 10);
		sprite->addKeyframe(FLYING, glm::vec2(0.0f, 0.2f));
		sprite->addKeyframe(FLYING, glm::vec2(0.1f, 0.2f));
		sprite->addKeyframe(FLYING, glm::vec2(0.2f, 0.2f));
		sprite->addKeyframe(FLYING, glm::vec2(0.3f, 0.2f));
	}

	sprite->setAnimationSpeed(EXPLODING, 10);
	sprite->addKeyframe(EXPLODING, glm::vec2(0.0f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.1f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.2f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.3f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.4f, 0.1f));
	sprite->addKeyframe(EXPLODING, glm::vec2(0.5f, 0.1f));	

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posProjectile.x), float(posProjectile.y)));
}

void Projectile::update(int deltaTime)
{
	// Check max distance
	if (posProjectile.y <= velocity || posProjectile.y >= 460) {
		cout << "Projectile deleted (1)" << endl;
		//em->destroyProjectile(id);
	}
	if (sqrt(((float)initialX - (float)posProjectile.x) * ((float)initialX - (float)posProjectile.x) + 
			((float)initialY - (float)posProjectile.y) * ((float)initialY - (float)posProjectile.y)) > MAX_DISTANCE) {
		cout << "Projectile deleted (2)" << endl;
		//em->destroyProjectile(id);
	}

	// If explotion time passed, delete projectile
	if (sprite->animation == EXPLODING && collisionTime > glutGet(GLUT_ELAPSED_TIME) - EXPLODING_TIME) {
		cout << "Projectile deleted (3)" << endl;
		//em->destroyProjectile(id);
	}

	// If not exploting, move
	if (sprite->animation == FLYING) {
		if (angle == 0) posProjectile.x += velocity;
		else if (angle == 90) posProjectile.y -= velocity;
		else if (angle == 180 || angle == -180) posProjectile.x -= velocity;
		else if (angle == 270 || angle == -90) posProjectile.y += velocity;
		else {
			int inc = (int)(sin(M_PI/4) * (double)velocity);
			if (angle == 45) { posProjectile.x += inc; posProjectile.y -= inc; }
			else if (angle == 135) { posProjectile.x -= inc; posProjectile.y -= inc; }
			else if (angle == 225 || angle == -135) { posProjectile.x -= inc; posProjectile.y += inc; }
			else if (angle == 315 || angle == -45) { posProjectile.x += inc; posProjectile.y += inc; }
		}
	}

	sprite->setPosition(glm::vec2(float(posProjectile.x), float(posProjectile.y)));
}

void Projectile::render()
{
	sprite->render();
}

glm::vec2 Projectile::getPosition()
{
	return posProjectile;
}

void Projectile::collisioned()
{
	sprite->changeAnimation(1);
	collisionTime = glutGet(GLUT_ELAPSED_TIME);
}

