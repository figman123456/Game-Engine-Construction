#pragma once

#include "Vector2.h"
#include "Graphics.h"

class Entity
{
public:
	Entity(){}
	~Entity(){}

	virtual void Init() = 0;
	virtual void Update() = 0;

	virtual void Render();

	virtual void Destroy() = 0;

	void SetIsAlive(bool l_isAlive){ m_isAlive = l_isAlive; }
	const bool GetIsAlive() const { return m_isAlive; }

	void SetPosition(CVector2 l_position){ m_position = l_position; }
	const CVector2 GetPosition() const { return m_position; }


private:

	bool m_isAlive{ true };

protected:
	

	CVector2 m_position{ 0, 0 };

	int m_gfxID{ -1 };
	int m_frame{ 0 };

	
};

