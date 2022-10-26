#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/VictoryPoints.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciation)
{
    VictoryPoints * victoryPointsmock = new VictoryPoints();
    BOOST_CHECK(1);
    
}