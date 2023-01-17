#include "stdio.h"
#include "enigma.hpp"
#include "status.hpp"


int main(int argc, char* argv[])
{
    status_t res = ok;

    if (argc < 3)
        res = argv_error;
    else
    {
        FILE *src, *dst;
        if ((src = fopen(argv[1], "rb")) == NULL)
            res = unknown_file;
        else if ((dst = fopen(argv[2], "wb")) == NULL)
        {
            fclose(src);
            res = unknown_file;
        }
        else
        {
            char sim;
            Enigma enigma = Enigma(0x12345678);
            while (fread(&sim, sizeof(char), 1, src) == 1)
            {
                sim = enigma.cipher(sim);
                fwrite(&sim, sizeof(char), 1, dst);
            }

            fclose(src);
            fclose(dst);
        }
    }

    return res;
}