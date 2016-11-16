#include "stdafx.h"
#include "Dictionary.h"

using namespace std;

int main(int argc, char *argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (argc == 2)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage: mini_dictionary.exe <dictionary file>\n";
		return 1;
	}
	string dictionaryFileName = "dictionary.txt";
	if (!dictionaryFileName.empty())
	{
		Dictionary dictionary = GetDictionaryFromFile(dictionaryFileName);
		StartTranslation(dictionary, dictionaryFileName);
	}
	else
	{
		cout << "Empty file name!\n";
		return 1;
	}
	return 0;
}