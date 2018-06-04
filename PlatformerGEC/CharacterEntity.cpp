#include "CharacterEntity.h"
#include "TimeManager.h"
#include "Utils.h"

#include <algorithm>

void CharacterEntity::AddAnimation(std::string l_name, std::vector<int> l_frames)
{
	m_animations[l_name] = l_frames;
}
void CharacterEntity::SetAnimation(std::string l_name)
{
	if (l_name != m_currentAnimation)
	{
		auto it = m_animations.find(l_name);

		if (it == m_animations.end())
		{
			m_frameIndex = 0;
			m_currentAnimation = "Default";
		}
		else
		{
			m_frameIndex = 0;
			m_currentAnimation = l_name;
		}
	}
}

void CharacterEntity::Update()
{
	double deltaTime = TimeManager::Instance().DeltaTime();

	m_previousPos = m_position;
	
	deltaTime = Utils::Clamp(deltaTime, 0.01, 0.016);

	m_wait += deltaTime;

	if (m_wait > .1)
	{
		m_frameIndex++;

		if (m_frameIndex == m_animations[m_currentAnimation].size())
		{
				m_frameIndex = 0;
		}

		m_frame = m_animations[m_currentAnimation].at(m_frameIndex);
		m_wait = 0;
	}

	

}

void CharacterEntity::Render()
{
	Graphics::Instance().DrawSprite(m_gfxID, (int)m_position.x, (int)m_position.y, m_frame);
}

const Rect CharacterEntity::GetCollisionBox() const
{
	Rect newRect = m_collisionBox;
	newRect.Translate((int)m_position.x, (int)m_position.y);
	return newRect;
}

