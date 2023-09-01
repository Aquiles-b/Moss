#ifndef ROBOT_HPP
#define ROBOT_HPP
#include "Animation.hpp"
namespace moss{
class Robot{
    public:
        Robot(const std::string& spr, const int& frames, const int& speed,
          const Vector2& offset, const int& frameHeight, const Vector2& posi);
        virtual ~Robot();

        void update();
    private:
        moss::Animation *sprite;
        Vector2 posi;
        int speed;
        int heightIndex;
};
}
#endif
