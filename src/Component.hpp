#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "Animation.hpp"
namespace moss{
class Component{
    public:
        Component(const std::string& img, const int& frames, const Vector2& posi, const int& speed);
        virtual ~Component();

        const unsigned int& getId() const;
        const Texture2D& getSprite() const;

        virtual void update(struct Vector2& coord);
    private:
        static unsigned int nextId;
        unsigned int id;
        moss::Animation *sprite;
        int sizeInMap;
        Vector2 posi;
};
}
#endif
