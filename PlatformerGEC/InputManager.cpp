#include "InputManager.h"
#include "Utils.h"

InputManager* InputManager::s_instance = nullptr;

CVector2 InputManager::GetGamepadAnalogLeft()
{
	CVector2 scaledInput{ Utils::SmoothStep(-32768.0f, 32767.0f, m_leftAxisRaw.x), Utils::SmoothStep(-32768.0f, 32767.0f, m_leftAxisRaw.y) };

	if (scaledInput.Length() < DEADZONE)
	{
		return CVector2{ 0.0f, 0.0f };
	}
	else
	{
		scaledInput.NormaliseInPlace();
		CVector2 result = CVector2{ scaledInput * ((scaledInput.Length() - DEADZONE) / (1.0f - DEADZONE)) };
		return result;
	}

}
CVector2 InputManager::GetGamepadAnalogRight()
{
	CVector2 scaledInput = CVector2{ Utils::SmoothStep(-32768.0f, 32767.0f, m_rightAxisRaw.x), Utils::SmoothStep(-32768.0f, 32767.0f, m_rightAxisRaw.y)};

	if (scaledInput.Length() < DEADZONE)
	{
		return CVector2{ 0.0f, 0.0f };
	}
	else
	{
		scaledInput.NormaliseInPlace();
		CVector2 result = CVector2{ scaledInput * ((scaledInput.Length() - DEADZONE) / (1.0f - DEADZONE)) };
		return result;
	}
}

void InputManager::Update()
{
	if (HAPI->GetControllerData(0, &m_controllerData))
	{
		m_leftAxisRaw = CVector2{ (float)m_controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X], (float)m_controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] };
		m_rightAxisRaw = CVector2{ (float)m_controllerData.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X], (float)m_controllerData.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] };
		m_gamepadExsists = true;
	}

	else
	{
		m_leftAxisRaw = CVector2{ 0.0f, 0.0f };
		m_rightAxisRaw = CVector2{ 0.0f, 0.0f };
	}

	HAPI->GetKeyboardData(&m_keyboardData);
	HAPI->GetMouseData(&m_mouseData);

	m_mousePos = CVector2{ (float)m_mouseData.x, (float)m_mouseData.y };


} 

void InputManager::Destroy()
{
	delete s_instance;
}