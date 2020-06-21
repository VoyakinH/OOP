#include "cdio.h"
//#include "object.h"
//#include "defines.h"
//#include <cstdlib>
//#include <cstdio>

static int open_file(FILE **f, const char *name)
{
    int err = OK;
    if (!name)
        err =  OPEN_FILE_ERR;
    *f = fopen(name, "r");
    if (!f && err == OK)
        err =  OPEN_FILE_ERR;
    return err;
}

static int read_num_from_file(int &nodes_num, int &links_num, FILE *f)
{
    int err = OK;
    if (fscanf(f, "%d %d", &nodes_num, &links_num) != 2)
        err =  FILE_INCORRECT;
    return err;
}

static int check_nums(const int &nodes_num, const int &links_num)
{
    int err = OK;
    if (nodes_num <= 0)
        err =  POINTS_INCORR;
    if (err == OK && links_num <= 0)
        err =  LINKS_INCORR;
    return err;
}

static int alloc_points(point_t **nodes, const int &nodes_num)
{
    *nodes = (point_t*)malloc(nodes_num * sizeof(point_t));
    int err = OK;
    if (!*nodes)
        err = ALLOCATION_ERR;
    return err;
}

static int alloc_links(link_t **links, const int &links_num)
{
    *links = (link_t*)malloc(links_num * sizeof(link_t));
    int err = OK;
    if (!*links)
        err = ALLOCATION_ERR;
    return err;
}

static int read_points_from_file(point_t *nodes, const int &nodes_num, FILE *f)
{
    int err = alloc_points(&nodes, nodes_num);
    for (int i = 0; err == OK && i < nodes_num; i++)
        if (fscanf(f, "%f %f %f", &nodes[i].x, &nodes[i].y, &nodes[i].z) != 3)
            err =  FILE_INCORRECT;
    return err;
}

static int read_links_from_file(link_t *links, const int &links_num, FILE *f)
{
    int err = alloc_links(&links, links_num);
    for (int i = 0; err == OK && i < links_num;  i++)
        if (fscanf(f, "%d %d", &links[i].p_1, &links[i].p_2) != 2)
            err = FILE_INCORRECT;
    return err;
}

static int check_links(const object_t &object)
{
    link_t *links = object.links;
    int err = OK;
    for (int i = 0; err == OK && i < object.links_num; i++)
        if (links[i].p_1 < 0 || links[i].p_2 < 0
                || links[i].p_1 > object.nodes_num - 1 || links[i].p_2 > object.nodes_num)
            err =  LINKS_CONTAIN_INCORR_POINTS;
    return err;
}

static void clear_points(point_t *points)
{
    free(points);
}

static void copy_model(object_t &object, object_t &new_obj)
{
    object = new_obj;
}

int load_file(object_t &object, const struct load_file &lf)
{
    FILE *f = NULL;
    if (open_file(&f, lf.file_name) != OK)
        return OPEN_FILE_ERR;

    object_t new_obj = init();
    int err = read_num_from_file(new_obj.nodes_num, new_obj.links_num, f);
    if (err == OK)
        err = check_nums(new_obj.nodes_num, new_obj.links_num);
    if (err == OK)
        err = read_points_from_file(new_obj.nodes, new_obj.nodes_num, f);
    if (err != OK)
        clear_points(new_obj.nodes);
    if (err == OK)
        err = read_links_from_file(new_obj.links, new_obj.links_num, f);
    if (err == OK)
        err = check_links(object);
    if (err == OK)
        copy_model(object, new_obj);
    if (err != OK)
        delete_object(new_obj);
    if (f != NULL)
        fclose(f);
    return err;
}
