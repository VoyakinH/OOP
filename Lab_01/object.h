#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>
#include "defines.h"

struct point_t
{
    float x;
    float y;
    float z;
};

struct link_t
{
    int p_1;
    int p_2;
};

struct object_t
{
    int nodes_num;
    int links_num;
    point_t *nodes;
    link_t *links;
};

object_t init();
int check_object(const object_t &object);
void delete_object(object_t& object);


#endif // OBJECT_H
