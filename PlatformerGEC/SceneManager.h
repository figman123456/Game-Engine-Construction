#pragma once

#include <string>
#include <unordered_map>
#include <memory>

class Scene;
class SceneManager
{

public:

	static SceneManager& Instance()
	{
		if (!s_instance)
		{
			s_instance = new SceneManager();
		}

		return *s_instance;
	}

	bool Init();
	void Update();
	void Render();

	void AddScene(std::shared_ptr<Scene> l_scene);
	const bool SetScene(std::string l_sceneName);

	void Destroy();

private:
	SceneManager();
	~SceneManager();

	static SceneManager* s_instance;

	
	std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;

	const std::string NO_SCENE = "NO_SCENE";
	std::string m_currentScene = NO_SCENE;

};
