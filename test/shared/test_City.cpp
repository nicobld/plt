#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/City.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationCard)
{
    Player * playermock = new Player("test");
    City * city = new City(*playermock);
    BOOST_CHECK(1);
}