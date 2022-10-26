#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/TileBeach.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationTileBeach)
{
    TileBeachType * tileBeachTypeEx = new TileBeachType("some_path_to_indicate");
    TileBeach * tileBeachMock = new TileBeach(*tileBeachTypeEx);

    BOOST_CHECK(1);
}