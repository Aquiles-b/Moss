#include "../headers/Construction.hpp"

moss::Construction::Construction()
    :robots{5}, isConnected{false}{
}

moss::Construction::~Construction(){}

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
