#pragma once


#include "Scene.h"
#include "TileMapEntity.h"
#include "PlayerCharacterEntity.h"

class LevelOneScene : public Scene
{
//Scene Interface
public:

	virtual void Init();
	virtual void Update();

public:
	LevelOneScene();

private:

	std::shared_ptr<TileMapEntity> m_map;
	std::shared_ptr<PlayerCharacterEntity> m_player;

	HAPI_TControllerData m_controller;

	const float JUMP_FORCE{ 200.0f };
	const float MOVE_FORCE{ 30.0f };

	//Input
	bool m_jumpPressed{false};
	bool m_isJumping{ false };
	bool m_isPlayerGrounded{ false };

	bool m_rightPressed{ false };
	bool m_leftPressed{ false };


};

