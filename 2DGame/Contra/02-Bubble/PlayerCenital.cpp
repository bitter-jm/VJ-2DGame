#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PlayerCenital.h"
#include "Game.h"

# define M_PI 3.14159265358979323846  /* pi */
 
#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define RUN_VELOCITY 4
#define SHOT_VELOCITY 11
#define UPGRADE_WEAPON_X 2600

enum PlayerCenitalAnims
{
	P0, P22, P45, P67, P90, P112, P135, P157, P180, P203, P225, P248, P270, P293, P314, P338, // STAND
	PR0, PR22, PR45, PR67, PR90, PR112, PR135, PR157, PR180, PR203, PR225, PR248, PR270, PR293, PR314, PR338, // RUN
	PS0, PS22, PS45, PS67, PS90, PS112, PS135, PS157, PS180, PS203, PS225, PS248, PS270, PS293, PS314, PS338, // SHOOT
	PD0, PD22, PD45, PD67, PD90, PD112, PD135, PD157, PD180, PD203, PD225, PD248, PD270, PD293, PD314, PD338, // DYING
	PDE0, PDE22, PDE45, PDE67, PDE90, PDE112, PDE135, PDE157, PDE180, PDE203, PDE225, PDE248, PDE270, PDE293, PDE314, PDE338 // DEAD
};

enum BasicAnimations
{
	STAND, RUN, OTHERS
};

void PlayerCenital::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	hp = 3;
	spritesheet.loadFromFile("images/playercenital.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(128, 128), glm::vec2(0.0625, 0.0625), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(80);

	// STANDING
	sprite->setAnimationSpeed(P0, 2);
	sprite->addKeyframe(P0, glm::vec2(0.f, 0.0625f * 12.f));
	sprite->setAnimationSpeed(P22, 2);
	sprite->addKeyframe(P22, glm::vec2(0.f, 0.0625f * 13.f));
	sprite->setAnimationSpeed(P45, 2);
	sprite->addKeyframe(P45, glm::vec2(0.f, 0.0625f * 14.f));
	sprite->setAnimationSpeed(P67, 2);
	sprite->addKeyframe(P67, glm::vec2(0.f, 0.0625f * 15.f));
	sprite->setAnimationSpeed(P90, 2);
	sprite->addKeyframe(P90, glm::vec2(0.f, 0.f));
	sprite->setAnimationSpeed(P112, 2);
	sprite->addKeyframe(P112, glm::vec2(0.f, 0.0625f));
	sprite->setAnimationSpeed(P135, 2);
	sprite->addKeyframe(P135, glm::vec2(0.f, 0.0625f * 2.f));
	sprite->setAnimationSpeed(P157, 2);
	sprite->addKeyframe(P157, glm::vec2(0.f, 0.0625f * 3.f));
	sprite->setAnimationSpeed(P180, 2);
	sprite->addKeyframe(P180, glm::vec2(0.f, 0.0625f * 4.f));
	sprite->setAnimationSpeed(P203, 2);
	sprite->addKeyframe(P203, glm::vec2(0.f, 0.0625f * 5.f));
	sprite->setAnimationSpeed(P225, 2);
	sprite->addKeyframe(P225, glm::vec2(0.f, 0.0625f * 6.f));
	sprite->setAnimationSpeed(P248, 2);
	sprite->addKeyframe(P248, glm::vec2(0.f, 0.0625f * 7.f));
	sprite->setAnimationSpeed(P270, 2);
	sprite->addKeyframe(P270, glm::vec2(0.f, 0.0625f * 8.f));
	sprite->setAnimationSpeed(P293, 2);
	sprite->addKeyframe(P293, glm::vec2(0.f, 0.0625f * 9.f));
	sprite->setAnimationSpeed(P314, 2);
	sprite->addKeyframe(P314, glm::vec2(0.f, 0.0625f * 10.f));
	sprite->setAnimationSpeed(P338, 2);
	sprite->addKeyframe(P338, glm::vec2(0.f, 0.0625f * 11.f));

	// RUNNING
	sprite->setAnimationSpeed(PR0, 10);
	sprite->addKeyframe(PR0, glm::vec2(0.0625f * 0.f, 0.0625f * 12.f));
	sprite->addKeyframe(PR0, glm::vec2(0.0625f * 1.f, 0.0625f * 12.f));
	sprite->addKeyframe(PR0, glm::vec2(0.0625f * 2.f, 0.0625f * 12.f));
	sprite->addKeyframe(PR0, glm::vec2(0.0625f * 3.f, 0.0625f * 12.f));
	sprite->setAnimationSpeed(PR22, 10);
	sprite->addKeyframe(PR22, glm::vec2(0.0625f * 0.f, 0.0625f * 13.f));
	sprite->addKeyframe(PR22, glm::vec2(0.0625f * 1.f, 0.0625f * 13.f));
	sprite->addKeyframe(PR22, glm::vec2(0.0625f * 2.f, 0.0625f * 13.f));
	sprite->addKeyframe(PR22, glm::vec2(0.0625f * 3.f, 0.0625f * 13.f));
	sprite->setAnimationSpeed(PR45, 10);
	sprite->addKeyframe(PR45, glm::vec2(0.0625f * 0.f, 0.0625f * 14.f));
	sprite->addKeyframe(PR45, glm::vec2(0.0625f * 1.f, 0.0625f * 14.f));
	sprite->addKeyframe(PR45, glm::vec2(0.0625f * 2.f, 0.0625f * 14.f));
	sprite->addKeyframe(PR45, glm::vec2(0.0625f * 3.f, 0.0625f * 14.f));
	sprite->setAnimationSpeed(PR67, 10);
	sprite->addKeyframe(PR67, glm::vec2(0.0625f * 0.f, 0.0625f * 15.f));
	sprite->addKeyframe(PR67, glm::vec2(0.0625f * 1.f, 0.0625f * 15.f));
	sprite->addKeyframe(PR67, glm::vec2(0.0625f * 2.f, 0.0625f * 15.f));
	sprite->addKeyframe(PR67, glm::vec2(0.0625f * 3.f, 0.0625f * 15.f));
	sprite->setAnimationSpeed(PR90, 10);
	sprite->addKeyframe(PR90, glm::vec2(0.0625f * 0.f, 0.0625f * 0.f));
	sprite->addKeyframe(PR90, glm::vec2(0.0625f * 1.f, 0.0625f * 0.f));
	sprite->addKeyframe(PR90, glm::vec2(0.0625f * 2.f, 0.0625f * 0.f));
	sprite->addKeyframe(PR90, glm::vec2(0.0625f * 3.f, 0.0625f * 0.f));
	sprite->setAnimationSpeed(PR112, 10);
	sprite->addKeyframe(PR112, glm::vec2(0.0625f * 0.f, 0.0625f * 1.f));
	sprite->addKeyframe(PR112, glm::vec2(0.0625f * 1.f, 0.0625f * 1.f));
	sprite->addKeyframe(PR112, glm::vec2(0.0625f * 2.f, 0.0625f * 1.f));
	sprite->addKeyframe(PR112, glm::vec2(0.0625f * 3.f, 0.0625f * 1.f));
	sprite->setAnimationSpeed(PR135, 10);
	sprite->addKeyframe(PR135, glm::vec2(0.0625f * 0.f, 0.0625f * 2.f));
	sprite->addKeyframe(PR135, glm::vec2(0.0625f * 1.f, 0.0625f * 2.f));
	sprite->addKeyframe(PR135, glm::vec2(0.0625f * 2.f, 0.0625f * 2.f));
	sprite->addKeyframe(PR135, glm::vec2(0.0625f * 3.f, 0.0625f * 2.f));
	sprite->setAnimationSpeed(PR157, 10);
	sprite->addKeyframe(PR157, glm::vec2(0.0625f * 0.f, 0.0625f * 3.f));
	sprite->addKeyframe(PR157, glm::vec2(0.0625f * 1.f, 0.0625f * 3.f));
	sprite->addKeyframe(PR157, glm::vec2(0.0625f * 2.f, 0.0625f * 3.f));
	sprite->addKeyframe(PR157, glm::vec2(0.0625f * 3.f, 0.0625f * 3.f));
	sprite->setAnimationSpeed(PR180, 10);
	sprite->addKeyframe(PR180, glm::vec2(0.0625f * 0.f, 0.0625f * 4.f));
	sprite->addKeyframe(PR180, glm::vec2(0.0625f * 1.f, 0.0625f * 4.f));
	sprite->addKeyframe(PR180, glm::vec2(0.0625f * 2.f, 0.0625f * 4.f));
	sprite->addKeyframe(PR180, glm::vec2(0.0625f * 3.f, 0.0625f * 4.f));
	sprite->setAnimationSpeed(PR203, 10);
	sprite->addKeyframe(PR203, glm::vec2(0.0625f * 0.f, 0.0625f * 5.f));
	sprite->addKeyframe(PR203, glm::vec2(0.0625f * 1.f, 0.0625f * 5.f));
	sprite->addKeyframe(PR203, glm::vec2(0.0625f * 2.f, 0.0625f * 5.f));
	sprite->addKeyframe(PR203, glm::vec2(0.0625f * 3.f, 0.0625f * 5.f));
	sprite->setAnimationSpeed(PR225, 10);
	sprite->addKeyframe(PR225, glm::vec2(0.0625f * 0.f, 0.0625f * 6.f));
	sprite->addKeyframe(PR225, glm::vec2(0.0625f * 1.f, 0.0625f * 6.f));
	sprite->addKeyframe(PR225, glm::vec2(0.0625f * 2.f, 0.0625f * 6.f));
	sprite->addKeyframe(PR225, glm::vec2(0.0625f * 3.f, 0.0625f * 6.f));
	sprite->setAnimationSpeed(PR248, 10);
	sprite->addKeyframe(PR248, glm::vec2(0.0625f * 0.f, 0.0625f * 7.f));
	sprite->addKeyframe(PR248, glm::vec2(0.0625f * 1.f, 0.0625f * 7.f));
	sprite->addKeyframe(PR248, glm::vec2(0.0625f * 2.f, 0.0625f * 7.f));
	sprite->addKeyframe(PR248, glm::vec2(0.0625f * 3.f, 0.0625f * 7.f));
	sprite->setAnimationSpeed(PR270, 10);
	sprite->addKeyframe(PR270, glm::vec2(0.0625f * 0.f, 0.0625f * 8.f));
	sprite->addKeyframe(PR270, glm::vec2(0.0625f * 1.f, 0.0625f * 8.f));
	sprite->addKeyframe(PR270, glm::vec2(0.0625f * 2.f, 0.0625f * 8.f));
	sprite->addKeyframe(PR270, glm::vec2(0.0625f * 3.f, 0.0625f * 8.f));
	sprite->setAnimationSpeed(PR293, 10);
	sprite->addKeyframe(PR293, glm::vec2(0.0625f * 0.f, 0.0625f * 9.f));
	sprite->addKeyframe(PR293, glm::vec2(0.0625f * 1.f, 0.0625f * 9.f));
	sprite->addKeyframe(PR293, glm::vec2(0.0625f * 2.f, 0.0625f * 9.f));
	sprite->addKeyframe(PR293, glm::vec2(0.0625f * 3.f, 0.0625f * 9.f));
	sprite->setAnimationSpeed(PR314, 10);
	sprite->addKeyframe(PR314, glm::vec2(0.0625f * 0.f, 0.0625f * 10.f));
	sprite->addKeyframe(PR314, glm::vec2(0.0625f * 1.f, 0.0625f * 10.f));
	sprite->addKeyframe(PR314, glm::vec2(0.0625f * 2.f, 0.0625f * 10.f));
	sprite->addKeyframe(PR314, glm::vec2(0.0625f * 3.f, 0.0625f * 10.f));
	sprite->setAnimationSpeed(PR338, 10);
	sprite->addKeyframe(PR338, glm::vec2(0.0625f * 0.f, 0.0625f * 11.f));
	sprite->addKeyframe(PR338, glm::vec2(0.0625f * 1.f, 0.0625f * 11.f));
	sprite->addKeyframe(PR338, glm::vec2(0.0625f * 2.f, 0.0625f * 11.f));
	sprite->addKeyframe(PR338, glm::vec2(0.0625f * 3.f, 0.0625f * 11.f));

	// SHOOTING
	sprite->setAnimationSpeed(PS0, 2);
	sprite->addKeyframe(PS0, glm::vec2(0.0625f * 4.f, 0.0625f * 12.f));
	sprite->setAnimationSpeed(PS22, 2);
	sprite->addKeyframe(PS22, glm::vec2(0.0625f * 4.f, 0.0625f * 13.f));
	sprite->setAnimationSpeed(PS45, 2);
	sprite->addKeyframe(PS45, glm::vec2(0.0625f * 4.f, 0.0625f * 14.f));
	sprite->setAnimationSpeed(PS67, 2);
	sprite->addKeyframe(PS67, glm::vec2(0.0625f * 4.f, 0.0625f * 15.f));
	sprite->setAnimationSpeed(PS90, 2);
	sprite->addKeyframe(PS90, glm::vec2(0.0625f * 4.f, 0.f));
	sprite->setAnimationSpeed(PS112, 2);
	sprite->addKeyframe(PS112, glm::vec2(0.0625f * 4.f, 0.0625f));
	sprite->setAnimationSpeed(PS135, 2);
	sprite->addKeyframe(PS135, glm::vec2(0.0625f * 4.f, 0.0625f * 2.f));
	sprite->setAnimationSpeed(PS157, 2);
	sprite->addKeyframe(PS157, glm::vec2(0.0625f * 4.f, 0.0625f * 3.f));
	sprite->setAnimationSpeed(PS180, 2);
	sprite->addKeyframe(PS180, glm::vec2(0.0625f * 4.f, 0.0625f * 4.f));
	sprite->setAnimationSpeed(PS203, 2);
	sprite->addKeyframe(PS203, glm::vec2(0.0625f * 4.f, 0.0625f * 5.f));
	sprite->setAnimationSpeed(PS225, 2);
	sprite->addKeyframe(PS225, glm::vec2(0.0625f * 4.f, 0.0625f * 6.f));
	sprite->setAnimationSpeed(PS248, 2);
	sprite->addKeyframe(PS248, glm::vec2(0.0625f * 4.f, 0.0625f * 7.f));
	sprite->setAnimationSpeed(PS270, 2);
	sprite->addKeyframe(PS270, glm::vec2(0.0625f * 4.f, 0.0625f * 8.f));
	sprite->setAnimationSpeed(PS293, 2);
	sprite->addKeyframe(PS293, glm::vec2(0.0625f * 4.f, 0.0625f * 9.f));
	sprite->setAnimationSpeed(PS314, 2);
	sprite->addKeyframe(PS314, glm::vec2(0.0625f * 4.f, 0.0625f * 10.f));
	sprite->setAnimationSpeed(PS338, 2);
	sprite->addKeyframe(PS338, glm::vec2(0.0625f * 4.f, 0.0625f * 11.f));

	// DYING
	sprite->setAnimationSpeed(PD0,2);
	sprite->addKeyframe(PD0, glm::vec2(0.0625f * 5.f, 0.0625f * 12.f));
	sprite->addKeyframe(PD0, glm::vec2(0.0625f * 6.f, 0.0625f * 12.f));
	sprite->setAnimationSpeed(PD22, 2);
	sprite->addKeyframe(PD22, glm::vec2(0.0625f * 5.f, 0.0625f * 13.f));
	sprite->addKeyframe(PD22, glm::vec2(0.0625f * 6.f, 0.0625f * 13.f));
	sprite->setAnimationSpeed(PD45, 2);
	sprite->addKeyframe(PD45, glm::vec2(0.0625f * 5.f, 0.0625f * 14.f));
	sprite->addKeyframe(PD45, glm::vec2(0.0625f * 6.f, 0.0625f * 14.f));
	sprite->setAnimationSpeed(PD67, 2);
	sprite->addKeyframe(PD67, glm::vec2(0.0625f * 5.f, 0.0625f * 15.f));
	sprite->addKeyframe(PD67, glm::vec2(0.0625f * 6.f, 0.0625f * 15.f));
	sprite->setAnimationSpeed(PD90, 2);
	sprite->addKeyframe(PD90, glm::vec2(0.0625f * 5.f, 0.f));
	sprite->addKeyframe(PD90, glm::vec2(0.0625f * 6.f, 0.f));
	sprite->setAnimationSpeed(PD112, 2);
	sprite->addKeyframe(PD112, glm::vec2(0.0625f * 5.f, 0.0625f));
	sprite->addKeyframe(PD112, glm::vec2(0.0625f * 6.f, 0.0625f));
	sprite->setAnimationSpeed(PD135, 2);
	sprite->addKeyframe(PD135, glm::vec2(0.0625f * 5.f, 0.0625f * 2.f));
	sprite->addKeyframe(PD135, glm::vec2(0.0625f * 6.f, 0.0625f * 2.f));
	sprite->setAnimationSpeed(PD157, 2);
	sprite->addKeyframe(PD157, glm::vec2(0.0625f * 5.f, 0.0625f * 3.f));
	sprite->addKeyframe(PD157, glm::vec2(0.0625f * 6.f, 0.0625f * 3.f));
	sprite->setAnimationSpeed(PD180, 2);
	sprite->addKeyframe(PD180, glm::vec2(0.0625f * 5.f, 0.0625f * 4.f));
	sprite->addKeyframe(PD180, glm::vec2(0.0625f * 6.f, 0.0625f * 4.f));
	sprite->setAnimationSpeed(PD203, 2);
	sprite->addKeyframe(PD203, glm::vec2(0.0625f * 5.f, 0.0625f * 5.f));
	sprite->addKeyframe(PD203, glm::vec2(0.0625f * 6.f, 0.0625f * 5.f));
	sprite->setAnimationSpeed(PD225, 2);
	sprite->addKeyframe(PD225, glm::vec2(0.0625f * 5.f, 0.0625f * 6.f));
	sprite->addKeyframe(PD225, glm::vec2(0.0625f * 6.f, 0.0625f * 6.f));
	sprite->setAnimationSpeed(PD248, 2);
	sprite->addKeyframe(PD248, glm::vec2(0.0625f * 5.f, 0.0625f * 7.f));
	sprite->addKeyframe(PD248, glm::vec2(0.0625f * 6.f, 0.0625f * 7.f));
	sprite->setAnimationSpeed(PD270, 2);
	sprite->addKeyframe(PD270, glm::vec2(0.0625f * 5.f, 0.0625f * 8.f));
	sprite->addKeyframe(PD270, glm::vec2(0.0625f * 6.f, 0.0625f * 8.f));
	sprite->setAnimationSpeed(PD293, 2);
	sprite->addKeyframe(PD293, glm::vec2(0.0625f * 5.f, 0.0625f * 9.f));
	sprite->addKeyframe(PD293, glm::vec2(0.0625f * 6.f, 0.0625f * 9.f));
	sprite->setAnimationSpeed(PD314, 2);
	sprite->addKeyframe(PD314, glm::vec2(0.0625f * 5.f, 0.0625f * 10.f));
	sprite->addKeyframe(PD314, glm::vec2(0.0625f * 6.f, 0.0625f * 10.f));
	sprite->setAnimationSpeed(PD338, 2);
	sprite->addKeyframe(PD338, glm::vec2(0.0625f * 5.f, 0.0625f * 11.f));
	sprite->addKeyframe(PD338, glm::vec2(0.0625f * 6.f, 0.0625f * 11.f));

	// DEAD
	sprite->setAnimationSpeed(PDE0, 2);
	sprite->addKeyframe(PDE0, glm::vec2(0.0625f * 6.f, 0.0625f * 12.f));
	sprite->setAnimationSpeed(PDE22, 2);
	sprite->addKeyframe(PDE22, glm::vec2(0.0625f * 6.f, 0.0625f * 13.f));
	sprite->setAnimationSpeed(PDE45, 2);
	sprite->addKeyframe(PDE45, glm::vec2(0.0625f * 6.f, 0.0625f * 14.f));
	sprite->setAnimationSpeed(PDE67, 2);
	sprite->addKeyframe(PDE67, glm::vec2(0.0625f * 6.f, 0.0625f * 15.f));
	sprite->setAnimationSpeed(PDE90, 2);
	sprite->addKeyframe(PDE90, glm::vec2(0.0625f * 6.f, 0.f));
	sprite->setAnimationSpeed(PDE112, 2);
	sprite->addKeyframe(PDE112, glm::vec2(0.0625f * 6.f, 0.0625f));
	sprite->setAnimationSpeed(PDE135, 2);
	sprite->addKeyframe(PDE135, glm::vec2(0.0625f * 6.f, 0.0625f * 2.f));
	sprite->setAnimationSpeed(PDE157, 2);
	sprite->addKeyframe(PDE157, glm::vec2(0.0625f * 6.f, 0.0625f * 3.f));
	sprite->setAnimationSpeed(PDE180, 2);
	sprite->addKeyframe(PDE180, glm::vec2(0.0625f * 6.f, 0.0625f * 4.f));
	sprite->setAnimationSpeed(PDE203, 2);
	sprite->addKeyframe(PDE203, glm::vec2(0.0625f * 6.f, 0.0625f * 5.f));
	sprite->setAnimationSpeed(PDE225, 2);
	sprite->addKeyframe(PDE225, glm::vec2(0.0625f * 6.f, 0.0625f * 6.f));
	sprite->setAnimationSpeed(PDE248, 2);
	sprite->addKeyframe(PDE248, glm::vec2(0.0625f * 6.f, 0.0625f * 7.f));
	sprite->setAnimationSpeed(PDE270, 2);
	sprite->addKeyframe(PDE270, glm::vec2(0.0625f * 6.f, 0.0625f * 8.f));
	sprite->setAnimationSpeed(PDE293, 2);
	sprite->addKeyframe(PDE293, glm::vec2(0.0625f * 6.f, 0.0625f * 9.f));
	sprite->setAnimationSpeed(PDE314, 2);
	sprite->addKeyframe(PDE314, glm::vec2(0.0625f * 6.f, 0.0625f * 10.f));
	sprite->setAnimationSpeed(PDE338, 2);
	sprite->addKeyframe(PDE338, glm::vec2(0.0625f * 6.f, 0.0625f * 11.f));

	sprite->changeAnimation(P0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayerCenital.x), float(tileMapDispl.y + posPlayerCenital.y)));

}

// Encargado de hacer seguir el raton y disparar
void PlayerCenital::changeBasicAction()
{
	posMouseX = Game::instance().getPosMouseX();
	posMouseY = Game::instance().getPosMouseY();
	int windowSizeX = glutGet(GLUT_WINDOW_WIDTH);
	int windowSizeY = glutGet(GLUT_WINDOW_HEIGHT);
	bool lookingRight = false;
	if (posMouseX > windowSizeX / 2) lookingRight = true;

	// ANGLE**
	//PLAYER -> Y = windowSizeY / 2		sobre [0, windowSizeY] 
	//MOUSE -> Y = posMouseY			sobre [0, windowSizeY]
	//PLAYER -> X = windowSizeX / 2		sobre [0, windowSizeX]
	//MOUSE -> X = posMouseX			sobre [0, windowSizeX]
	// double angulo = atan2(MOUSE.Y - PLAYER.Y, MOUSE.X - PLAYER.X) * 180 / M_PI;
	if (!dead) {
		angle = atan2(posMouseY - windowSizeY / 2, posMouseX - windowSizeX / 2) * 180 / M_PI;
		angle = -angle;
		if (angle < 0) angle = 360 + angle % 360;
	}

	// SHOOTING**
	// CURRENT TIME -> glutGet(GLUT_ELAPSED_TIME)
	// LAST SHOOTED -> lastShot
	// CURRENTLY SHOOTING -> shooting
	if (!dead) {
		if (!shooting && Game::instance().isMousePressed() && lastShot + 400 <= glutGet(GLUT_ELAPSED_TIME) && basicAction != OTHERS) {
			// Initial shoot action
			shooting = true;
			lastShot = glutGet(GLUT_ELAPSED_TIME);
			shoot(angle, posPlayerCenital.x, posPlayerCenital.y);
		}
		else if (lastShot < glutGet(GLUT_ELAPSED_TIME) && lastShot + 75 >= glutGet(GLUT_ELAPSED_TIME) && basicAction != OTHERS) {
			// Shooting animation
			shooting = true;
		}
		else {
			shooting = false;
		}
	}
	else shooting = false;

	// DYING**
	bool renderDying = false;
	bool renderDead = false;
	if (dead && deathTime + 1000 >= glutGet(GLUT_ELAPSED_TIME)) {
		renderDying = true;
	}
	else if (dead) {
		renderDead = true;
		deathFinished = true;
	}


	if (angle > 349 || angle <= 11) {
		if (renderDying) {
			if (sprite->animation() != PD0) {
				sprite->changeAnimation(PD0);
			}
		}
		else if (renderDead) {
			if (sprite->animation() != PDE0) {
				sprite->changeAnimation(PDE0);
			}
		}
		else if (shooting) sprite->changeAnimation(PS0);
		else if (moving && sprite->animation() != PR0) sprite->changeAnimation(PR0);
		else if (!moving && sprite->animation() != P0) sprite->changeAnimation(P0);
	}
	else if (angle <= 33) {
		if (renderDying) {
			if (sprite->animation() != PD22) {
				sprite->changeAnimation(PD22);
			}
		}
		else if (renderDead) {
			if (sprite->animation() != PDE22) {
				sprite->changeAnimation(PDE22);
			}
		}
		else if (shooting) sprite->changeAnimation(PS22);
		else if (moving && sprite->animation() != PR22) sprite->changeAnimation(PR22);
		else if (!moving && sprite->animation() != P22) sprite->changeAnimation(P22);
	}
	else if (angle <= 56) {
		if (renderDying) {
			if (sprite->animation() != PD45) {
				sprite->changeAnimation(PD45);
			}
		}
		else if (renderDead) {
			if (sprite->animation() != PDE45) {
				sprite->changeAnimation(PDE45);
			}
		}
		else if (shooting) sprite->changeAnimation(PS45);
		else if (moving && sprite->animation() != PR45) sprite->changeAnimation(PR45);
		else if (!moving && sprite->animation() != P45) sprite->changeAnimation(P45);
	}
	else if (angle <= 78) {
		if (renderDying) {
			if (sprite->animation() != PD67) {
				sprite->changeAnimation(PD67);
			}
		}
		else if (renderDead) {
			if (sprite->animation() != PDE67) {
				sprite->changeAnimation(PDE67);
			}
		}
		else if (shooting) sprite->changeAnimation(PS67);
		else if (moving && sprite->animation() != PR67) sprite->changeAnimation(PR67);
		else if (!moving && sprite->animation() != P67) sprite->changeAnimation(P67);
	}
	else if (angle <= 101) {
		if (renderDying) {
			if (sprite->animation() != PD90) {
				sprite->changeAnimation(PD90);
			}
		}
		else if (renderDead) {
			if (sprite->animation() != PDE90) {
				sprite->changeAnimation(PDE90);
			}
		}
		else if (shooting) sprite->changeAnimation(PS90);
		else if (moving && sprite->animation() != PR90) sprite->changeAnimation(PR90);
		else if (!moving && sprite->animation() != P90) sprite->changeAnimation(P90);
	}
	else if (angle <= 123) {
		if (renderDying) {
			if (sprite->animation() != PD112) {
				sprite->changeAnimation(PD112);
			}
		}
		else if (renderDead) {
			if (sprite->animation() != PDE112) {
				sprite->changeAnimation(PDE112);
			}
		}
		else if (shooting) sprite->changeAnimation(PS112);
		else if (moving && sprite->animation() != PR112) sprite->changeAnimation(PR112);
		else if (!moving && sprite->animation() != P112) sprite->changeAnimation(P112);
	}
	else if (angle <= 146) {
		if (renderDying) {
			if (sprite->animation() != PD135) {
				sprite->changeAnimation(PD135);
			}
		}
		else if (renderDead) {
			if (sprite->animation() != PDE135) {
				sprite->changeAnimation(PDE135);
			}
		}
		else if (shooting) sprite->changeAnimation(PS135);
		else if (moving && sprite->animation() != PR135) sprite->changeAnimation(PR135);
		else if (!moving && sprite->animation() != P135) sprite->changeAnimation(P135);
	}
	else if (angle <= 168) {
	if (renderDying) {
		if (sprite->animation() != PD157) {
			sprite->changeAnimation(PD157);
		}
	}
	else if (renderDead) {
		if (sprite->animation() != PDE157) {
			sprite->changeAnimation(PDE157);
		}
	}
		else if (shooting) sprite->changeAnimation(PS157);
		else if (moving && sprite->animation() != PR157) sprite->changeAnimation(PR157);
		else if (!moving && sprite->animation() != P157) sprite->changeAnimation(P157);
	}
	else if (angle <= 191) {
	if (renderDying) {
		if (sprite->animation() != PD180) {
			sprite->changeAnimation(PD180);
		}
	}
	else if (renderDead) {
		if (sprite->animation() != PDE180) {
			sprite->changeAnimation(PDE180);
		}
	}
		else if (shooting) sprite->changeAnimation(PS180);
		else if (moving && sprite->animation() != PR180) sprite->changeAnimation(PR180);
		else if (!moving && sprite->animation() != P180) sprite->changeAnimation(P180);
	}
	else if (angle <= 214) {
	if (renderDying) {
		if (sprite->animation() != PD203) {
			sprite->changeAnimation(PD203);
		}
	}
	else if (renderDead) {
		if (sprite->animation() != PDE203) {
			sprite->changeAnimation(PDE203);
		}
	}
		else if (shooting) sprite->changeAnimation(PS203);
		else if (moving && sprite->animation() != PR203) sprite->changeAnimation(PR203);
		else if (!moving && sprite->animation() != P203) sprite->changeAnimation(P203);
	}
	else if (angle <= 236) {
	if (renderDying) {
		if (sprite->animation() != PD225) {
			sprite->changeAnimation(PD225);
		}
	}
	else if (renderDead) {
		if (sprite->animation() != PDE225) {
			sprite->changeAnimation(PDE225);
		}
	}
		else if (shooting) sprite->changeAnimation(PS225);
		else if (moving && sprite->animation() != PR225) sprite->changeAnimation(PR225);
		else if (!moving && sprite->animation() != P225) sprite->changeAnimation(P225);
	}
	else if (angle <= 259) {
	if (renderDying) {
		if (sprite->animation() != PD248) {
			sprite->changeAnimation(PD248);
		}
	}
	else if (renderDead) {
		if (sprite->animation() != PDE248) {
			sprite->changeAnimation(PDE248);
		}
	}
		else if (shooting) sprite->changeAnimation(PS248);
		else if (moving && sprite->animation() != PR248) sprite->changeAnimation(PR248);
		else if (!moving && sprite->animation() != P248) sprite->changeAnimation(P248);
	}
	else if (angle <= 281) {
	if (renderDying) {
		if (sprite->animation() != PD270) {
			sprite->changeAnimation(PD270);
		}
	}
	else if (renderDead) {
		if (sprite->animation() != PDE270) {
			sprite->changeAnimation(PDE270);
		}
	}
		else if (shooting) sprite->changeAnimation(PS270);
		else if (moving && sprite->animation() != PR270) sprite->changeAnimation(PR270);
		else if (!moving && sprite->animation() != P270) sprite->changeAnimation(P270);
	}
	else if (angle <= 304) {
	if (renderDying) {
		if (sprite->animation() != PD293) {
			sprite->changeAnimation(PD293);
		}
	}
	else if (renderDead) {
		if (sprite->animation() != PDE293) {
			sprite->changeAnimation(PDE293);
		}
	}
		else if (shooting) sprite->changeAnimation(PS293);
		else if (moving && sprite->animation() != PR293) sprite->changeAnimation(PR293);
		else if (!moving && sprite->animation() != P293) sprite->changeAnimation(P293);
	}
	else if (angle <= 325) {
	if (renderDying) {
		if (sprite->animation() != PD314) {
			sprite->changeAnimation(PD314);
		}
	}
	else if (renderDead) {
		if (sprite->animation() != PDE314) {
			sprite->changeAnimation(PDE314);
		}
	}
		else if (shooting) sprite->changeAnimation(PS314);
		else if (moving && sprite->animation() != PR314) sprite->changeAnimation(PR314);
		else if (!moving && sprite->animation() != P314) sprite->changeAnimation(P314);
	}
	else if (angle <= 349) {
	if (renderDying) {
		if (sprite->animation() != PD338) {
			sprite->changeAnimation(PD338);
		}
	}
	else if (renderDead) {
		if (sprite->animation() != PDE338) {
			sprite->changeAnimation(PDE338);
		}
	}
		else if (shooting) sprite->changeAnimation(PS338);
		else if (moving && sprite->animation() != PR338) sprite->changeAnimation(PR338);
		else if (!moving && sprite->animation() != P338) sprite->changeAnimation(P338);
	}
}

void PlayerCenital::update(int deltaTime, ShaderProgram& shaderProgram)
{
	changeBasicAction();

	//if (hp <= 0) kill();

	// Movimiento
	moving = false;
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT) && !dead)
	{
		posPlayerCenital.x -= RUN_VELOCITY;
		if (map->collisionMoveLeft(glm::vec2(posPlayerCenital.x + 32, posPlayerCenital.y+32), glm::ivec2(48, 48)))
			posPlayerCenital.x += RUN_VELOCITY;
		else moving = true;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !dead)
	{
		posPlayerCenital.x += RUN_VELOCITY;
		if (map->collisionMoveRight(glm::vec2(posPlayerCenital.x + 32, posPlayerCenital.y+32), glm::ivec2(48, 48)))
			posPlayerCenital.x -= RUN_VELOCITY;
		else moving = true;
	} 
	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !dead)
	{
		posPlayerCenital.y -= RUN_VELOCITY;
		if (map->collisionMoveUp(glm::vec2(posPlayerCenital.x + 32, posPlayerCenital.y+32), glm::ivec2(48, 48))) // TODO!!!!
		  	posPlayerCenital.y += RUN_VELOCITY;
		else moving = true;
	}
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !dead)
	{
		posPlayerCenital.y += RUN_VELOCITY;
		if (map->collisionMoveDown(glm::vec2(posPlayerCenital.x+32, posPlayerCenital.y), glm::ivec2(48, 84), &posPlayerCenital.y))
			posPlayerCenital.y -= RUN_VELOCITY;
		else moving = true;
	}

	// Actualizar numero de vidas (visual)
	lifes.clear();
	for (int i = 0; i < hp; i++) {
		Life* l = new Life();
		if (posPlayerCenital.x <= float(SCREEN_WIDTH - 1) / 2.0f) l->init(tileMapDispl, shaderProgram, glm::vec2(10 + i * 32, 10));
		else l->init(tileMapDispl, shaderProgram, glm::vec2(posPlayerCenital.x + 10 + i * 32 - SCREEN_WIDTH / 2, posPlayerCenital.y - SCREEN_HEIGHT / 2 + 30));
		lifes.push_back(l);
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayerCenital.x), float(tileMapDispl.y + posPlayerCenital.y)));
	sprite->update(deltaTime);
}

void PlayerCenital::render()
{
	sprite->render();
	for (int i = 0; i < lifes.size(); i++) {
		lifes[i]->render();
	}
}

void PlayerCenital::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void PlayerCenital::setPosition(const glm::vec2& pos)
{
	posPlayerCenital = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayerCenital.x), float(tileMapDispl.y + posPlayerCenital.y)));
}

glm::vec2 PlayerCenital::getPosition()
{
	return posPlayerCenital;
}

void PlayerCenital::shoot(double angulo, int x, int y)
{
	if (currentGun == 1) SoundManager::getInstance()->playSound("sounds/defaultGun.ogg", false);
	else if (currentGun == 2) SoundManager::getInstance()->playSound("sounds/shotGun.ogg", false);
	shootedProjectile = true;
	projectileCoords.x = x+64;
	projectileCoords.y = y+64;
	projectileType = currentGun;
	projectileVelocity = SHOT_VELOCITY;
	projectileAngle = angle;
}

void PlayerCenital::kill() {
	if (!dead) {
		deathTime = glutGet(GLUT_ELAPSED_TIME);
		dead = true;
	}
}

bool PlayerCenital::isDead() {
	return deathFinished;
}

bool PlayerCenital::hasShootedProjectile() {
	if (shootedProjectile) {
		shootedProjectile = false;
		return true;
	}
	else return false;
}
glm::ivec2 PlayerCenital::getProjectileCoords() {
	return projectileCoords;
}
int PlayerCenital::getProjectileAngle() {
	return projectileAngle;
}
int PlayerCenital::getProjectileVelocity() {
	return projectileVelocity;
}
int PlayerCenital::getProjectileType() {
	return projectileType;
}

void PlayerCenital::upgradeSpreadGun() {
	this->spreadGun = true;
	this->render();
}

void PlayerCenital::reduceHP(float dmg) {
	hp -= dmg;
	if (hp < 0) hp = 0;
	if (hp == 0) kill();
}

void PlayerCenital::addHP(float hp) {
	this->hp += hp;

}

int PlayerCenital::getDeathFinished() {
	return deathFinished;
}