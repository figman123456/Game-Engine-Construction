#include <algorithm>

#include "Sprite.h"
#include "Rect.h"

Sprite::Sprite(BYTE* l_image, int l_frameWidth, int l_frameHeight, int l_imageWidth, int l_imageHeight)
{
	m_image = l_image;
	m_imageWidth = l_imageWidth;
	m_imageHeight = l_imageHeight;
	m_frameWidth = l_frameWidth;
	m_frameHeight = l_frameHeight;
	m_colums = l_imageWidth / l_frameWidth;
}

Sprite::~Sprite()
{
	delete[] m_image;
}

void Sprite::Draw(int l_x, int l_y, int l_frame, Rect& l_screenRect, BYTE* l_screen) const
{
	Rect newSourceRect{ 0, 0, m_frameHeight, m_frameWidth };

	newSourceRect.Translate(l_x, l_y);

	if (newSourceRect.NotIn(l_screenRect))
	{
		return;
	}

	if (l_screenRect.Contains(newSourceRect))
	{
		newSourceRect.Translate(-l_x, -l_y);
		newSourceRect.Translate((l_frame % m_colums) * m_frameWidth, (l_frame / m_colums) * m_frameHeight);

		const int endOfLineDestIncrement = (l_screenRect.GetWidth() - m_frameWidth) * 4;

		BYTE* destPtr = l_screen + (l_x + l_y*l_screenRect.GetWidth()) * 4;
		BYTE* sourcePtr = m_image + (newSourceRect.m_left + newSourceRect.m_top * m_imageWidth) * 4;

		for (int j = 0; j < m_frameHeight; j++)
		{
			for (int i = 0; i < m_frameWidth; i++)
			{
				BYTE alpha = sourcePtr[3];

				if (alpha == 255)
				{
					memcpy(destPtr, sourcePtr, 4);
				}
				else if (alpha == 0)
				{

				}
				else
				{
					destPtr[0] = destPtr[0] + ((alpha*(sourcePtr[0] - destPtr[0])) >> 8);
					destPtr[1] = destPtr[1] + ((alpha*(sourcePtr[1] - destPtr[1])) >> 8);
					destPtr[2] = destPtr[2] + ((alpha*(sourcePtr[2] - destPtr[2])) >> 8);
				}

				sourcePtr += 4;
				destPtr += 4;
			}
			sourcePtr += (m_imageWidth - m_frameWidth) * 4;
			destPtr += endOfLineDestIncrement;
		}
	}
	else
	{
		newSourceRect.ClipTo(l_screenRect);
		newSourceRect.Translate(-l_x, -l_y);

		l_x = std::max(l_x, 0);
		l_y = std::max(l_y, 0);

		newSourceRect.Translate((l_frame % m_colums) * m_frameWidth,(l_frame / m_colums) * m_frameHeight);

		const int endOfLineDestIncrement = (l_screenRect.GetWidth() - newSourceRect.GetWidth()) * 4;

		BYTE* destPtr = l_screen + (l_x + l_y*l_screenRect.GetWidth()) * 4;
		BYTE* sourcePtr = m_image + (newSourceRect.m_left + newSourceRect.m_top * m_imageWidth) * 4;

		for (int j = 0; j < newSourceRect.GetHeight(); j++)
		{
			for (int i = 0; i < newSourceRect.GetWidth(); i++)
			{
				BYTE alpha = sourcePtr[3];

				if (alpha == 255)
				{
						memcpy(destPtr, sourcePtr, 4);
				}
				else if (alpha == 0)
				{
					alpha = alpha;
				}
				else
				{
					destPtr[0] = destPtr[0] + ((alpha*(sourcePtr[0] - destPtr[0])) >> 8);
					destPtr[1] = destPtr[1] + ((alpha*(sourcePtr[1] - destPtr[1])) >> 8);
					destPtr[2] = destPtr[2] + ((alpha*(sourcePtr[2] - destPtr[2])) >> 8);
				}

				sourcePtr += 4;
				destPtr += 4;
				}
				sourcePtr += (m_imageWidth - newSourceRect.GetWidth()) * 4;
				destPtr += endOfLineDestIncrement;
			}
	}

	
}
