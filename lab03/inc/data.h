#ifndef __DATA_H__
#define __DATA_H__

    typedef unsigned char byte_t;
    typedef unsigned int word_t;

    typedef struct
    {
        word_t words[4];
        int size;
    } block_t;

#endif //__DATA_H__