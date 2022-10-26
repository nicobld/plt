#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Resource.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationResource)
{
    Resource * resourceMock = new Resource(ResourceType::Lumber);
    BOOST_CHECK(1);
}