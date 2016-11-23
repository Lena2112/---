#include "stdafx.h"
#include "../Dictionary/Dictionary.h"

BOOST_AUTO_TEST_SUITE(IsWordInDictionary_function)
BOOST_AUTO_TEST_CASE(returns_true_if_word_is_in_dictionary)
{
	std::string word = "apple";
	Dictionary dictionary = {
		{ word, "яблоко" }
	};

	BOOST_CHECK(FindTranslation(word, dictionary));
}

BOOST_AUTO_TEST_CASE(returns_false_if_word_is_not_in_dictionary)
{
	std::string word = "banana";
	Dictionary dictionary = {
		{ "president", "президент" },
		{ "tomato", "помидор" }
	};

	BOOST_CHECK(!FindTranslation(word, dictionary));
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GetDictionaryFromFile_function)
BOOST_AUTO_TEST_CASE(returns_empty_dictionary_from_empty_file)
{
	Dictionary dictionary;
	BOOST_CHECK(dictionary == GetDictionaryFromFile("empty.txt"));
}

BOOST_AUTO_TEST_CASE(returns_some_correct_dictionary_from_some_correct_file)
{
	Dictionary dictionary = {
		{ "cat", "кот" },
		{ "dog", "собака" }
	};

	BOOST_CHECK(dictionary == GetDictionaryFromFile("dictionary-file.txt"));
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SaveDictionaryInFile_function)
BOOST_AUTO_TEST_CASE(saves_dictionary_changes_in_file_by_changing_file)
{
	remove("dictionary-changes.txt");
	std::string file = "dictionary-changes.txt";

	Dictionary dictionary1 = {
		{ "average", "средний" },
		{ "big", "большой" },
		{ "small", "маленький" }
	};

	SaveChangesToFile(dictionary1, file);
	Dictionary dictionary2 = GetDictionaryFromFile(file);
	BOOST_CHECK(dictionary1 == dictionary2);
}
BOOST_AUTO_TEST_SUITE_END()