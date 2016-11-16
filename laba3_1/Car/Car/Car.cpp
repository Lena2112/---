#include "stdafx.h"
#include "RemoteControl.h"
#include "CarSet.h"


using namespace std;

int main()
{
	CCar car;
	CRemoteControl remoteControl(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
}