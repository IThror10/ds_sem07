#include <stdio.h>
#include <string.h>
#include "common.hpp"

int main(int argc, char **argv)
{
    if (argc < 3)
        return -1;

    char *key = argv[2];
    FILE *lib = fopen(argv[1], "rb+");
    
    int i = 0, rc;
    bool found = false;
    do
    {
        char sym = ' ';
        rc = fread(&sym, sizeof(char), 1, lib);
        if (rc == 1)
        {
            if (sym == KEY_MESSAGE[0])
                i = 1;
            else if (sym == KEY_MESSAGE[i])
                i++;
            else
                i = 0;
                
            if (i == KEY_LEN)
                found = true;
        }
    } while (rc == 1 && !found);

    if (found)
    {
        long pos = ftell(lib);
        fseek(lib, 0, SEEK_CUR);
        fwrite(key, strlen(key), 1, lib);
    }
    fclose(lib);
    return 0;
}