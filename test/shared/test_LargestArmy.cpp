#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/LargestArmy.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationLargestArmy)
{
    LargestArmy * largestArmyMock = new LargestArmy();
    BOOST_CHECK(1);
}
