#include "codes.h"
#include <malloc.h>

status_t add_code(codes_t *codes, unsigned char *str, int bits, char sim)
{
    if (codes == NULL || str == NULL || bits == 0)
        return null_pointer_error;

    status_t res = ok;
    int bytes = (bits + 7) / 8;
    unsigned char *tmp = malloc(sizeof(unsigned char) * bytes);
    if (tmp == NULL)
        res = memory_error;
    else
    {
        for (int i = 0; i < bytes; i++)
            tmp[i] = str[i];
        if (bits % 8)
            tmp[bytes - 1] &= (0xFF << (8 - bits % 8));
        
        code_t *code = (codes->data) + codes->size;
        code->bits = bits;
        code->sim = sim;
        code->string = tmp;

        codes->size++;
    }
    return res;
}

static status_t fill_codes(codes_t *codes, nodes_t *nodes, char index, unsigned char *str, char bits)
{
    status_t res = ok;
    if (nodes == NULL || str == NULL)
        res = null_pointer_error;
    
    node_t *cur = (nodes->data) + index;
    str[bits / 8] |= 0x80 >> (bits % 8);
    if (res == ok)
    {
        if (LEFT_IS_TREE(cur->flags))
            res = fill_codes(codes, nodes, cur->left, str, bits + 1);
        else
            res = add_code(codes, str, bits + 1, cur->left);
    }

    str[bits / 8] ^= 0x80 >> (bits % 8);
    if (res == ok)
    {
        if (RIGHT_IS_TREE(cur->flags))
            res = fill_codes(codes, nodes, cur->right, str, bits + 1);
        else
            res = add_code(codes, str, bits + 1, cur->right);
    }
    return res;
}

static code_t *find_simb_code(codes_t *codes, char sim)
{
    code_t *code = codes->data;
    while (code->sim != sim)
        code++;
    return code;
}

int write_code(char *str, char sim, codes_t *codes, int bits)
{
    char offset = bits % 8;
    code_t *code = find_simb_code(codes, sim);
    if (code)
    {
        str += bits / 8;
        bits += code->bits;
        for (int i = 0; i < (code->bits + 7) / 8; i++)
        {
            str[i] |= (code->string[i] >> offset);
            str[i + 1] = (code->string[i]) << (8 - offset);
        }
    }
    return bits;
}

status_t create_codes(codes_t **codes, nodes_t *nodes)
{
    if (nodes == NULL || codes == NULL)
        return null_pointer_error;

    status_t res = ok;
    codes_t *tmp = alloc_codes(nodes->size + 1);
    if (tmp == NULL)
        res = memory_error;
    else
    {
        unsigned char string[64];
        res = fill_codes(tmp, nodes, 0, string, 0);
        if (res == ok)
            *codes = tmp;
        else
            free_codes(tmp);
    }
    return res;
}

codes_t *alloc_codes(int size)
{
    codes_t *tmp = malloc(sizeof(codes_t) + sizeof(code_t) * size);
    if (tmp != NULL)
        tmp->size = 0;
    return tmp;
}

void free_codes(codes_t *codes)
{
    if (codes)
    {
        for (int i = 0; i < codes->size; i++)
            free(codes->data[i].string);
        free(codes);
    }
}