#ifndef FLOOR_HPP
#define FLOOR_HPP
#include "Component.hpp"
namespace moss{
class Floor : public Component{
    public:
        Floor(const std::string& img);
        virtual ~Floor();

        void update(struct Vector2& coord) override;
    private:
};
}
#endif
