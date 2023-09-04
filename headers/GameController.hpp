#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP
#include <cstdint>
#include <vector>
#include "Map.hpp"
namespace moss{
class GameController{
    public:
        GameController(const int64_t& floor);
        virtual ~GameController();

        void updatePaths(const struct cellMatrix& mtx, const std::vector<struct cellMatrix>& constructions) const;
    private:
        std::vector<Vector2> path;
};
}
#endif
