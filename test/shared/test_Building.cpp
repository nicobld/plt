#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Building.h"

using namespace ::state;

BOOST_AUTO_TEST_SUITE(TestSuiteBuilding)

    BOOST_AUTO_TEST_CASE(TestInstanciationBuilding)
    {
        Player playermock = new Player("player");
        Building building = new Building(playermock);
        BOOST_CHECK_EQUAL(building.getPlayer(), "player");
    }

BOOST_AUTO_TEST_SUITE_END();