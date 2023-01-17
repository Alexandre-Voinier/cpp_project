#include <memory>
#include <vector>

#include "MovingObject.hpp"

using namespace std;

// Helper function
// Check pos when creating an object in random pos
bool checkPos(int posX, int posY, vector<shared_ptr<MovingObject>> objects) {
    for (unsigned i = 0; i < objects.size(); i++) {
        int posX_2 = objects[i]->getPosX();
        int posY_2 = objects[i]->getPosY();
        if (posX_2 <= posX + OBJECT_WIDTH && 
            posX_2 >= posX - OBJECT_WIDTH &&
            posY_2 <= posY + OBJECT_HEIGHT &&
            posY_2 >= posY - OBJECT_HEIGHT) {
                return false;
        }
    }
    return true;
}
