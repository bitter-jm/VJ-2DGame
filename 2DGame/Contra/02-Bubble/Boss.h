#pragma once
#include "NPC.h"

class Boss: public NPC
{
	public:
	bool playerInRange();
	void shootMain(float time);
	void shootLeft(float time);
	void shootRight(float time);
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int pID, TileMap* tileMap, glm::vec2 pos);
	void update(int deltaTime);
	void reduceRightHp(float dmg);
	bool is_left_dead();
	bool is_right_dead();
	void reduceLeftHp(float dmg);

	private:
		float leftPartHP, rightPartHP;	// hp from the NPC class is the main body
		float leftPartDMG, rightPartDMG; // main dmg is in the NPC
		float secondsToAttackLeft, secondsToAttackRight;
		float leftLastShot, rightLastShot;
		float leftPartRange, rightPartRange;
		float leftProjSpeed, rightProjSpeed;

		glm::vec2 mainPos, leftPos, rightPos; 
};

