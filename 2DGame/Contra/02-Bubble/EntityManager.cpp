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
		int typeproj = player->getProjectileType();
		int angleproj = player->getProjectileAngle();
		glm::ivec2 coordsproj = player->getProjectileCoords();
		int velocityproj = player->getProjectileVelocity();
		Projectile p;
		p.init(nextProjectileID, coordsproj.x, coordsproj.y, angleproj, velocityproj, typeproj, false, *shaderProgram);
		projectiles[nextProjectileID] = p;
		nextProjectileID++;
		if (typeproj == 2) {
			Projectile p2, p3;
			if (angleproj == 0) {
				p2.init(nextProjectileID, coordsproj.x, coordsproj.y, 22, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID] = p2;
				p3.init(nextProjectileID+1, coordsproj.x, coordsproj.y, -22, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID+1] = p3;
			}
			else if (angleproj == 45) {
				p2.init(nextProjectileID, coordsproj.x, coordsproj.y, 67, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID] = p2;
				p3.init(nextProjectileID + 1, coordsproj.x, coordsproj.y, 22, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID + 1] = p3;
			}
			else if (angleproj == 135) {
				p2.init(nextProjectileID, coordsproj.x, coordsproj.y, 112, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID] = p2;
				p3.init(nextProjectileID + 1, coordsproj.x, coordsproj.y, 157, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID + 1] = p3;
			}
			else if (angleproj == 180 || angleproj == -180) {
				p2.init(nextProjectileID, coordsproj.x, coordsproj.y, 157, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID] = p2;
				p3.init(nextProjectileID + 1, coordsproj.x, coordsproj.y, -157, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID + 1] = p3;
			}
			else if (angleproj == -135 || angleproj == 225) {
				p2.init(nextProjectileID, coordsproj.x, coordsproj.y, -157, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID] = p2;
				p3.init(nextProjectileID + 1, coordsproj.x, coordsproj.y, -112, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID + 1] = p3;
			}
			else if (angleproj == -45 || angleproj == 315) {
				p2.init(nextProjectileID, coordsproj.x, coordsproj.y, -67, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID] = p2;
				p3.init(nextProjectileID + 1, coordsproj.x, coordsproj.y, -22, velocityproj, typeproj, false, *shaderProgram);
				projectiles[nextProjectileID + 1] = p3;
			}
			nextProjectileID += 2;
		}
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
