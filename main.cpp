#include <iostream>
#include <vector>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "uart.hpp"
#include "crc.hpp"

uint8_t co2_acquire[8] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00};
uint8_t soil_acuire[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00};

uint8_t addr1to2[8] = {0x01, 0x06, 0x07, 0xd0, 0x00, 0x02, 0x0, 0x0};



int main(int argc, char * argv[]){
    uart port("/dev/ttyUSB0", 4800, 8, 'N', 1);
    

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.107");
    servaddr.sin_port = htons(atoi(argv[1]));
    if(bind(sockfd, (sockaddr *)&(servaddr), sizeof(servaddr))){
        printf("socket success");
    }
    else{
        printf("socket error");
    }


    CRC::Mod16 mod(0x8005, 0xffff, 0x0000, true, true);
    CRC::crc16(co2_acquire, 6, mod);
    CRC::crc16(soil_acuire, 6, mod);
    // CRC::crc16(addr1to2, 6, mod);
    // port.send(addr1to2, 8);
   
    while(1){

        // sensor 1
        port.send(co2_acquire, 8);
        std::vector<uint8_t> data(15, 0);
        port.receive(data.data(), 15, 100000);
        float hum = (int16_t)((data[3] << 8) | data[4]) / 10.0, 
              tem = (int16_t)((data[5] << 8) | (data[6])) / 10.0,
              co2 = (uint16_t)((data[7] << 8) | (data[8])),
              light = (uint32_t)((data[9] << 24) | (data[10] << 16) | (data[11] << 8) | (data[12]));
        // printf("humidity:%.2f%, temperature:%.2fcentigrade, co2:%.2fppm, light:%.2flux\n", hum, tem, co2, light);


        //sensor 2
        port.send(soil_acuire, 8);
        std::fill(data.begin(), data.end(), 0);
        port.receive(data.data(), 13, 100000);
        float soil_hum = (int16_t)((data[3] << 8) | data[4]) / 10.0, 
              soil_tem = (int16_t)((data[5] << 8) | (data[6])) / 10.0,
              soil_ec = (uint16_t)((data[7] << 8) | (data[8])),
              soil_ph = (uint16_t)((data[9] << 8) | (data[10])) / 10.0;
        // printf("soil humidity:%.2f%, soil temperature:%.2fcentigrade, soil electrical conductivity:%.2fppm, PH:%.2flux\n", soil_hum, soil_tem, soil_ec, soil_ph);

        usleep(100000);
    }

    
   
    return 0;
}