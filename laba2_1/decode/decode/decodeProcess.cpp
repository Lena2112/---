#include "stdafx.h"

using namespace std;
string ChangeString(string & strHtml, const string &searchStr, char changeChar)
{
	string newStr = "";
	size_t beginPosition = 0;
	size_t findPosition = strHtml.find(searchStr);

	while ((findPosition != string::npos))
	{
		newStr += strHtml.substr(beginPosition, findPosition - beginPosition);
		newStr += changeChar;
		beginPosition = findPosition + searchStr.length();
		findPosition = strHtml.find(searchStr, beginPosition);
	}

	return newStr += strHtml.substr(beginPosition);
}

string HtmlDecode(string & htmlString)
{
	map <string, char> mapDecode =
	{
		{ "&quot;", '\"' },
		{ "&apos;", '\'' },
		{ "&lt;", '<' },
		{ "&gt;", '>' },
		{ "&amp;", '&' }
	};
	for (auto i = mapDecode.begin(); i != mapDecode.end(); ++i)
	{
		htmlString = ChangeString(htmlString, i->first, i->second);
	}
	return htmlString;
}
