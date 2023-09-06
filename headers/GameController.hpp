#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP
#include <cstdint>
#include <iostream>
#include <vector>
#include "../include/raylib.h"
#include "../include/raymath.h"
#include "Construction.hpp"
#include "cellMatrix.hpp"
namespace moss{
class GameController{
    public:
        GameController(const int64_t& floorId, const int& heightCellIso, const int& size);
        virtual ~GameController();

        const bool& getIsChanged() const;
        void setIsChanged(const bool& isChanged);

        void updatePaths(struct cellMatrix **mtx, std::vector<struct cellMatrix> *construCoords);
        void mapToMatrixCoord(const float& x, const float& y, int& l, int& c) const;
        void matrixToMapCoord(const int& l, const int& c, Vector2& coordIso) const;
    private:
        int64_t floorId;
        int heightCellIso;
        struct paths *paths;
        short **footPrint;
        int size;
        int numPaths;
        bool isChanged;

        void findPath(const int& l, const int& c, struct cellMatrix **mtx,
                        int& pathIndex, int& numCoord, short direction);
        bool isInsideLimit(const int& l, const int& c) const;
        bool isAllowedWalk(const int& l, const int& c, struct cellMatrix **mtx) const;
        void addCoordPath(const int& l, const int& c, const int& pathIndex, int& numCoord);
        void clearFootPrint();
        void clearPaths();
};
}
#endif
