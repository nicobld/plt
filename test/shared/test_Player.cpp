#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Player.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(PlayerInstanciation)
{
    Player * playermock = new Player("test");
    BOOST_CHECK_EQUAL(playermock->getName(), "test");
}