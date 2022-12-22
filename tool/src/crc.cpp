#include "crc.hpp"

uint16_t CRC::reverse16(uint16_t data){
    uint16_t ans = 0;
    for(int i = 0; i < 16; ++i){
        ans |= ((data >> i) & 0x0001) << (15 - i);
    }
    return ans;
}

uint8_t CRC::reverse8(uint8_t data){
    uint8_t ans = 0;
    for(int i = 0; i < 8; ++i){
        ans |= ((data >> i) & 0x01) << (7 - i);
    }
    return ans;
}

void CRC::crc16(uint8_t * data, int n, Mod16 mod){
    uint8_t byte;
    uint16_t crc = mod.Initvalue;
    for(int i = 0; i < n; ++i){
        byte = *(data + i);
        if(mod.InputReverse){
            byte = reverse8(byte);
        }
        crc ^= byte << 8;
        for(int j = 0; j < 8; ++j){
            if(crc & 0x8000){
                crc = (crc << 1) ^ 0x8005;
            }
            else{
                crc <<= 1;
            }
        }
    }
    if(mod.OutputReverse){
        crc = reverse16(crc);
    }

    data[n] = crc;
    data[n + 1] = crc >> 8;
}

CRC::Mod16::Mod16(uint16_t Poly, uint16_t Initvalue, uint16_t OutputXOR, bool InputReverse, bool OutputReverse){
    this->Poly = Poly;
    this->Initvalue = Initvalue;
    this->OutputXOR = OutputXOR;
    this->InputReverse = InputReverse;
    this->OutputReverse = OutputReverse;
}