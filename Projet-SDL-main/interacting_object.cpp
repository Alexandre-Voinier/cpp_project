#include "interacting_object.hh"

void interacting_object::add_property(const char* key) {
    this->properties.insert(key);
}

bool interacting_object::has_property(const char* key) {
    if (this->properties.find(key) == this->properties.end()) {
        return false;
    }
    return true;
}

bool interacting_object::remove_property(const char* key) {
    return this->properties.erase(key);
}