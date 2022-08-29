//
// Created by pkulik0 on 29/08/2022.
//

#include "dimensions.h"
#include "ncurses.h"

dimensions_t dimensions_sub(dimensions_t lhs, dimensions_t rhs) {
    return (dimensions_t){lhs.x-rhs.x, lhs.y-rhs.y};
}

dimensions_t dimensions_add(dimensions_t lhs, dimensions_t rhs) {
    return (dimensions_t){lhs.x+rhs.x, lhs.y+rhs.y};
}

dimensions_t dimensions_scale(dimensions_t dim, double scale) {
    return (dimensions_t){dim.x*scale, dim.y*scale};
}