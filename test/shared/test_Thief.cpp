#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Thief.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationThief)
{
    Thief * thiefMock = new Thief();
    BOOST_CHECK(1);
}