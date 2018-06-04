
#include<HAPI_lib.h>
#include<memory>

#include"Graphics.h"
#include"SceneManager.h"
#include"TimeManager.h"
#include"InputManager.h"
#include"LevelOneScene.h"




void HAPI_Main()
{
	if (!Graphics::Instance().Initialize(800, 600))
		HAPI->Close();

	if (!SceneManager::Instance().Init())
		HAPI->Close();

	std::shared_ptr<LevelOneScene> levelOne = std::make_shared<LevelOneScene>();
	SceneManager::Instance().AddScene(levelOne);	
	SceneManager::Instance().SetScene("Level 1");
	
	HAPI->SetShowFPS(true);

	while (HAPI->Update())
	{
		TimeManager::Instance().Update();
		InputManager::Instance().Update();
		Graphics::Instance().Clear();
		SceneManager::Instance().Update();
		SceneManager::Instance().Render();
	}
	InputManager::Instance().Destroy();
	TimeManager::Instance().Destroy();
	SceneManager::Instance().Destroy();
	Graphics::Instance().Destroy();

	HAPI->Close();
}
