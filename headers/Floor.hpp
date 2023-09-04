#ifndef FLOOR_HPP
#define FLOOR_HPP
#include "Component.hpp"
namespace moss{
class Floor : public Component{
    public:
        Floor(const std::string& img);
        virtual ~Floor();

        void updateBefore(Vector2& coord, const Color& c) override;
        void updateAfter(Vector2& coord, const Color& c) override;
    private:
};
}
#endif
