#ifndef CONSTRUCTION_HPP
#define CONSTRUCTION_HPP
#include "ComponentModel.hpp"
#include "GameController.hpp"
#include <cstdint>
namespace moss{
class Construction{
    public:
        Construction();
        virtual ~Construction();

        const bool getIsConnected() const;
        void setIsConnected(const bool& isConnected);;
        const int getRobots() const;
        void setRobots(const int& robots);
        Vector2 **getPath() const;
        void setPath(Vector2 **path);
    private:
        int robots;
        bool isConnected;
        struct paths *paths;
        int numPath;
};
}
#endif
