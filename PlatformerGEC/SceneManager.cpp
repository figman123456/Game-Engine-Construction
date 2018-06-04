#include "SceneManager.h"
#include "Scene.h"

#include <HAPI_lib.h>

SceneManager* SceneManager::s_instance = nullptr;

SceneManager::SceneManager()
{

}
SceneManager::~SceneManager()
{

}

void SceneManager::AddScene(std::shared_ptr<Scene> l_scene)
{
	l_scene->Init();
	m_scenes[l_scene->GetName()] = l_scene;
}

const bool SceneManager::SetScene(std::string l_sceneName)
{
	auto it = m_scenes.find(l_sceneName);

	if (it == m_scenes.end())
	{
		m_currentScene = NO_SCENE;
		HAPI->DebugText(std::string("Scene: " + l_sceneName + " not found!"));
		return false;
	}
	else
	{
		m_currentScene = l_sceneName;
		return true;
	}
}

bool SceneManager::Init()
{
	for (auto scene : m_scenes)
	{
		scene.second->Init();
	}

	return true;
}

void SceneManager::Update()
{
	if (m_currentScene != NO_SCENE)
	{
		m_scenes[m_currentScene]->Update();
	}
}
void SceneManager::Render()
{
	if (m_currentScene != NO_SCENE)
	{
		m_scenes[m_currentScene]->Render();
	}
}

void SceneManager::Destroy()
{
	for (auto scene : m_scenes)
	{
		scene.second->Destroy();
	}

	m_scenes.clear();
	delete s_instance;

}
