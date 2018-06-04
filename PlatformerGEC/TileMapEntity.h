#pragma once

#include "Entity.h"
#include "CharacterEntity.h"
#include "Rect.h"

#include<string>
#include<vector>
#include<memory>

class TileMapEntity : public Entity
{
//Entity Interface 
public:

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	TileMapEntity(std::string l_mapPath);
	void CheckCollisions(Rect l_colisionBox);

	void AddForce(CVector2 l_force){ m_velocity = m_velocity - l_force; }
	void SetVelocity(CVector2 l_vel){ m_velocity = l_vel; }
	const CVector2 GetVelocity() const { return m_velocity; }

	void SetPlayer(std::shared_ptr<CharacterEntity> l_player){ m_player = l_player; }

	const bool IsPlayerGrounded()const { return m_playerGrounded; }

private:

	std::string m_mapPath;

	std::shared_ptr<CharacterEntity> m_player;

	const float GRAVITY = 2.5f;
	const float MAX_VEL_Y = 400.0f;
	const float MAX_VEL_X = 180.0f;
	const float JUMP_FORCE{ 400.0f };
	const float MOVE_FORCE{ 30.0f };

	CVector2 m_velocity{ 0, 0 };

	unsigned int m_mapWidth{ 0 };
	unsigned int m_mapHeight{ 0 };
	unsigned int m_tileWidth{ 0 };
	unsigned int m_tileHeight{ 0 };

	bool m_playerGrounded{ false };

	std::vector<int> m_map;
	std::vector<bool> m_collisionMask;
	std::vector<Rect> m_tileBoxes;

	HAPI_TControllerData m_controller;

	//Input
	bool m_jumpPressed{ false };
	bool m_isJumping{ false };
	bool m_isPlayerGrounded{ false };

	bool m_rightPressed{ false };
	bool m_leftPressed{ false };

};

