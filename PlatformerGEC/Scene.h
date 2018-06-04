#pragma once

#include<string>
#include<memory>
#include<vector>

class Entity;
class Scene
{
public:

	typedef std::string scene_name_t;

	Scene(){}

	virtual void Init() = 0;
	virtual void Update();
	virtual void Render();
	virtual void Destroy();


	void AddGameObject(std::shared_ptr<Entity> l_go);

	const std::string GetName() const{ return m_sceneName; }

protected:
	scene_name_t m_sceneName;
private:
	std::vector<std::shared_ptr<Entity>> m_entities;
};

