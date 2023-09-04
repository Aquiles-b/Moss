#include "../headers/GameController.hpp"

moss::GameController::GameController(const int64_t& floorId, const int& heightCellIso): floorId{floorId},
                        numPaths{4}, paths{new struct paths[4]}, heightCellIso{heightCellIso}{
    for (int i = 0; i < this->numPaths; ++i)
        this->paths[i].coords = new Vector2[128];
}

moss::GameController::~GameController(){
    for (int i = 0; i < this->numPaths; ++i)
        delete[] this->paths[i].coords;
    delete[] this->paths;
}

void moss::GameController::updatePaths(const struct cellMatrix **mtx, 
                            std::vector<struct cellMatrix> *construCoords, const int& size){
    std::vector<struct cellMatrix>::iterator it = construCoords->begin();
    int pathIndex{0};
    for ( ; it != construCoords->end(); ++it){
        findPath(it->lOrigin, it->cOrigin, mtx, size, pathIndex);
        it->constInfo->setPath(*this->path);
        pathIndex = 0;
    }
}

bool moss::GameController::findPath(const int& l, const int& c, const struct cellMatrix **mtx,
                                    const int& size, int& pathIndex){
    Vector2 coordIso{0};
    if (isInsideLimit(l, c, size) && isAllowedWalk(l, c, size, mtx)){
        if (mtx[l][c].value == -3){
            matrixToMapCoord(l, c, coordIso);
            this->paths[0][0] = coordIso;
        }
    }
    if (isInsideLimit(l+1, c, size) && isAllowedWalk(l+1, c, size, mtx))
        return findPath(l+1, c, mtx, size, pathIndex);
    if (isInsideLimit(l-1, c, size) && isAllowedWalk(l-1, c, size, mtx))
        return findPath(l-1, c, mtx, size, pathIndex);
    if (isInsideLimit(l, c+1, size) && isAllowedWalk(l, c+1, size, mtx))
        return findPath(l, c+1, mtx, size, pathIndex);
    if (isInsideLimit(l, c-1, size) && isAllowedWalk(l, c-1, size, mtx))
        return findPath(l, c-1, mtx, size, pathIndex);

    return false;
}

void moss::GameController::matrixToMapCoord(const int& l, const int& c, Vector2& coordIso) const{
    coordIso.x = (c - l) * this->heightCellIso;
    coordIso.y = (c + l) * this->heightCellIso / 2.0f;
}

void moss::GameController::mapToMatrixCoord(const float& x, const float& y, int& l, int& c) const{
    l = -ceil((x * 0.5f - y) / this->heightCellIso);
    c = floor((x * 0.5f + y) / this->heightCellIso);
}

bool moss::GameController::isInsideLimit(const int& l, const int& c, const int& size) const{
    if (l >= 0 && l < size && c >= 0 && c < size)
        return true;
    return false;
}

bool moss::GameController::isAllowedWalk(const int& l, const int& c, const int& size, const struct cellMatrix **mtx) const{
    if (mtx[l][c].value == -3 || mtx[l][c].value == this->floorId)
        return true;
    return false;
}
