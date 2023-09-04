#include "../headers/Construction.hpp"

moss::Construction::Construction()
    :robots{5}, isConnected{false}, path{new std::vector<std::vector<Vector2>>}{
}

moss::Construction::~Construction(){
    delete path;
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

Vector2 **moss::Construction::getPath() const{
    return this->path;
}
void moss::Construction::setPath(Vector2 **path){
    this->path = path;
}
