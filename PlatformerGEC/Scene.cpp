#include "Scene.h"
#include "Entity.h"

void Scene::Render()
{
	for (auto entity : m_entities)
	{
		if (entity->GetIsAlive())
			entity->Render();
	}
}

void Scene::Update()
{
	for (auto entity : m_entities)
	{
		if (entity->GetIsAlive())
			entity->Update();
	}
}

void Scene::Destroy()
{
	for (auto entity : m_entities)
	{
		entity->Destroy();
	}
}

void Scene::AddGameObject(std::shared_ptr<Entity> l_go)
{
	m_entities.push_back(l_go);
}
