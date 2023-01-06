#ifndef __CODES_H__
#define __CODES_H__

    #include "status.h"
    #include "nodes.h"

    typedef struct
    {
        char bits;
        char sim;
        unsigned char *string;
    } code_t;

    typedef struct
    {
        int size;
        code_t data[];
    } codes_t;
    
    status_t add_code(codes_t *codes, unsigned char *str, int bits, char sim);
    int write_code(char *str, char sim, codes_t *codes, int bits);
    status_t create_codes(codes_t **codes, nodes_t *nodes);
    codes_t *alloc_codes(int size);
    void free_codes(codes_t *codes);

#endif //__CODES_H__