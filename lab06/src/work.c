#include "work.h"
#include "codes.h"

static status_t meta_out(FILE *dst, codes_t *codes)
{
    if (dst == NULL || codes == NULL)
        return null_pointer_error;
    
    int size = codes->size;
    fwrite(&size, sizeof(int), 1, dst);
    fwrite(&codes->size, sizeof(char), 1, dst);

    for (int i = 0; i < size; i++)
    {
        fwrite(&(codes->data[i].sim), sizeof(char), 1, dst);
        fwrite(&(codes->data[i].bits), sizeof(char), 1, dst);
    }
    return ok;
}

static status_t translate_file(FILE *src, FILE *dst, nodes_t *nodes)
{
    codes_t *codes = NULL;
    status_t res = create_codes(&codes, nodes);
    if (res == ok)
        res = meta_out(dst, codes);
    if (res == ok)
    {
        rewind(src);
        char read, str[65];
        str[0] = (char) 0;
        int amount = 0, bits = 0;
        while (!feof(src) && fread(&read, sizeof(char), 1, src) == 1)
        {
            amount++;
            bits = write_code(str, read, codes, bits);
            
            if (bits > 7)
            {
                fwrite(str, sizeof(char), bits / 8, dst);
                str[0] = str[bits / 8];
                bits %= 8;
            }
        }
        if (bits)
            fwrite(str, sizeof(char), 1, dst);

        rewind(dst);
        fwrite(&amount, sizeof(int), 1, dst);
    }
    free_codes(codes);
    return res;
}

static status_t create_freq_table(FILE *src, freq_list_t **freq)
{
    status_t res = ok;
    if (freq == NULL || src == NULL)
        res = null_pointer_error;
    else
    {
        char read;
        freq_list_t *list = NULL;
        
        while (!feof(src) && fread(&read, sizeof(char), 1, src) == 1 && res == ok)
            res = increase_freq(&list, read);

        if (res != ok)
            free_list(&list);
        else
            *freq = list;
    }
    return res;
}

status_t squeeze(FILE *src, FILE *dst)
{
    status_t res = ok;
    if (src == NULL || dst == NULL)
        res = no_such_file;
    else 
    {
        freq_list_t *freq = NULL;
        nodes_t *nodes = NULL;

        res = create_freq_table(src, &freq);
        if (res == ok)
            res = build_nodes(&nodes, freq);

        if (res == ok)
            translate_file(src, dst, nodes);
        
        free_list(&freq);
        free_nodes(nodes);
    }
    return res;
}

nodes_t *read_nodes(FILE *src)
{
    char chars = 0;
    fread(&chars, sizeof(char), 1, src);

    nodes_t *nodes = alloc_nodes(chars - 1);
    if (nodes)
    {
        nodes->size = 1;
        for (; chars > 0; chars--)
        {
            char read[2];
            fread(read, sizeof(char), 2, src);
            put_node(nodes, read[0], read[1]);
        }
    }
    return nodes;
}

status_t unsqueeze(FILE *src, FILE *dst)
{
    status_t res = ok;
    if (src == NULL || dst == NULL)
        res = no_such_file;
    else
    {
        int amount = 0;
        fread(&amount, sizeof(int), 1, src);

        nodes_t *nodes = read_nodes(src);
        if (nodes == NULL)
            res = memory_error;
        else
        {
            node_t *node = nodes->data;
            char bits = 0, read;
            while (amount > 0)
            {
                if (bits == 0)
                {
                    bits = 8;
                    fscanf(src, "%c", &read);
                }

                char bit = 1 & (read >> --bits);
                if (bit && LEFT_IS_TREE(node->flags))
                    node = (nodes->data) + node->left;
                else if (bit)
                {
                    amount--;
                    fwrite(&node->left, sizeof(char), 1, dst);
                    node = nodes->data;
                }
                else if (RIGHT_IS_TREE(node->flags))
                    node = (nodes->data) + node->right;
                else
                {
                    amount--;
                    fwrite(&node->right, sizeof(char), 1, dst);
                    node = nodes->data;
                }
            }
        }
        free_nodes(nodes);
    }
    return res;    
}