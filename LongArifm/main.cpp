#include "long_arifm.h"
#include <boost\test\unit_test.hpp>

#define BOOST_TEST_CASE(testBigInteger)

using namespace LA;

BOOST_AUTO_TEST_CASE(testBigInteger) 
{
	big_integer a, b, res;
	a.set("-7489375693457938");
	b.set("2355295");

	res = a + b;
	BOOST_CHECK_EQUAL(res.toString(), "-7489375691102643");
	res = a - b;
	BOOST_CHECK_EQUAL(res.toString(), "-7489375695813233");
	res = a * b;
	BOOST_CHECK_EQUAL(res.toString(), "-17639689123923014081710");
	res = a / b;
	BOOST_CHECK_EQUAL(res.toString(), "-3179803674");
	system("pause");
}
