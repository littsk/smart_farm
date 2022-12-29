#ifndef TCP_HPP
#define TCP_HPP

#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace tcp{
    bool readn(const int sockfd, uint8_t * buf, const size_t n);
    bool sendn(const int sockfd, const uint8_t * buf, const size_t n);
}

#endif