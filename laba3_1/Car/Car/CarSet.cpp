#include "stdafx.h"
#include "CarSet.h"

bool CCar::EngineIsTurnedOn() const
{
	return m_engineIsTurnedOn;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

int CCar::GetGear() const
{
	return m_gear;
}

Directions CCar::GetDirection() const
{
	Directions direction;

	if (m_speed == 0)
	{
		direction = Directions::NONE;
	}
	else if (m_speed < 0)
	{
		direction = Directions::BACKWARD;
	}
	else if (m_speed > 0)
	{
		direction = Directions::FORWARD;
	}

	return direction;
}

bool CCar::TurnOnEngine()
{
	if (m_engineIsTurnedOn)
	{
		return false;
	}

	m_engineIsTurnedOn = true;

	return true;
}

bool CCar::TurnOffEngine()
{
	if (!m_engineIsTurnedOn || !(m_gear == 0 && m_speed == 0))
	{
		return false;
	}

	m_engineIsTurnedOn = false;

	return true;
}

bool CCar::SetGear(int gear)
{
	if (((!m_engineIsTurnedOn) && (gear != 0)) || (gear < -1) || (gear > 5))
	{
		return false;
	}

	bool switched = false;

	switch (gear)
	{
	case -1:
	{
		if ((m_speed == 0) && ((m_gear == Gear::NEUTRAL) || (m_gear == Gear::FIRST)))
		{
			m_gear = Gear::REVERSE;
			switched = true;
		}
		break;
	}
	case 0:
	{
		m_gear = Gear::NEUTRAL;
		switched = true;
		break;
	}
	case 1:
	{
		if (((m_gear == Gear::REVERSE) && (m_speed == 0)) ||
			((m_gear == Gear::NEUTRAL) && (m_speed >= 0) && (m_speed <= 30)) ||
			((m_direction == Directions::FORWARD) && (m_speed >= 0) && (m_speed <= 30)))
		{
			m_gear = Gear::FIRST;
			switched = true;
		}
		break;
	}
	case 2:
	{
		if ((m_speed >= 20) && (m_speed <= 50))
		{
			m_gear = Gear::SECOND;
			switched = true;
		}
		break;
	}
	case 3:
	{
		if ((m_speed >= 30) && (m_speed <= 60))
		{
			m_gear = Gear::THIRD;
			switched = true;
		}
		break;
	}
	case 4:
	{
		if ((m_speed >= 40) && (m_speed <= 90))
		{
			m_gear = Gear::FOURTH;
			switched = true;
		}
		break;
	}
	case 5:
	{
		if ((m_speed >= 50) && (m_speed <= 150))
		{
			m_gear = Gear::FIFTH;
			switched = true;
		}
		break;
	}
	}

	return switched;
}

bool CCar::SetSpeed(int speed) 
{
	if (!m_engineIsTurnedOn)
	{
		return false;
	}

	bool changed = false;

	if ((m_gear == Gear::REVERSE) && (speed <= 0) && (speed >= -20))
	{
		m_speed = speed;
		m_direction = (m_speed == 0) ? (Directions::NONE) : (Directions::BACKWARD);
		changed = true;
	}
	else if ((m_gear == Gear::NEUTRAL) && (speed <= m_speed))
	{
		m_speed = speed;
		if (speed == 0)
		{
			m_direction = Directions::NONE;
		}
		changed = true;
	}
	else if (((m_gear == Gear::FIRST) && (speed >= 0) && (speed <= 30)) ||
		((m_gear == Gear::SECOND) && (speed >= 20) && (speed <= 50)) ||
		((m_gear == Gear::THIRD) && (speed >= 30) && (speed <= 60)) ||
		((m_gear == Gear::FOURTH) && (speed >= 40) && (speed <= 90)) ||
		((m_gear == Gear::FIFTH) && (speed >= 50) && (speed <= 150)))
	{
		m_speed = speed;
		m_direction = Directions::FORWARD;
		changed = true;
	}

	return changed;
}