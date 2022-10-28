#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/GameCards.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationGameCards)
{
    GameCards * gameCardsMock = new GameCards();
    BOOST_CHECK(1);
}