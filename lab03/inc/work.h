#ifndef __WORK_H__
#define __WORK_H__

    #include <stdio.h>
    #include "status.h"

    status_t encrypt_file(FILE *src, FILE *dst);
    status_t decrypt_file(FILE *src, FILE *dst);

#endif //__WORK_H__
