#include <GL/glew.h>
#include <GL/glut.h>
#include "EntityManager.h"
#include <iostream>
#include "Projectile.h"

using namespace std;

void EntityManager::init(Player *p)
{
	player = p;
}

void EntityManager::update(int deltaTime)
{
	//Update each projectile
	//Find collisions between player and enemy projectiles
	//	Kill player
	//Find collisions between player projectiles and enemies
	//	Reduce lifes enemy
	//Find collisions between player and enemies
}

void EntityManager::render()
{
	//Render each projectile
}

void EntityManager::createProjectile() {

}

void EntityManager::destroyProjectile(int id) {

}
