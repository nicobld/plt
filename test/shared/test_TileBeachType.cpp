#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/TileBeachType.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationTileBeachType)
{
    TileBeachType * tileBeachTypeEx = new TileBeachType("some_path");

    BOOST_CHECK(1);
}