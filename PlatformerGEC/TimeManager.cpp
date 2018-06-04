#include "TimeManager.h"
#include "HAPI_lib.h"

TimeManager* TimeManager::s_instance = nullptr;


void TimeManager::Update()
{
	m_oldTime = m_newTime;
	m_newTime = HAPI->GetTime();
}
const double TimeManager::DeltaTime() const
{
	return (m_newTime - m_oldTime) / 1000;
}

void TimeManager::Destroy()
{
	delete s_instance;
}