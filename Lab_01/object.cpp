#include "object.h"
//#include <cstdlib>
//#include "defines.h"

object_t init()
{
    object_t object;
    object.links_num = 0;
    object.nodes_num = 0;
    object.links = NULL;
    object.nodes = NULL;
    return object;
}

int check_object(const object_t &object)
{
    if (!object.nodes || !object.links)
        return ARR_UNINITIALIZED;
    if (object.nodes_num <= 0)
        return POINTS_INCORR;
    if (object.links_num <= 0)
        return LINKS_INCORR;
    return OK;
}

void delete_object(object_t &object)
{
    free(object.nodes);
    free(object.links);
    object.nodes_num = 0;
    object.links_num = 0;
    return;
}
