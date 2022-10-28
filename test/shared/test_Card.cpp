#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Card.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationCard)
{
    Card * cardMock = new Card();
    BOOST_CHECK(1);
}