#include <iostream>
#include <vector>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "uart.hpp"
#include "crc.hpp"
#include "log.hpp"

uint8_t co2_acquire[8] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00};
uint8_t soil_acuire[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00};

uint8_t addr1to2[8] = {0x01, 0x06, 0x07, 0xd0, 0x00, 0x02, 0x0, 0x0};

void f(int num){
    printf("%dsignal\n", num);
    sleep(3);
    return;
}

int main(int argc, char * argv[]){
    uart port("/dev/ttyUSB0", 4800, 8, 'N', 1);

    log * logfile = new log("./tmp/test.log", 100);

    logfile->write("%s", "niubi");
    logfile->write_ex("%s\n", "shabi");
    sleep(3);
    logfile->write("%s", "niubi");
    logfile->write_ex("%s\n", "shabi");

    

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd == -1){
        perror("socket");
    }
    struct sockaddr_in servaddr = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.107");
    servaddr.sin_port = htons(atoi(argv[1]));
    if(bind(listen_fd, (struct sockaddr *)&(servaddr), sizeof(servaddr)) != 0){
        perror("bind");;
    }

    if(listen(listen_fd, 3) == -1){
        perror("listen");
    }

    int client_fd;
    int socket_addr_len = sizeof(struct sockaddr_in);
    struct sockaddr_in client_addr;
    if((client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, (socklen_t *)&socket_addr_len)) < 0){
        perror("accpet");
    }
    printf("%s: %dconnected\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

    const char * str = "hello!";

    if(send(client_fd, str, 6, 0) <= 0){
        perror("send");
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