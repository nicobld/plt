#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Knight.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationKnight)
{
    Knight * knightMock = new Knight();
    BOOST_CHECK(1);
}