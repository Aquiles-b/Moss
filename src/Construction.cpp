#include "../headers/Construction.hpp"

using namespace moss;

moss::Construction::Construction(const int& lDoor, const int& cDoor)
    :robots{3}, isConnected{false}, paths{new struct paths[4]}, maxPaths{4}, numPaths{0}, color{GRAY},
    cDoor{cDoor}, lDoor{lDoor}{
    for (int i = 0; i < this->maxPaths; ++i){
        this->paths[i].coords = new Vector2[128];
        this->paths[i].tam = 0;
    }
}

moss::Construction::~Construction(){
    for (int i = 0; i < this->maxPaths; ++i)
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

struct paths moss::Construction::getRandomPath() const{
    return this->paths[0];
}

void moss::Construction::setPaths(struct paths *paths, const int& numPaths){
    this->numPaths = numPaths;
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

void moss::Construction::decreaseOneRobot(){
    --this->robots;
}

void moss::Construction::clearPaths(){
    for (int i = 0; i < this->numPaths; ++i)
        this->paths[i].tam = 0;
    this->numPaths = 0;
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
