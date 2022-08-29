//
// Created by pkulik0 on 29/08/2022.
//

#ifndef ASDF_DIMENSIONS_H
#define ASDF_DIMENSIONS_H

typedef struct Dimensions {
    int x;
    int y;
} dimensions_t;

dimensions_t dimensions_sub(dimensions_t lhs, dimensions_t rhs);
dimensions_t dimensions_add(dimensions_t lhs, dimensions_t rhs);
dimensions_t dimensions_scale(dimensions_t dim, double scale);

#endif //ASDF_DIMENSIONS_H
