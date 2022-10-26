#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Progress.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationProgress)
{
    Progress * progressMock = new Progress();
    BOOST_CHECK(1);
}