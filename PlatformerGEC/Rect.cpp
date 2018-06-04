#include "Rect.h"
#include <algorithm>

void Rect::ClipTo(const Rect &other)
{
	m_left = std::max(m_left, other.m_left);
	m_top = std::max(m_top, other.m_top);
	m_right = std::min(m_right, other.m_right);
	m_bottom = std::min(m_bottom, other.m_bottom);
}

void Rect::Translate(int x, int y)
{
	m_top += y;
	m_bottom += y;
	m_right += x;
	m_left += x;
}

void Rect::Clamp()
{
	if (m_left < 0)
		m_left = 0;
	if (m_top < 0)
		m_top = 0;
}

bool Rect::Contains(const Rect &other)
{
	if (m_left < other.m_left && m_right > other.m_right && m_top < other.m_top && m_bottom > other.m_bottom)
		return true;
	
	return false;
}

bool Rect::NotIn(const Rect &other)
{
	if (m_right < other.m_left || m_left > other.m_right || m_bottom < other.m_top || m_top > other.m_bottom)
		return true;

	return false;
}

bool Rect::Intersects(const Rect &other)
{
	if (m_left < other.m_right &&  m_right > other.m_left &&  m_top < other.m_bottom && m_bottom > other.m_top)
		return true;
	return false;
}

