#include "freq_list.h"
#include <malloc.h>
#include <stdlib.h>

status_t rebalance_list(freq_list_t *list)
{
    if (list == NULL)
        return null_pointer_error;

    while (list->next && list->amount > list->next->amount)
    {
        unsigned long tmp_amount = list->next->amount;
        char tmp_flag = list->next->flag;
        char tmp_letter = list->next->letter;
        
        list->next->amount = list->amount;
        list->next->flag = list->flag;
        list->next->letter = list->letter;

        list->amount = tmp_amount;
        list->flag = tmp_flag;
        list->letter = tmp_letter;

        list = list->next;
    }
    return ok;
}

static status_t add_element(freq_list_t **list, char sim)
{
    status_t res = ok;
    if (list == NULL)
        res = null_pointer_error;
    else
    {
        freq_list_t *add = malloc(sizeof(freq_list_t));
        if (add == NULL)
            res = memory_error;
        else
        {
            add->flag = 0;
            add->amount = 1;
            add->letter = sim;
            add->next = *list;
            *list = add;
        }
    }
    return res;
}

static freq_list_t *find_element(freq_list_t *list, char sim)
{
    while (list && list->letter != sim)
        list = list->next;
    return list;
}

status_t increase_freq(freq_list_t **list, char sim)
{
    status_t res = ok;
    if (list == NULL)
        res = null_pointer_error;
    else
    {
        freq_list_t *ptr = find_element(*list, sim);
        if (ptr == NULL)
            res = add_element(list, sim);
        else
        {
            ptr->amount++;
            rebalance_list(ptr);
        }
    }
    return res;
}

void free_list(freq_list_t **list)
{
    if (list)
    {
        freq_list_t *head = *list;
        while (head)
        {
            freq_list_t *next = head->next;
            free(head);
            head = next;
        }
        *list = NULL;
    }
}

int list_size(freq_list_t const *list)
{
    int size = 0;
    while (list)
    {
        size++;
        list = list->next;
    }
    return size;
}