#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "Animation.hpp"
#include <cstdint>
namespace moss{
class Component{
    public:
        Component(const std::string& imgAf, const std::string& imgBf, const int& frames, const Vector2& posi, const int& speed,
                  const int& width, const int& height, const Vector2& offset);
        Component(const std::string& img, const std::string& imgBf, const int& frames, const Vector2& posi, const int& speed,
                  const int& width, const int& height);
        Component(const std::string& img, const int& frames, const Vector2& posi, const int& speed, const int& width,
                const int& height);
        virtual ~Component();

        const int64_t& getId() const;
        const Texture2D& getImg() const;
        const int& getWidth() const;
        const int& getHeight() const;
        const moss::Animation *getSprite() const;

        virtual void updateAfter(Vector2& coord, const Color& c);
        virtual void updateBefore(Vector2& coord, const Color& c);
    private:
        static int64_t nextId;
        int64_t id;
        moss::Animation *spriteBf;
        moss::Animation *spriteAf;
        int width;
        int height;
        Vector2 posi;
};
}
#endif
