#include <set>
#include <string>

#include "InteractionObject.hpp"

using namespace std;

set<string> InteractionObject::getProperties() {
    return _properties;
}

void InteractionObject::setProperties(set<string> newProperties) {
    _properties = newProperties;
}
