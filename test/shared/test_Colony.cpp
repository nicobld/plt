#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Colony.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationColony)
{
    Player * playermock = new Player("test");
    Colony * colonymock = new Colony(*playermock);
    BOOST_CHECK(1);
}