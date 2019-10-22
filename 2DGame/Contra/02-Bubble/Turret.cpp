#include "Turret.h"

enum TurretAnim {
	STAND_LEFT
};

void Turret::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	float spriteSheetX = 0.1;
	float spriteSheetY = 1.0 / 18.0;

	spritesheet.loadFromFile("images/enemies.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 48), glm::vec2(0.1, 0.05), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));

	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(STAND_LEFT, 2);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0*spriteSheetX, 6 * spriteSheetY));
	sprite->changeAnimation(STAND_LEFT);
}



