#include "stdafx.h"
#include "CarSet.h"
#include "RemoteControl.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CCar & car, std::istream & input, std::ostream & output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "EngineOn", [this](istream & strm) {
			return TurnOn(strm);
		} },
		{ "EngineOff", bind(&CRemoteControl::TurnOff, this, _1) },
		{ "Info", bind(&CRemoteControl::Info, this, _1) },
		{ "SetGear", bind(&CRemoteControl::SetGear, this, _1) },
		{ "SetSpeed", bind(&CRemoteControl::SetSpeed, this, _1) }
})
{
}

		bool CRemoteControl::HandleCommand()
		{
			string commandLine;
			getline(m_input, commandLine);
			istringstream strm(commandLine);

			string action;
			strm >> action;

			auto it = m_actionMap.find(action);

			if (it != m_actionMap.end())
			{
				return it->second(strm);
			}

			return false;
		}

		bool CRemoteControl::TurnOn(std::istream & /*args*/)
		{
			if (m_car.TurnOnEngine())
			{
				m_output << "Car engine is turned on" << endl;
			}
			else
			{
				m_output << "Can't enable engine" << endl;
			}

			return true;
		}

		bool CRemoteControl::TurnOff(std::istream & /*args*/)
		{
			if (m_car.TurnOffEngine())
			{
				m_output << "Car engine is turned off" << endl;
			}
			else
			{
				m_output << "Can't disable engine" << endl;
			}

			return true;
		}

		bool CRemoteControl::Info(std::istream & /*args*/)
		{
			string info = (m_car.EngineIsTurnedOn()) ? ("Car engine is turned on\n") : ("Car engine is turned off\n");
			info += "Direction: ";

			switch (m_car.GetDirection())
			{
			case Directions::BACKWARD:
			{
				info += "back\n";
				break;
			}
			case Directions::NONE:
			{
				info += "stationary\n";
				break;
			}
			case Directions::FORWARD:
			{
				info += "forward\n";
				break;
			}
			default:
				break;
			}

			info += "Gear: " + to_string(m_car.GetGear()) + "\nSpeed: " + to_string(abs(m_car.GetSpeed())) + " km/h\n";
			m_output << info;

			return true;
		}

		bool CRemoteControl::SetGear(std::istream & args)
		{
			int gear;

			args >> gear;

			if (m_car.SetGear(gear))
			{
				cout << "Select gear " << gear << "\n";
			}
			else
			{
				cout << "Can't select gear\n";
			}

			return true;
		}

		bool CRemoteControl::SetSpeed(std::istream & args)
		{
			int speed;

			if (args >> speed)
			{
				if (m_car.SetSpeed(speed))
				{
					cout << "Select speed " << abs(speed) << "\n";
				}
				else
				{
					cout << "Can't select speed\n";
				}
			}
			else
			{
				cout << "Unknown command!\n";
			}

			return true;
		}