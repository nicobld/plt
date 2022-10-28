#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Tile.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationTile)
{
    Tile * tileMock = new Tile();
    BOOST_CHECK(1);
}