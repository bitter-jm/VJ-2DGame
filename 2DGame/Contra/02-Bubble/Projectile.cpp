#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Projectile.h"

# define M_PI 3.14159265358979323846  /* pi */
#define MAX_DISTANCE 750
#define EXPLODING_TIME 1000

enum ProjectileAnims
{
	FLYING, EXPLODING
};

void Projectile::init(int ID, int x, int y, int a, int v, int t, bool e, ShaderProgram& shaderProgram)
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
	spritesheet.loadFromFile("images/proyectiles.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.1, 0.1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	if (!enemy) {
		sprite->setAnimationSpeed(FLYING, 8);
		sprite->addKeyframe(FLYING, glm::vec2(0.0f, 0.f));
		sprite->addKeyframe(FLYING, glm::vec2(0.1f, 0.f));
		sprite->addKeyframe(FLYING, glm::vec2(0.2f, 0.f));
		sprite->addKeyframe(FLYING, glm::vec2(0.3f, 0.f));
	} 
	else {
		sprite->setAnimationSpeed(FLYING, 8);
		sprite->addKeyframe(FLYING, glm::vec2(0.0f, 0.2f));
		sprite->addKeyframe(FLYING, glm::vec2(0.1f, 0.2f));
		sprite->addKeyframe(FLYING, glm::vec2(0.2f, 0.2f));
		sprite->addKeyframe(FLYING, glm::vec2(0.3f, 0.2f));
	}

	sprite->setAnimationSpeed(EXPLODING, 8);
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
	if (posProjectile.y <= velocity || posProjectile.y >= 490) {
		cout << "Projectile deleted (1)" << endl;
		deleteProjectile = true;
	}
	if (sqrt(((float)initialX - (float)posProjectile.x) * ((float)initialX - (float)posProjectile.x) + 
			((float)initialY - (float)posProjectile.y) * ((float)initialY - (float)posProjectile.y)) > MAX_DISTANCE) {
		cout << "Projectile deleted (2)" << endl;
		deleteProjectile = true;
	}

	// If explotion time passed, delete projectile
	if (sprite->animation() == EXPLODING && collisionTime > glutGet(GLUT_ELAPSED_TIME) - EXPLODING_TIME) {
		cout << "Projectile deleted (3)" << endl;
		deleteProjectile = true;
	}

	// If not exploting, move
	if (sprite->animation() == FLYING) {
		if (angle == 0) posProjectile.x += velocity;
		else if (angle == 90) posProjectile.y -= velocity;
		else if (angle == 180 || angle == -180) posProjectile.x -= velocity;
		else if (angle == 270 || angle == -90) posProjectile.y += velocity;
		else {
			int inc45 = (int)(sin(M_PI/4) * (double)velocity);
			int inc22s = 2;//(int)(sin(M_PI / 8) * (double)velocity); // Pequeno (La velocidad es tan pequeña que al pasarlo an int se lo carga a 0...)
			int inc22c = 7;// (int)(sin(M_PI / 8) * (double)velocity); // Grande
			if (angle == 45) { posProjectile.x += inc45; posProjectile.y -= inc45; }
			else if (angle == 135) { posProjectile.x -= inc45; posProjectile.y -= inc45; }
			else if (angle == 225 || angle == -135) { posProjectile.x -= inc45; posProjectile.y += inc45; }
			else if (angle == 315 || angle == -45) { posProjectile.x += inc45; posProjectile.y += inc45; }
			else if (angle == 22) { posProjectile.x += inc22c; posProjectile.y -= inc22s; }
			else if (angle == 67) { posProjectile.x += inc22s; posProjectile.y -= inc22c; }
			else if (angle == 112) { posProjectile.x -= inc22s; posProjectile.y -= inc22c; }
			else if (angle == 157) { posProjectile.x -= inc22c; posProjectile.y -= inc22s; }
			else if (angle == -157 || angle == 360 - 157) { posProjectile.x -= inc22c; posProjectile.y += inc22s; }
			else if (angle == -112 || angle == 360 - 112) { posProjectile.x -= inc22s; posProjectile.y += inc22c; }
			else if (angle == -67 || angle == 360 - 67) { posProjectile.x += inc22s; posProjectile.y += inc22c; }
			else if (angle == -22 || angle == 360-22) { posProjectile.x += inc22c; posProjectile.y += inc22s; }
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

bool Projectile::needToDelete() {
	return deleteProjectile;
}

