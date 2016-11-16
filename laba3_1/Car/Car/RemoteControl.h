#pragma once
#include <boost/noncopyable.hpp>
#include "stdafx.h"
using namespace std;
class CCar;

class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CCar & car, istream & input, ostream & output);
	bool HandleCommand();
private:
	bool TurnOn(istream & args);
	bool TurnOff(istream & args);
	bool Info(istream & args);
	bool SetGear(istream & args);
	bool SetSpeed(istream & args);
private:
	typedef map<string, function<bool(istream & args)>> ActionMap;

	CCar & m_car;
	istream & m_input;
	ostream & m_output;

	const ActionMap m_actionMap;
};