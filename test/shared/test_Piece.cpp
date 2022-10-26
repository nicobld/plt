#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Piece.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestInstanciationPiece)
{
    Piece * pieceMock = new Piece();
    BOOST_CHECK(1);
}