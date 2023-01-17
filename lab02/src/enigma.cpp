#include "enigma.hpp"
#include "rotor.hpp"
#include "reflector.hpp"

Enigma::Enigma(unsigned srandStart)
{
    srand(srandStart);
    this->reflector = new Reflector();
    this->rotors = new Rotor[ROTORS_COUNT];

    this->configure(srandStart);
}

Enigma::~Enigma()
{
    delete[] rotors;
    delete reflector;
}

void Enigma::configure(unsigned srandSet)
{
    srand(srandSet);
    this->configure();
}

void Enigma::configure()
{
    for (int i = 0; i < ROTORS_COUNT; i++)
        rotors[i].setPosition(rand() % ALPH_SIZE);
}

char Enigma::cipher(unsigned char letter)
{
    for (int i = 0; i < ROTORS_COUNT; i++)
        letter = rotors[i].commutateFwdLetter(letter);
    letter = reflector->reflect(letter);
    for (int i = ROTORS_COUNT - 1; i >= 0; i--)
        letter = rotors[i].commutateBwdLetter(letter);

    for (int i = 0; i < ROTORS_COUNT && rotors[i].spinRotor(); i++);
    return letter;
}