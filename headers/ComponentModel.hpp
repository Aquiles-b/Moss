#ifndef COMPONENT_MODEL_HPP
#define COMPONENT_MODEL_HPP
#include "Animation.hpp"
#include <cstdint>
namespace moss{
class ComponentModel{
    public:
        ComponentModel();
        ComponentModel(const std::string& imgBf, const std::string& imgAf, const int& frames, const int& speed,
                  const int& width, const int& height, const Vector2& offset, const bool& isTile, const int& lDoor,
                  const int& cDoor);
        ComponentModel(const std::string& imgBf, const std::string& imgAf, const int& frames, const int& speed,
                  const int& width, const int& height, const bool& isTile);
        ComponentModel(const std::string& img, const int& frames, const int& speed, const int& width,
                const int& height, const bool& isTile);
        virtual ~ComponentModel();

        const int64_t& getId() const;
        void setId(const int64_t& id);
        const int& getWidth() const;
        void setWidth(const int& width);
        const int& getHeight() const;
        void setHeight(const int& height);
        moss::Animation *getSpriteBf() const;
        void setSpriteBf(moss::Animation *spriteBf);
        moss::Animation *getSpriteAf() const;
        void setSpriteAf(moss::Animation *spriteAf);
        const bool& getIsTile() const;
        void setIsTile(const bool& isTile);
        const int& getCDoor() const;
        void setCDoor(const int& cDoor);
        const int& getLDoor() const;
        void setLDoor(const int& lDoor);

        virtual void updateAfter(Vector2& coord, const Color& c);
        virtual void updateBefore(Vector2& coord, const Color& c);
    private:
        static int64_t nextId;
        int64_t id;
        moss::Animation *spriteBf;
        moss::Animation *spriteAf;
        int width;
        int height;
        int lDoor;
        int cDoor;
        bool isTile;
};
}
#endif
