#include "tcp.hpp"

bool tcp::readn(const int sockfd, uint8_t * buf, const size_t n){
    int idx = 0, nleft = n, nread = 0;

    while(nleft){
        nread = read(sockfd, buf + idx, nleft);
        idx += nread;
        nleft -= nread;
    }

    return true;
}

bool tcp::sendn(const int sockfd, const uint8_t * buf, const size_t n){
    int idx = 0, nwrite = 0, nleft = n;

    while(nleft){
        nwrite = write(sockfd, buf + idx, nleft);
        idx += nwrite;
        nleft -= nwrite;
    }

    return true;
}