#include "stdafx.h"

#include "../decode/decode.h"

using namespace std;

bool StringsAreEqual(string const& x, string const& y)
{
	return x == y;
}

BOOST_AUTO_TEST_SUITE(ProcessDecodeTest)
//������,������� �� �������� ������������ ������
BOOST_AUTO_TEST_CASE(string_no_change)
{
	string str = "Fox in socks";
	str = HtmlDecode(str);
	BOOST_CHECK(StringsAreEqual(str, "Fox in socks"));
}
//������,������� �������� ��� ������������ ������

BOOST_AUTO_TEST_CASE(string_with_all_symbols)
{
	string str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	str = HtmlDecode(str);
	BOOST_CHECK(StringsAreEqual(str, "Cat <says> \"Meow\". M&M's"));
}
//������ ������

BOOST_AUTO_TEST_CASE(string_empty)
{
	string str = "";
	str = HtmlDecode(str);
	BOOST_CHECK(StringsAreEqual(str, ""));
}
BOOST_AUTO_TEST_SUITE_END()