#include <iostream>
#ifndef MAPA_HPP
#define MAPA_HPP
namespace moss{
class Mapa{
    public:
        Mapa();
        Mapa(const unsigned int& lines, const unsigned int& columns);
        virtual ~Mapa();

        short **getMapa() const;
        void imprimeMapa() const;
        
    private:
        const unsigned lines;
        const unsigned columns;
        short **mapa;
};
}
#endif
