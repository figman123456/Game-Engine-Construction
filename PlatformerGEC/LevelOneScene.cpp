#include "LevelOneScene.h"

#include "InputManager.h"


LevelOneScene::LevelOneScene()
{
}

void LevelOneScene::Init()
{
	m_sceneName = "Level 1";

	m_map = std::make_shared<TileMapEntity>("res/map.tmx");
	AddGameObject(m_map);

	m_player = std::make_shared<PlayerCharacterEntity>();
	m_player->Init();
	m_player->SetCollision(Rect{ 9, 4, 48, 38 });
	m_player->SetPosition(CVector2{ 366.0f, 266.0f });
	AddGameObject(m_player);

	m_map->SetPlayer(m_player);

}

void LevelOneScene::Update()
{
	Scene::Update();
}
