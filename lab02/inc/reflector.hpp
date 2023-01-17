#ifndef __REFLECTOR_HPP__
#define __REFLECTOR_HPP__

    #include "settings.hpp"

    class Reflector
    {
    public:
        Reflector();
        ~Reflector() = default;
        unsigned char reflect(unsigned char letter) const;

    private:
        unsigned char data[ALPH_SIZE];
    };

#endif //__REFLECTOR_HPP__