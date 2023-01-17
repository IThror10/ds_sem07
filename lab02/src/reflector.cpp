#include "reflector.hpp"

Reflector::Reflector()
{
    bool flags[ALPH_SIZE];
    for (int i = 0; i < ALPH_SIZE; i++)
        flags[i] = true;

    for (int i = 0; i < ALPH_SIZE; i++)
    {
        if (flags[i])
        {
            int pos = rand() % ALPH_SIZE;
            while (!flags[pos] || pos == i)
                pos = (pos + 1) % ALPH_SIZE;
            
            data[pos] = i;
            data[i] = pos;

            flags[pos] = false;
            flags[i] = false;
        }
    }
}

unsigned char Reflector::reflect(unsigned char letter) const
{
    return data[letter];
}