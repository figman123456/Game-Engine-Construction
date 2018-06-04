#include "Entity.h"
#include "Graphics.h"

void Entity::Render(){

	Graphics::Instance().DrawSprite(m_gfxID, (int)m_position.x, (int)m_position.y, m_frame);

}


