#pragma once

#include<unordered_map>
#include<vector>
#include<string>

#include "Entity.h"
class CharacterEntity : public Entity
{
//Entity Interface
public:

	virtual void Init() = 0;
	virtual void Update();
	virtual void Render();
	virtual void Destroy() = 0;

public:
	CharacterEntity(){}

	void AddAnimation(std::string l_name, std::vector<int> l_frames);
	void SetAnimation(std::string l_name);

	const Rect GetCollisionBox() const;
	void SetCollision(Rect l_collisionBox){ m_collisionBox = l_collisionBox; }

	const bool CollidesWith(CharacterEntity* l_other){ m_collisionBox.Intersects(l_other->GetCollisionBox()); }

private:

	float m_wait{ 0.0f };

	const float GRAVITY = 9.81f;
	const float MAX_VEL_Y = 100.0f;
	const float MAX_VEL_X = 60.0f;

	CVector2 m_velocity{ 0, 0 };
	CVector2 m_previousPos{ 0, 0 };
	
	float m_frameCounter{ 0 };
	int m_fps{ 24 };

	int m_frameIndex{ 0 };

	bool m_hasMapColision = false;
	bool m_hasGravity = false;

	std::unordered_map < std::string, std::vector<int>> m_animations;
	std::string m_currentAnimation = "Default";

	Rect m_collisionBox{ 0, 0, 32, 32 };

};

