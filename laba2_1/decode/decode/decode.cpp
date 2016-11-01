#include "stdafx.h"
using namespace std;

int main()
{
	string htmlString;
	while (getline(cin, htmlString))
	{
		htmlString = HtmlDecode(htmlString);
		cout << htmlString << endl;
	}
	return 0;
}
