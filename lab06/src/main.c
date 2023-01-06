#include <string.h>
#include "work.h"

int main(int argc, char **argv)
{
    status_t res = ok;
    
    if (argc < 4)
        res = wrong_args;
    else
    {
        FILE *src, *dst;
        src = fopen(argv[2], "rb");
        dst = fopen(argv[3], "wb");
        
        if (!strcmp(argv[1], "squeeze"))
            res = squeeze(src, dst);
        else if (!strcmp(argv[1], "unsqueeze"))
            res = unsqueeze(src, dst);
        else
            res = uknown_command;

        fclose(src);
        fclose(dst);
    } 

    return res;
} 