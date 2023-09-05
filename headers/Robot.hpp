#ifndef ROBOT_HPP
#define ROBOT_HPP
#include "Animation.hpp"
namespace moss{
class Robot{
    public:
        Robot(const std::string& spr, const int& frames, const int& speedAnimation,
          const Vector2& offset, const int& frameHeight, const Vector2& posi, const float& speed,
          Vector2 *path, const int& tamPath);
        virtual ~Robot();

        const bool& getReached() const;

        void update();
    private:
        moss::Animation *sprite;
        Vector2 posi;
        Vector2 *path;
        int tamPath;
        int vertexIndex;
        float speed;
        int heightIndex;
        int hsp;
        int vsp;
        bool reached;
};
}
#endif
