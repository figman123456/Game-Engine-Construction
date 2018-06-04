#include "Graphics.h"
#include "Sprite.h"

Graphics* Graphics::s_instance = nullptr;

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
}

//Graphics Functions
bool Graphics::Initialize(int l_width, int l_height)
{
	if (!HAPI->Initialise(&l_width, &l_height))
	{
		HAPI->UserMessage("Failed to initialize HAPI!", "ERROR");
		return false;
	}

	m_screen = HAPI->GetScreenPointer();
	m_screenRect.m_right = l_width;
	m_screenRect.m_bottom = l_height;
	
	return true;
}
void Graphics::Destroy()
{
	for (auto sprite : m_sprites)
	{
		delete sprite;
	}

	delete s_instance;
}

//Sprite Functions
int Graphics::CreateSprite(std::string l_filePath, int l_frameWidth, int l_frameHeight)
{
	BYTE* image{ nullptr };
	int width{ 0 };
	int height{ 0 };
	if (!HAPI->LoadTexture(l_filePath, &image, &width, &height))
	{
		HAPI->UserMessage("Could not load image: " + l_filePath, "Error!");
		delete[] image;
		return -1;
	}
	m_nextID++;
	Sprite* newSprite = new Sprite(image, l_frameWidth, l_frameHeight, width, height);
	m_sprites.push_back(newSprite);
	return m_nextID;
} 
void Graphics::DrawSprite(int l_id, int l_x, int l_y, int l_frame)
{
	if (l_id < 0)
		return;
	m_sprites[l_id]->Draw(l_x, l_y, l_frame,  m_screenRect, m_screen);
}

//Draw Functions
void Graphics::Clear()
{
	memset(m_screen, 0, m_screenRect.GetWidth() * m_screenRect.GetHeight() * 4);
}