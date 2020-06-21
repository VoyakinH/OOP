#include "draw.h"
//#include <QGraphicsScene>
//#include <QGraphicsView>
//#include "defines.h"
//#include "object.h"

static void create_scene(const int w, const int h, struct draw dr)
{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(-w / 2, -h / 2, w - 2, h - 2);
    dr.QGV->setScene(scene);
    return;
}

// Создать структуру и поместить туда qpen
static QPen create_pen()
{
    QPen penBlack(COLOR);
    return penBlack;
}

static void add_line(struct draw dr, const line_t line, const QPen pen)
{
    dr.QGV->scene()->addLine(line.x_1, line.y_1, line.x_2, line.y_2, pen);
    return;
}

int draw_object(const object_t &object, struct draw dr)
{
    int err = check_object(object);
    if (err != OK)
        return err;
    create_scene(dr.w, dr.h, dr);
    QPen pen = create_pen();
    point_t *nodes = object.nodes;
    link_t *links = object.links;
    for (int i = 0; i < object.links_num; i++)
    {
        line_t line;
        int ind_p1 = links[i].p_1;
        int ind_p2 = links[i].p_2;
        line.x_1 = nodes[ind_p1].x;
        line.y_1 = -nodes[ind_p1].y;
        line.x_2 = nodes[ind_p2].x;
        line.y_2 = -nodes[ind_p2].y;
        add_line(dr, line, pen);
    }
    return OK;
}
