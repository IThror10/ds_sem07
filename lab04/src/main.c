#include "work.h"
#include <string.h>

int main(int argc, char **argv)
{
    status_t res = ok;
    if (argc != 5)
        res = argv_error;
    else
    {
        FILE *src, *dst, *key;
        if ((src = fopen(argv[2], "rb")) == NULL)
            res = unknown_file;
        else if ((dst = fopen(argv[3], "wb")) == NULL)
        {
            res = unknown_file;
            fclose(src);
        }
        else if ((key = fopen(argv[4], "r")) == NULL)
        {
            res = unknown_file;
            fclose(src);
            fclose(dst);
        }
        else
        {
            if (!strcmp(argv[1], "encrypt"))
                res = encrypt_file(src, dst, key);
            else if (!strcmp(argv[1], "decrypt"))
                res = decrypt_file(src, dst, key);
            else
                res = unknown_command;

            fclose(src);
            fclose(dst);
            fclose(key);
        }
    }

    if (res != ok)
        print_error_status(res);
    return res;
}