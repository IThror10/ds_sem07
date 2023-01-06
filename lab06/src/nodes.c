#include <malloc.h>
#include "nodes.h"

nodes_t* alloc_nodes(int size)
{
    if (size <= 0)
        size = 1;

    nodes_t *nodes = malloc(2 * sizeof(int) + size * sizeof(node_t));
    if (nodes)
    {
        nodes->size = size;
        for (int i = 0; i < size; i++) {
            node_t *cur = (nodes->data) + i;
            cur->flags = 0;
            cur->left = 0;
            cur->right = 0;
        }
    }
    return nodes;
}

void free_nodes(nodes_t *nodes)
{
    free(nodes);
}


status_t build_nodes(nodes_t **nodes, freq_list_t *list) {
    if (nodes == NULL || list == NULL)
        return null_pointer_error;

    status_t res = ok;
    int size = list_size(list);
    nodes_t *tnodes = alloc_nodes(size - 1);
    if (nodes == NULL)
        res = memory_error;
    else if (size == 1)
    {
        node_t *cur = tnodes->data;
        cur->left = list->letter;
        cur->flags = LEAF_LEFT;
        *nodes = tnodes;
    }
    else
    {
        *nodes = tnodes;
        for (int i = tnodes->size - 1; i >= 0; i--)
        {
            node_t *cur = (tnodes->data) + i;
            cur->left = list->letter;
            cur->right = list->next->letter;
            cur->flags = list->flag ? TREE_LEFT : 0;
            cur->flags |= list->next->flag ? TREE_RIGHT : 0;

            list->next->amount += list->amount;
            list = list->next;
            list->letter = i;
            list->flag = 1;
            rebalance_list(list);
        }
    }
    return res;
}

static node_t *build_path(nodes_t *nodes, char index, char depth)
{
    node_t *node = (nodes->data) + index;
    if (depth <= 0)
    {
        if (!LEFT_IS_FREE(node->flags) && !RIGHT_IS_FREE(node->flags))
            node = NULL;
    }
    else
    {
        node_t *tmp = NULL;
        if (LEFT_IS_TREE(node->flags))
            tmp = build_path(nodes, node->left, depth - 1);
        else if (LEFT_IS_FREE(node->flags))
        {
            node->left = nodes->size++;
            node->flags |= TREE_LEFT;
            tmp = build_path(nodes, node->left, depth - 1);
        }

        if (tmp == NULL)
        {
            if (RIGHT_IS_TREE(node->flags))
                tmp = build_path(nodes, node->right, depth - 1);
            else if (RIGHT_IS_FREE(node->flags))
            {
                node->right = nodes->size++;
                node->flags |= TREE_RIGHT;
                tmp = build_path(nodes, node->right, depth - 1);
            }
        }
        node = tmp;
    }
    return node;
}

status_t put_node(nodes_t *nodes, char sim, char depth)
{
    node_t *node = build_path(nodes, 0, depth - 1);
    if (node == NULL)
        return null_pointer_error;

    if (LEFT_IS_FREE(node->flags))
    {
        node->flags |= LEAF_LEFT;
        node->left = sim;
    }
    else
    {
        node->flags |= LEAF_RIGHT;
        node->right = sim;
    }
    return ok;
}