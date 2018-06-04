#pragma once

class Rect
{
public:

	Rect(){}
	Rect(int l_top, int l_left, int l_bottom, int l_right) : m_top(l_top), m_left(l_left), m_bottom(l_bottom), m_right(l_right){}

	int m_top{ 0 };
	int m_right{ 0 };
	int m_left{ 0 };
	int m_bottom{ 0 };

	int GetWidth(){ return m_right - m_left; }
	int GetHeight(){ return m_bottom - m_top; }

	void Translate(int x, int y);
	void ClipTo(const Rect &other);
	void Clamp();

	bool Contains(const Rect &other);
	bool NotIn(const Rect &other);
	bool Intersects(const Rect &other);
};