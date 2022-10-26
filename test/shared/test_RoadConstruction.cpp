#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/RoadConstruction.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationRoadConstruction)
{
    RoadConstruction * roadConstructionMock = new RoadConstruction();
    BOOST_CHECK(1);
}