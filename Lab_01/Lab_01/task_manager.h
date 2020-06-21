#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "object.h"
#include "defines.h"
#include "cdio.h"
#include "draw.h"
#include "operations.h"

enum task_num
{
    INIT,
    LOAD_FILE,
    DRAW,
    MOVE,
    SCALE,
    ROTATE,
    QUIT
};

struct request
{
    task_num act;
    union
    {
        struct load_file lf;
        struct draw dr;
        struct move mo;
        struct scale sc;
        struct rotate ro;
    };
};

int task_manager(request task);

#endif // TASK_MANAGER_H
