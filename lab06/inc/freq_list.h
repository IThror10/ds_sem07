#ifndef __FREQ_LIST_H__
#define __FREQ_LIST_H__

    #include "status.h"

    typedef struct freq_list_t freq_list_t;
    struct freq_list_t {
        char flag;
        char letter;
        unsigned long amount;
        freq_list_t *next;
    };

    status_t increase_freq(freq_list_t **list, char sim);
    status_t rebalance_list(freq_list_t *list);
    int list_size(freq_list_t const *list);
    void free_list(freq_list_t **list);

#endif //__FREQ_LIST_H__