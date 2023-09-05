#ifndef CONSTRUCTION_HPP
#define CONSTRUCTION_HPP
#include <cstdint>
#include "../include/raylib.h"
namespace moss{
struct paths{
    Vector2 *coords;
    int tam;
};
class Construction{
    public:
        Construction();
        virtual ~Construction();

        const bool getIsConnected() const;
        void setIsConnected(const bool& isConnected);;
        const int getRobots() const;
        void setRobots(const int& robots);
        const struct paths *getPaths() const;
        void setPaths(struct paths *paths, const int& numPaths);
    private:
        int robots;
        bool isConnected;
        struct paths *paths;
        int numPaths;
};
}
#endif
