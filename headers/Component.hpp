#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "Animation.hpp"
#include <cstdint>
namespace moss{
class Component{
    public:
        Component(const std::string& img, const int& frames, const Vector2& posi, const int& speed,
                  const int& width, const int& height);
        virtual ~Component();

        const int64_t& getId() const;
        const Texture2D& getSprite() const;
        const int& getWidth() const;
        const int& getHeight() const;

        virtual void update(struct Vector2& coord);
        bool insideLimits(const int& l, const int& c, const int& size) const;
    private:
        static int64_t nextId;
        int64_t id;
        moss::Animation *sprite;
        int width;
        int height;
        Vector2 posi;
};
}
#endif
