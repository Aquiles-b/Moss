#include "../headers/Construction.hpp"

using namespace moss;

moss::Construction::Construction(const int& lDoor, const int& cDoor)
    :robots{3}, isConnected{false}, paths{new struct paths[4]}, numPaths{4}, color{GRAY},
    cDoor{cDoor}, lDoor{lDoor}{
    for (int i = 0; i < this->numPaths; ++i)
        this->paths[i].coords = new Vector2[128];
}

moss::Construction::~Construction(){
    for (int i = 0; i < this->numPaths; ++i)
        delete[] paths[i].coords;
    delete[] paths;
}

const bool moss::Construction::getIsConnected() const{
    return this->isConnected;
}

void moss::Construction::setIsConnected(const bool& isConnected){
    this->isConnected = isConnected;
}

const int moss::Construction::getRobots() const{
    return this->robots;
}
void moss::Construction::setRobots(const int& robots){
    this->robots = robots;
}

struct paths *moss::Construction::getPaths() const{
    return this->paths;
}

void moss::Construction::setPaths(struct paths *paths, const int& numPaths){
    for (int i = 0; i < numPaths; ++i){
        this->paths[i].tam = paths[i].tam;
        for (int j = 0; j < paths[i].tam; ++j){
            this->paths[i].coords[j].x = paths[i].coords[j].x;
            this->paths[i].coords[j].y = paths[i].coords[j].y;
        }
    }
}

void moss::Construction::increaseOneRobot(){
    ++this->robots;
}

const Color& moss::Construction::getColor() const{
    return this->color;
}

void moss::Construction::setColor(const Color& color){
    this->color = color;
}

const int& moss::Construction::getCDoor() const{
    return this->cDoor;
}

void moss::Construction::setCDoor(const int& cDoor){
    this->cDoor = cDoor;
}

const int& moss::Construction::getLDoor() const{
    return this->lDoor;
}

void moss::Construction::setLDoor(const int& lDoor){
    this->lDoor = lDoor;
}
