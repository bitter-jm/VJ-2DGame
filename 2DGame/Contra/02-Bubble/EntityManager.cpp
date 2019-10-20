#include <GL/glew.h>
#include <GL/glut.h>
#include "EntityManager.h"
#include <iostream>
#include <set>
#include "Projectile.h"

using namespace std;

//EntityManager::EntityManager()
//{
//	player = NULL;
//}

void EntityManager::init(Player *p, ShaderProgram *SP)
{
	player = p;
	shaderProgram = SP;
}

void EntityManager::update(int deltaTime)
{
	//Find if player created new projectile
	if (player->hasShootedProjectile()) {
		Projectile p;
		p.init(nextProjectileID, player->getProjectileCoords().x, player->getProjectileCoords().y, player->getProjectileAngle(), player->getProjectileVelocity(), player->getProjectileType(), false, *shaderProgram);
		projectiles[nextProjectileID] = p;
		nextProjectileID++;
	}


	set<int> toErase;
	for (auto& x : projectiles) {
		x.second.update(deltaTime);
		if (x.second.needToDelete()) toErase.insert(x.first);
	}

	for (auto& x : toErase) {
		projectiles.erase(x);
	}



	//Find collisions between player and enemy projectiles
	//	Kill player
	//Find collisions between player projectiles and enemies
	//	Reduce lifes enemy
	//Find collisions between player and enemies
	//	Kill player
}

void EntityManager::render()
{
	for (auto& x : projectiles) {
		x.second.render();
	}
}

void EntityManager::createProjectile() {

}

void EntityManager::destroyProjectile(int id) {

}
