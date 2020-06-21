#include "operations.h"
//#include <math.h>
//#include "defines.h"
//#include "object.h"

static void move_point(point_t &point, const struct move &mo)
{
    point.x += mo.dx;
    point.y += mo.dy;
    point.z += mo.dz;
    return;
}

int move_object(object_t &object, const struct move &mo)
{
    int err = check_object(object);
    if (err != OK)
        return err;
    for (int i = 0; i < object.nodes_num; i++)
        move_point(object.nodes[i], mo);
    return err;
}

static void scale_point(point_t &point, const struct scale &sc)
{
    point.x = sc.kx * point.x + sc.xm * (1 - sc.kx);
    point.y = sc.ky * point.y + sc.ym * (1 - sc.ky);
    point.z = sc.kz * point.z + sc.zm * (1 - sc.kz);
    return;
}

int scale_object(object_t &object, const struct scale &sc)
{
    int err = check_object(object);
    if (err != OK)
        return err;
    for (int i = 0; i < object.nodes_num; i++)
        scale_point(object.nodes[i], sc);
    return err;
}
static struct trig count_trig(const struct rotate &ro)
{
    struct trig tg;
    tg.cos_x = cos(ro.dgx * PI / 180);
    tg.cos_y = cos(ro.dgy * PI / 180);
    tg.cos_z = cos(ro.dgz * PI / 180);
    tg.sin_x = sin(ro.dgx * PI / 180);
    tg.sin_y = sin(ro.dgy * PI / 180);
    tg.sin_z = sin(ro.dgz * PI / 180);
    return tg;
}

// Тут ошибка в логике. Надо создать буферы и работать с ними. тк если поменять в первой строчке
// point.x то потом будет учитываться оно а не начальное.
static void rotate_point(point_t &point, const struct trig &tg, const struct rotate &ro)
{
    point.x = ro.xc + (point.x - ro.xc) * tg.cos_z - (point.y - ro.yc) * tg.sin_z;
    point.y = ro.yc + (point.x - ro.xc) * tg.sin_z + (point.y - ro.yc) * tg.cos_z;
    point.y = ro.yc + (point.y - ro.yc) * tg.cos_x - (point.z - ro.zc) * tg.sin_x;
    point.z = ro.zc + (point.z - ro.zc) * tg.cos_x + (point.y - ro.yc) * tg.sin_x;
    point.x = ro.xc + (point.x - ro.xc) * tg.cos_y + (point.z - ro.zc) * tg.sin_y;
    point.z = ro.zc + (point.z - ro.zc) * tg.cos_y - (point.x - ro.xc) * tg.sin_y;
    return;
}

int rotate_object(object_t &object, const struct rotate &ro)
{
    int err = check_object(object);
    if (err != OK)
        return err;
    struct trig tg = count_trig(ro);
    for (int i = 0; i < object.nodes_num; i++)
        rotate_point(object.nodes[i], tg, ro);
    return err;
}
