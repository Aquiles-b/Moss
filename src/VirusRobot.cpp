#include "../headers/VirusRobot.hpp"

moss::VirusRobot::VirusRobot(Texture2D *spr, const int& frames, const int& speedAnimation,
  const Vector2& offset, const int& frameHeight, const Vector2& posi, const float& speed,
  Vector2 *path, const int& tamPath): Robot{spr, frames, speedAnimation, offset, frameHeight,
    posi, speed, path, tamPath}{
    this->setColor(GREEN);
}

moss::VirusRobot:: ~VirusRobot(){}
