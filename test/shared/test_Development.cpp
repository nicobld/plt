#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Development.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationDevelopment)
{
    bool keep = true;
    Development developmentmock = new Development(keep);
    BOOST_CHECK_EQUAL(keep, true);
}