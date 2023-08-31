#ifndef FLOOR_HPP
#define FLOOR_HPP
#include "Component.hpp"
namespace moss{
class Floor : public Component{
    public:
        Floor(const std::string& img);
        virtual ~Floor();

        void update(Vector2& coord, const Color& c) override;
    private:
};
}
#endif
