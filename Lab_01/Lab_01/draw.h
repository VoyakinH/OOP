#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "defines.h"
#include "object.h"

struct draw
{
    QGraphicsView *QGV;
    int h;
    int w;
};

struct line_t
{
    int x_1;
    int y_1;
    int x_2;
    int y_2;
};

int draw_object(const object_t &object, struct draw dr);

#endif // DRAW_H
