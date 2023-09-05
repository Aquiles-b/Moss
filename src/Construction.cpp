#include "../headers/Construction.hpp"

using namespace moss;

moss::Construction::Construction()
    :robots{5}, isConnected{false}, paths{new struct paths[4]}{
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

const struct paths *moss::Construction::getPaths() const{
    return this->paths;
}

void moss::Construction::setPaths(struct paths *paths, const int& numPaths){
    for (int i = 0; i < numPaths; ++i){
        this->paths[i].tam = paths[i].tam;
        for (int j = 0; j < paths[i].tam; ++j)
            this->paths[i].coords[j] = paths[i].coords[j];
    }
}
