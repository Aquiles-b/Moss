#include "../headers/Hud.hpp"

moss::Hud::Hud(const std::string& editModeComps, const std::string& hammer)
    : editModeComps{LoadTexture(editModeComps.c_str())}, hammer{LoadTexture(hammer.c_str())},
    selected{0}, editMode{false}{
}

moss::Hud::~Hud(){
    UnloadTexture(this->editModeComps);
    UnloadTexture(this->hammer);
}

void moss::Hud::draw(const Vector2& mouse) const{
    int posiRec{0};
    if (this->editMode){
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
void moss::Hud::updateSelected(const Vector2& mouse){
    if (IsKeyPressed(KEY_ONE))
        this->selected = 0;
    else if (IsKeyPressed(KEY_TWO))
        this->selected = 1;
    else if (IsKeyPressed(KEY_THREE))
        this->selected = 2;
    else if (IsKeyPressed(KEY_FOUR))
        this->selected = -1;
    this->selected = mouseChoose(mouse);
}

void moss::Hud::update(const Vector2& mouse){
    if (IsKeyPressed(KEY_E))
        this->editMode = !this->editMode;
    if (this->editMode)
        updateSelected(mouse);
}

int moss::Hud::mouseChoose(const Vector2& mouse){
    if (mouse.y > 80.0f)
        return this->selected;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if (mouse.x <= 323){
            if (mouse.x > 242)
                return -1;
            else if (mouse.x > 161)
                return 2;
            else if (mouse.x > 80)
                return 1;
            else 
                return 0;
        }
    }
    return this->selected;
}

const int moss::Hud::getSelected() const{
    return this->selected;
}

    const bool& moss::Hud::getEditMode() const{
    return this->editMode;
}

