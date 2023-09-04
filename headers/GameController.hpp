#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP
#include <cstdint>
#include <vector>
#include "Map.hpp"
namespace moss{
struct paths{
    Vector2 *coords;
    int tam;
};
class GameController{
    public:
        GameController(const int64_t& floorId, const int& heightCellIso);
        virtual ~GameController();

        void updatePaths(const struct cellMatrix **mtx, std::vector<struct cellMatrix> *construCoords,
                            const int& size);
        void mapToMatrixCoord(const float& x, const float& y, int& l, int& c) const;
        void matrixToMapCoord(const int& l, const int& c, Vector2& coordIso) const;
    private:
        int64_t floorId;
        int heightCellIso;
        bool findPath(const int& l, const int& c, const struct cellMatrix **mtx, const int& size, int& pathIndex);
        bool isInsideLimit(const int& l, const int& c, const int& size) const;
        bool isAllowedWalk(const int& l, const int& c, const int& size, const struct cellMatrix **mtx) const;
        struct paths *paths;
        int numPaths;
};
}
#endif
