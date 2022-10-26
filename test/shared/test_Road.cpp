#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Road.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationRoad)
{
    Player * playerMock = new Player("test");
    Road * roadMock = new Road(*playerMock);
    BOOST_CHECK(1);
}