#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <math.h>
#include "defines.h"
#include "object.h"

struct move
{
    float dx;
    float dy;
    float dz;
};

struct scale
{
    float kx;
    float ky;
    float kz;
    float xm;
    float ym;
    float zm;
};

struct rotate
{
    int dgx;
    int dgy;
    int dgz;
    float xc;
    float yc;
    float zc;
};

struct trig
{
    float cos_x;
    float cos_y;
    float cos_z;
    float sin_x;
    float sin_y;
    float sin_z;
};

int move_object(object_t &object, const struct move &mo);
int scale_object(object_t &object, const struct scale &sc);
int rotate_object(object_t &object, const struct rotate &ro);

#endif // OPERATIONS_H
