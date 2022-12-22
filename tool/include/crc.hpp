#include <iostream>

namespace CRC{
    struct Mod16{
        uint16_t Poly, Initvalue, OutputXOR;
        bool InputReverse, OutputReverse;
        Mod16(uint16_t Poly, uint16_t Initvalue, uint16_t OutputXOR, bool InputReverse, bool OutputReverse);
    };

    void crc16(uint8_t * data, int n, Mod16 mod);
    uint16_t reverse16(uint16_t data);
    uint8_t reverse8(uint8_t data);
}

