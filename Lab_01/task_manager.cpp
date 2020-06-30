#include "task_manager.h"
//#include "defines.h"
//#include "cdio.h"
//#include "error_output.h"
//#include "draw.h"
//#include "operations.h"

int task_manager(request task)
{
    int  err = OK;
    static object_t object = init();

    switch (task.act)
    {
    case INIT:
        break;
    case LOAD_FILE:
        err = load_file(object, task.lf);
        break;
    case DRAW:
        err = draw_object(object, task.dr);
        break;
    case MOVE:
        err = move_object(object, task.mo);
        break;
    case SCALE:
        err = scale_object(object, task.sc);
        break;
    case ROTATE:
        err = rotate_object(object, task.ro);
        break;
    case QUIT:
        delete_object(object);
        break;
    default:
        err = UNKNOWN_COMMAND;
    }

    return err;
}
