#ifndef __ENIGMA_HPP__
#define __ENIGMA_HPP__

    class Rotor;
    class Reflector;
    
    class Enigma
    {
    public:
        Enigma(unsigned srandSet);
        ~Enigma();

        void configure(unsigned srandSet);
        char cipher(unsigned char letter);
    
    private:
        void configure();
        Rotor *rotors;
        Reflector *reflector;
    };

#endif //__ENIGMA_HPP__