#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Game.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationGame)
{
    int nb_player = 4;
    Game * gamemock = new Game(nb_player);
    BOOST_CHECK_EQUAL(nb_player, 4);
}