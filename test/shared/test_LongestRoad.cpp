#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/LongestRoad.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationLongestRoad)
{
    LongestRoad * longestRoadMock = new LongestRoad();
    BOOST_CHECK(1);
}