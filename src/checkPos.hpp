#pragma once

#include <memory>
#include <vector>

#include "MovingObject.hpp"

bool checkPos(int posX, int posY, std::vector<std::shared_ptr<MovingObject>> objects);
