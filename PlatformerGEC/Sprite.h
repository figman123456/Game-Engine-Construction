#pragma once

#include<HAPI_lib.h>
class Rect;
class Sprite
{
public:
	Sprite(BYTE* l_image, int l_frameWidth, int l_frameHeight, int l_imageWidth, int l_imageHeight);
	~Sprite();

	void Draw(int l_x, int l_y, int l_frame, Rect& l_screenRect, BYTE* l_screen) const;

private:
	int m_frameWidth{ 0 };
	int m_frameHeight{ 0 };
	int m_imageHeight{ 0 };
	int m_imageWidth{ 0 };
	int m_colums{ 0 };
	BYTE* m_image{ nullptr };
};
