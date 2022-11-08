#include "Development.h"

namespace state{

Development::Development(DevelopmentType developmentType): developmentType(developmentType) {
    if (developmentType == Knight || developmentType == VictoryPointsCard)
        keep = true;
    else
        keep = false;
}

}
