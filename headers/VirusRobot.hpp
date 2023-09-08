#ifndef VIRUS_ROBOT_HPP
#define VIRUS_ROBOT_HPP
#include "Robot.hpp"
namespace moss{
class VirusRobot: public Robot{
    public:
        VirusRobot(Texture2D *spr, const int& frames, const int& speedAnimation,
          const Vector2& offset, const int& frameHeight, const Vector2& posi, const float& speed,
          Vector2 *path, const int& tamPath);
        virtual ~VirusRobot();
    private:
};
}

#endif
