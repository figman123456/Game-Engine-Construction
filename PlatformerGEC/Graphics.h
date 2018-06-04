#pragma once

#include<HAPI_lib.h>
#include<string>
#include<vector>

#include"Rect.h"

//Foreword Declaration
class Sprite;

class Graphics
{
public:

	//Graphics Functions
	bool Initialize(int l_width, int l_height);
	static Graphics& Instance()
	{
		if (!s_instance)
		{
			s_instance = new Graphics();
		}

		return *s_instance;
	}
	void Destroy();

	//Sprite Functions
	int CreateSprite(std::string l_filePath, int l_frameWidth, int l_frameHeight);
	void DrawSprite(int l_id, int l_x, int l_y, int l_frame);

	//Draw Functions
	void Clear();

private:
	Graphics();
	~Graphics();

	static Graphics* s_instance;

	std::vector<Sprite*> m_sprites;

	BYTE* m_screen = nullptr;
	int m_nextID{ -1 };

	Rect m_screenRect{ 0, 0, 0, 0 };

};

