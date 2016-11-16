#include "stdafx.h"
#include "Dictionary.h"

using namespace std;
using namespace boost;

static const string EXIT_DICTIONARY = "...";

bool IsEmptyFile(ifstream & file)
{
	return file.peek() == ifstream::traits_type::eof();
}

Dictionary GetDictionaryFromFile(string const&dictionaryFileName)
{
	Dictionary dictionary;
	ifstream dictionaryFile(dictionaryFileName);
	if (dictionaryFile.is_open() && !IsEmptyFile(dictionaryFile))
	{
		string buffer;
		while (getline(dictionaryFile, buffer))
		{
			vector<string> translation;
			boost::split(translation, buffer, boost::is_any_of(":"));
			dictionary.emplace(translation[0], translation[1]);
		}
	}
	else
	{
		std::cout << "Dictionary could not be opened and it will work with an empty dictionary\n";
	}
	return dictionary;
}

bool ProcessingNewWords(string &newWord, Dictionary &dictionary)
{
	cout << ">";
	string translationNewWord;
	getline(cin, translationNewWord);
	bool dictionaryHasChanged = false;
	if (!translationNewWord.empty())
	{
		dictionary.emplace(newWord, translationNewWord);
		dictionaryHasChanged = true;
		cout << "Слово " << newWord << " сохранено в словаре как " << translationNewWord << ".\n";
	}
	else
	{
		cout << "Слово " << newWord << " проигнорировано.\n";
	}
	return dictionaryHasChanged;
}

bool FindTranslation(string inputWord, Dictionary &dictionary)
{
	bool find = false;
	boost::optional<string> findWord;
	to_lower(inputWord);
	auto iterator = dictionary.find(inputWord);
	if (iterator != dictionary.end())
    {
		findWord = iterator->second;
		cout << iterator->second << endl;
		find = true;
	}
	if (!findWord)
	{
		for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
		{
			transform(it->second.begin(), it->second.end(), it->second.begin(), bind2nd(std::ptr_fun(&tolower<wchar_t>), locale("")));
			if (it->second == inputWord)
			{
				findWord = it->first;
				cout << it->first << endl;
				find = true;
			}
		}
	}
	return find;
}

std::string GetString(pair<std::string, std::string> translation)
{
	return  translation.first + ":" + translation.second;
}

void SaveChangesToFile(Dictionary const& dictionary, string const& dictionaryFileName)
{
	ofstream dictionaryFile(dictionaryFileName);
	std::transform(dictionary.begin(), dictionary.end(), std::ostream_iterator<std::string>(dictionaryFile, "\n"), GetString);
}

void StartTranslation(Dictionary &dictionary, string const&dictionaryFileName)
{
	string inputWord;
	string translatedWord;
	cout << ">";
	bool dictionaryHasChanged = false;
	while (getline(cin, inputWord) && (inputWord != EXIT_DICTIONARY))
	{
		if (!inputWord.empty())
		{
			if (!FindTranslation(inputWord, dictionary))
			{
				cout << "Неизвестное слово " << inputWord << ". Введите перевод или пустую строку для отказа.\n";
				dictionaryHasChanged = ProcessingNewWords(inputWord, dictionary);
			}
			cout << ">";
		}
		else
		{
			cout << ">";
		}
	}
	if (dictionaryHasChanged)
	{
		cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
		char save;
		cin >> save;
		save = tolower(save);
		if (save == 'y')
		{
			SaveChangesToFile(dictionary, dictionaryFileName);
			cout << "Изменения сохранены. До свидания." << endl;
		}
	}
}