#include "PlayerCharacterEntity.h"

void PlayerCharacterEntity::Init()
{
	m_gfxID = Graphics::Instance().CreateSprite("res/cat_sprites.png", 72, 64);

	AddAnimation("Default", std::vector < int > {0});
	AddAnimation("Dead", std::vector < int > {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
	AddAnimation("Walk", std::vector < int > {28, 29, 30, 31, 32, 33, 34, 35, 36, 37});
}
void PlayerCharacterEntity::Destroy()
{

}

