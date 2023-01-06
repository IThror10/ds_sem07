#ifndef __NODES_H__
#define __NODES_H__

    #include "freq_list.h"
    #include "status.h"

    #define TREE_LEFT 0x1
    #define TREE_RIGHT 0x10
    #define LEAF_LEFT 0x2
    #define LEAF_RIGHT 0x20
    
    #define LEFT_IS_TREE(flag) ((flag) & 0x1)
    #define RIGHT_IS_TREE(flag) ((flag) & 0x10)
    #define LEFT_IS_FREE(flag) (!((flag) & 0x3))
    #define RIGHT_IS_FREE(flag) (!((flag) & 0x30))

    typedef struct {
        char flags;
        char left;
        char right;
    } node_t;

    typedef struct {
        int size;
        node_t data[];
    } nodes_t;

    nodes_t* alloc_nodes(int size);
    void free_nodes(nodes_t *nodes);
    status_t put_node(nodes_t *nodes, char sim, char depth);
    status_t build_nodes(nodes_t **nodes, freq_list_t *freq);

#endif //__NODES_H__