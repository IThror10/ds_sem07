#ifndef __ROTOR_HPP__
#define __ROTOR_HPP__

    #include "settings.hpp"

    typedef struct
    {
        unsigned char fwd;
        unsigned char bwd;
    } pair_t;

    class Rotor
    {
    public:
        Rotor();
        ~Rotor() = default;

        unsigned char commutateFwdLetter(unsigned char letter);
        unsigned char commutateBwdLetter(unsigned char letter);
        void setPosition(int tick);
        bool spinRotor();

    private:
        int curTick;
        pair_t data[ALPH_SIZE][ALPH_SIZE];
    };

#endif //__ROTOR_HPP__