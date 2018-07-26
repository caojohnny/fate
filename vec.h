#ifndef FATE_VEC_H
#define FATE_VEC_H

typedef struct {
    double x;
    double y;
    double z;
} vec;

/**
 * Performs a scalar multiplication on the given vector.
 *
 * @return a new vector containing the multiplied values
 */
vec vec_mul(double, vec);

/**
 * Adds the values of two vectors together.
 *
 * @return a new vector containing the added values
 */
vec vec_add(vec, vec);

/**
 * Prints the given vector to stdout.
 */
void vec_print(vec);

#endif /* FATE_VEC_H */
