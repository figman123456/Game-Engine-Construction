#include "TileMapEntity.h"
#include "pugixml\pugixml.hpp"
#include "pugixml\pugiconfig.hpp"
#include "Utils.h"
#include "TimeManager.h"
#include "Scene.h"


TileMapEntity::TileMapEntity(std::string l_mapPath)
{

	pugi::xml_document* doc = new pugi::xml_document();
	pugi::xml_parse_result result = doc->load_file(l_mapPath.c_str(), pugi::xml_encoding::encoding_auto);

	HAPI->DebugText(result.description());

	pugi::xml_node mapNode = doc->child("map");

	pugi::xml_attribute widthAttrib = mapNode.attribute("width");
	m_mapWidth = (unsigned int)widthAttrib.as_uint(0);
	m_mapHeight = (unsigned int)mapNode.attribute("height").as_uint(0);
	m_tileWidth = (unsigned int)mapNode.attribute("tilewidth").as_uint(0);
	m_tileHeight = (unsigned int)mapNode.attribute("tileheight").as_uint(0);

	std::string imagePath = doc->child("map").child("tileset").child("image").attribute("source").as_string();
	m_gfxID = Graphics::Instance().CreateSprite("res/" + imagePath, m_tileWidth, m_tileHeight);

	pugi::xml_node mapData = doc->child("map").child("layer").child("data");

	for (auto tile : mapData.children())
	{
		auto tileData = tile.attribute("gid");
		m_map.push_back(tileData.as_int());
		m_collisionMask.push_back((bool)tileData.as_int());
	}


	for (int i = 0; i < (int)m_mapHeight; i++)
	{
		for (int j = 0; j < (int)m_mapWidth; j++)
		{
			if (m_collisionMask[i*(int)m_mapWidth+j])
			{
				int x = j* m_tileWidth;
				int y = i * m_tileHeight;
				int width = x + m_tileWidth;
				int height = y + m_tileHeight;

				Rect newRect{y,x,height,width};

				m_tileBoxes.push_back(newRect);
			}
		}
		
	}

	delete doc;
	
}

void TileMapEntity::Init()
{

}

void TileMapEntity::Update()
{
	if (HAPI->GetControllerData(0, &m_controller))
	{
		if (m_controller.digitalButtons[HK_DIGITAL_A])
		{
			m_jumpPressed = true;
		}
		else
		{
			m_jumpPressed = false;
		}

		if (m_controller.digitalButtons[HK_DIGITAL_DPAD_RIGHT])
		{
			m_rightPressed = true;
		}
		else
		{
			m_rightPressed = false;
		}

		if (m_controller.digitalButtons[HK_DIGITAL_DPAD_LEFT])
		{
			m_leftPressed = true;
		}
		else
		{
			m_leftPressed = false;
		}

	}

	float deltaTime = TimeManager::Instance().DeltaTime();
	
	m_velocity.y -= GRAVITY;

	if (m_isPlayerGrounded)
	{
		m_velocity.y = 0;
		m_isJumping = false;
	}

	if (m_jumpPressed && !m_isJumping && m_isPlayerGrounded)
	{
		AddForce(CVector2{ 0.0f, -JUMP_FORCE });
		m_isJumping = true;
		m_isPlayerGrounded = false;
	}

	if (m_rightPressed)
	{
		AddForce(CVector2{ MOVE_FORCE, 0.0f });
		m_player->SetAnimation("Walk");
		
	}
	else if (m_leftPressed)
	{
		AddForce(CVector2{ -MOVE_FORCE, 0.0f });
		m_player->SetAnimation("Walk");
		
	}
	else
	{
		m_velocity = CVector2{ 0.0f, m_velocity.y };
		m_player->SetAnimation("Default");
	}
	

	m_velocity.y = Utils::Clamp(m_velocity.y, -MAX_VEL_Y, MAX_VEL_Y);
	m_velocity.x = Utils::Clamp(m_velocity.x, -MAX_VEL_X, MAX_VEL_X);

	m_position = m_position + m_velocity * deltaTime;

	CheckCollisions(m_player->GetCollisionBox());
}

void TileMapEntity::Render()
{
	
	for (int i = 0; i < (int)m_mapHeight; i++)
	{
		for (int j = 0; j < (int)m_mapWidth; j++)
		{
			int tileFrame = m_map[(i * (int)m_mapWidth) + j] - 1;
			
			if (tileFrame > -1)
			{
				int posX = ((int)m_position.x) + (j * m_tileWidth);
				int posY = ((int)m_position.y) + (i * m_tileHeight);
				Graphics::Instance().DrawSprite(m_gfxID, posX, posY, tileFrame);
			}	
		}
	}
}

void TileMapEntity::Destroy()
{

}

void TileMapEntity::CheckCollisions(Rect l_colisionBox)
{
	m_isPlayerGrounded = false;

	for (auto tile : m_tileBoxes)
	{
		Rect tempTile = tile;

		tempTile.Translate((int)m_position.x, (int)m_position.y);

		if (tempTile.Intersects(l_colisionBox))
		{

			if (tempTile.m_top < l_colisionBox.m_bottom && tempTile.m_top >  l_colisionBox.m_top)
			{
				m_position.y -= (float)(tempTile.m_top - l_colisionBox.m_bottom );
				m_velocity = CVector2{ m_velocity.x, 0.0f };
				m_isPlayerGrounded = true;
			}

			if (tempTile.m_bottom > l_colisionBox.m_top && tempTile.m_bottom < l_colisionBox.m_bottom)
			{
				m_position.y -= (float)(tempTile.m_bottom  - l_colisionBox.m_top -1);
				m_velocity = CVector2{ m_velocity.x, 0.0f };
			}


		} 

		tempTile = tile;
		tempTile.Translate((int)m_position.x, (int)m_position.y);

		if (tempTile.Intersects(l_colisionBox))
		{
			if (tempTile.m_right > l_colisionBox.m_left && tempTile.m_right < l_colisionBox.m_right)
			{
				m_position.x -= (float)((tempTile.m_right - l_colisionBox.m_left));
				m_velocity = CVector2{ 0.0f, m_velocity.y };
			}
			if (tempTile.m_left < l_colisionBox.m_right && tempTile.m_left > l_colisionBox.m_left)
			{
				m_position.x -= (float)((tempTile.m_left - l_colisionBox.m_right));
				m_velocity = CVector2{ 0.0f, m_velocity.y };
			}

		}

	}
}

