#include "stdafx.h"
#include "..\vector\VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// Функция ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	// Создает пустой вектор из пустого вектора
	BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	// вектор, минимальный элемент которого 0, превращает в вектор, состоящий из нулей
	BOOST_AUTO_TEST_CASE(does_not_change_vector_containing_no_positive_numbers)
	{
		vector<double> numbers = { 4, 0, 3, 6};
		ProcessVector(numbers);
		BOOST_CHECK(VectorsAreEqual(numbers , {0, 0, 0, 0}));
	}

	// при обработке вектора 
	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_several_positive_elements)
		// должен добавить их среднее арифметическое к каждому элементу
		BOOST_AUTO_TEST_CASE(should_add_their_average_to_each_element)
		{
			vector<double> numbers = { -1, 1, 2, 3 };
			ProcessVector(numbers);
			BOOST_CHECK(VectorsAreEqual(numbers, { -3, -2, -1, 1 }));
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()