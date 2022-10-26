#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Special.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationSpecial)
{
    Special * specialMock = new Special();
    BOOST_CHECK(1);
}