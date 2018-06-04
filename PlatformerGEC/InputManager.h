#pragma once

#include<vector>

#include"HAPI_lib.h"
#include"Vector2.h"

class InputManager
{
public:
	static InputManager& Instance()
	{
		if (!s_instance)
		{
			s_instance = new InputManager();
		}

		return *s_instance;
	}

	void Update();

	CVector2 GetGamepadAnalogLeft();
	CVector2 GetGamepadAnalogRight();

	void Destroy();

private:
	InputManager(){}
	~InputManager(){}

	const float DEADZONE = 0.25f;

	static InputManager* s_instance;

	CVector2 m_leftAxisRaw{ 0.0f, 0.0f };
	CVector2 m_rightAxisRaw{ 0.0f, 0.0f };

	CVector2 m_mousePos{ 0.0f, 0.0f };

	HAPI_TControllerData  m_controllerData;
	HAPI_TKeyboardData m_keyboardData;
	HAPI_TMouseData m_mouseData;

	bool m_gamepadExsists;
};

