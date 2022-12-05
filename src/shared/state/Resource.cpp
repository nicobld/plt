#include "Resource.h"

namespace state{

Resource::Resource(){}

Resource::Resource(ResourceType resourceType) : resourceType(resourceType) {
    this->number = 0;
}

Resource::Resource(ResourceType resourceType, int number) : resourceType(resourceType), number(number) {}
    
}
