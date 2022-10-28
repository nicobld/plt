#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Invention.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationInvention)
{
    Invention * inventionMock = new Invention();
    BOOST_CHECK(1);
}