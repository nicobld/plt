#include "Port.h"

namespace state {

Port::Port(int exchangeRate, ResourceType resourceType, int x1, int y1, int x2, int y2): exchangeRate(exchangeRate), resourceType(resourceType) {
    position[0].x = x1;
    position[0].y = y1;
    position[1].x = x2;
    position[1].y = y2;
}

}