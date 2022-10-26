#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Monopoly.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationMonopoly)
{
    Monopoly * MonopolyMock = new Monopoly();
    BOOST_CHECK(1);
}