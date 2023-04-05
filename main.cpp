#include <iostream>
#include <vector>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "uart.hpp"
#include "log.hpp"
#include "tcp.hpp"

#include "opencv2/opencv.hpp"
#include "camera.hpp"


int main(int argc, char * argv[]){
    printf("hello, world");
    uart * port = new uart("/dev/ttyUSB0", 4800, 8, 'N', 1);
    CameraCatchNode * node = new CameraCatchNode();
    node->record("./test1.mp4");

    cv::VideoCapture cap("./tmp/test1.avi");
    cv::Mat frame;
    while(1){
        cap >> frame;
        cv::imshow("show", frame);
    }

    // log * logfile = new log("./tmp/test.log", 100);
    // int sockfd;
    // if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    //     perror("socket");
    // }
    // struct sockaddr_in servaddr = {0};
    // servaddr.sin_family = AF_INET;
    // struct hostent * h;
    // if((h = gethostbyname(argv[1])) == NULL){
    //     printf("host name error");
    // }
    // memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
    // servaddr.sin_port = htons(atoi(argv[2]));
    // if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0){
    //     perror("connect");
    // }

    // std::vector<uint8_t> tcp_data(8, 0);
    // std::vector<uint8_t> uart_data(15, 0);
    // while(1){

    //     tcp::readn(sockfd, tcp_data.data(), 8);
    //     port->send(tcp_data.data(), 8);
    //     port->receive(uart_data.data(), 15, 100000);
    //     tcp::sendn(sockfd, uart_data.data(), 15);
    //     // usleep(100000);
    // }
    return 0;
}
