#pragma once

#include <memory>
#include <set>
#include <string>

class InteractionObject {
public:
    virtual void interact(std::shared_ptr<InteractionObject> const &secondObject) = 0;

    std::set<std::string> getProperties();
    void setProperties(std::set<std::string> newProperties);

protected:
    std::set<std::string> _properties;
};
