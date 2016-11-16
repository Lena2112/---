#pragma once
enum class Directions
{
	BACKWARD = -1,
	NONE = 0,
	FORWARD = 1
};

enum Gear
{
	REVERSE = -1,
	NEUTRAL = 0,
	FIRST = 1,
	SECOND = 2,
	THIRD = 3,
	FOURTH = 4,
	FIFTH = 5
};

class CCar
{
public:
	bool EngineIsTurnedOn() const;
	int GetSpeed() const;
	int GetGear() const;
	Directions  GetDirection() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
private:
	Gear m_gear = Gear::NEUTRAL;
	bool m_engineIsTurnedOn = false;
	int m_speed = 0;
	Directions m_direction;
};