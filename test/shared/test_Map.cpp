#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Map.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationMap)
{
    Map mapMock = Map();
    BOOST_CHECK(1);
}