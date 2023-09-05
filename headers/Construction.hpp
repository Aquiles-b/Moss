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
        Construction(const int& lDoor, const int& cDoor);
        virtual ~Construction();

        const bool getIsConnected() const;
        void setIsConnected(const bool& isConnected);;
        const int getRobots() const;
        void setRobots(const int& robots);
        const struct paths *getPaths() const;
        void setPaths(struct paths *paths, const int& numPaths);
        const Color& getColor() const;
        void setColor(const Color& color);
        const int& getCDoor() const;
        void setCDoor(const int& cDoor);
        const int& getLDoor() const;
        void setLDoor(const int& lDoor);
    private:
        int robots;
        bool isConnected;
        struct paths *paths;
        int numPaths;
        Color color;
        int lDoor;
        int cDoor;
};
}
#endif
