#include "../headers/Hud.hpp"

moss::Hud::Hud(const std::string& editModeComps, const std::string& hammer)
    : editModeComps{LoadTexture(editModeComps.c_str())}, hammer{LoadTexture(hammer.c_str())}{
}

moss::Hud::~Hud(){
    UnloadTexture(this->editModeComps);
}

void moss::Hud::draw(const Vector2& mouse, const bool& editMode) const{
    int posiRec{0};
    if (editMode){
        switch (this->selected){
            case 0:
                posiRec = 0;
                break;
            case 1:
                posiRec = 80;
                break;
            case 2:
                posiRec = 163;
                break;
            case -1: 
                posiRec = 245;
                DrawTextureV(this->hammer, {mouse.x - 10, mouse.y - 10}, WHITE);
                break;
        }
        DrawRectangle(posiRec, 0, 80, 80, WHITE);
        DrawTextureV(this->editModeComps, {0.0f, 0.0f}, WHITE);
    }
}

void moss::Hud::update(){
    if (IsKeyPressed(KEY_ONE))
        this->selected = 0;
    else if (IsKeyPressed(KEY_TWO))
        this->selected = 1;
    else if (IsKeyPressed(KEY_THREE))
        this->selected = 2;
    else if (IsKeyPressed(KEY_FOUR))
        this->selected = -1;
}

const int moss::Hud::getSelected() const{
    return this->selected;
}
