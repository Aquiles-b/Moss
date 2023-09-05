#ifndef CELL_MATRIX_HPP
#define CELL_MATRIX_HPP
#include "Construction.hpp"
namespace moss{
struct cellMatrix{
    int value;
    int lOrigin;
    int cOrigin;
    moss::Construction *constInfo;
};
}
#endif
