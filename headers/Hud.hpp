#ifndef HUD_HPP
#define HUD_HPP
#include <iostream>
#include <vector>
#include "../include/raylib.h"
namespace moss{
class Hud{
    public:
        Hud(const std::string& editModeComps, const std::string& hammer);
        virtual ~Hud();

        const int getSelected() const;

        void draw(const Vector2& mouse, const bool& editMode) const;
        void update(const Vector2& mouse, const bool& editMode);
        
    private:
        Texture2D editModeComps;
        Texture2D hammer;
        int selected;

        void updateSelected(const Vector2& mouse);
        int mouseChoose(const Vector2& mouse);
};
}
#endif
