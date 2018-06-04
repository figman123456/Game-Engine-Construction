#pragma once
class TimeManager
{
public:
	static TimeManager& Instance()
	{
		if (!s_instance)
		{
			s_instance = new TimeManager();
		}

		return *s_instance;
	}

	void Update();
	const double DeltaTime() const ;

	void Destroy();

private:
	TimeManager(){}
	~TimeManager(){}

	static TimeManager* s_instance;

	double m_oldTime{ 0.0 };
	double m_newTime{ 0.0 };
};

