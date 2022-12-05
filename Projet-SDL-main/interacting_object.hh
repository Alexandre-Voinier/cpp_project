#pragma once

#include <set>
#include <iostream>
#include <string>

class interacting_object {
private:
    std::set<std::string> properties;

public:
    void add_property(const char*  key);
    bool has_property(const char* key);
    bool remove_property(const char* key);
    ~interacting_object() { };
};