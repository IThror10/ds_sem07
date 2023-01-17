#include "rotor.hpp"

Rotor::Rotor() : curTick(0)
{
    for (int tick = 0; tick < ALPH_SIZE; tick++)
    {
        bool flags[ALPH_SIZE];
        for (int i = 0; i < ALPH_SIZE; i++)
            flags[i] = true;

        for (int byte = 0; byte < ALPH_SIZE; byte++)
        {
            int i = rand() % ALPH_SIZE;
            while (!flags[i])
                i = (i + 1) % ALPH_SIZE;
            
            data[tick][byte].fwd = i;
            data[tick][i].bwd = byte;
            flags[i] = false;
        }
    }
}

unsigned char Rotor::commutateFwdLetter(unsigned char letter)
{
    return data[curTick][letter].fwd;
}

unsigned char Rotor::commutateBwdLetter(unsigned char letter)
{
    return data[curTick][letter].bwd;
}

bool Rotor::spinRotor()
{
    curTick = (curTick + 1) % ALPH_SIZE;
    return curTick == 0;
}

void Rotor::setPosition(int tick)
{
    curTick = tick % ALPH_SIZE;
}