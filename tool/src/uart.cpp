#include "uart.hpp"

uart::uart(const char * file_pth, int nSpeed, int nBits, char nEvent, int nStop){
    this->fd = this->open_port(file_pth);
    this->baudrate = nSpeed;
    this->set_opt(nSpeed, nBits, nEvent, nStop);

    FD_ZERO(&this->fd_sets);
    FD_SET(this->fd, &this->fd_sets);

    // int flag = fcntl(this->fd, F_GETFL);
    // fcntl(this->fd, F_SETFL, flag & (~O_NONBLOCK));
}

uart::~uart(){
    close(this->fd);
}

int uart::get_fd() const{
    return this->fd;
}

size_t uart::send(const void *buf, size_t count){
    return write(this->fd, buf, count);
}

int uart::receive(uint8_t * buf, size_t count, uint32_t timewait){
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = timewait;
    if(select(this->fd + 1, &this->fd_sets, NULL, NULL, &timeout) < 0){
        throw uart::error("receive error");
    }
    else if(FD_ISSET(this->fd, &this->fd_sets)){
        uint32_t delay_time = (1000000 / (this->baudrate >> 3)) * count * 3 / 2;
        usleep(delay_time);
        read(this->fd, buf, count);
        return 1;
    }
    else{
        return 0;
    }
}

int uart::open_port(const char * file_pth){
    int fd;
    fd = open(file_pth, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1){
        throw uart::error("comport didn't exist");
    }
    return fd;
}

int uart::set_opt(int nSpeed, int nBits, char nEvent, int nStop) 
{ 
    struct termios newtio,oldtio; 
/*保存测试现有串口参数设置，在这里如果串口号等出错，会有相关的出错信息*/ 
    if(tcgetattr(this->fd,&oldtio)  !=  0) {  
        perror("SetupSerial 1");
        printf("tcgetattrfd,&oldtio) -> %d\n",tcgetattr(this->fd,&oldtio)); 
        return -1; 
    } 
    memset(&newtio, 0, sizeof( newtio ) ); 
/*步骤一，设置字符大小*/ 
    newtio.c_cflag  |=  CLOCAL | CREAD;  
    newtio.c_cflag &= ~CSIZE;  
/*设置停止位*/ 
    switch( nBits ) 
    { 
    case 7: 
    newtio.c_cflag |= CS7; 
    break; 
    case 8: 
    newtio.c_cflag |= CS8; 
    break; 
    } 
/*设置奇偶校验位*/ 
    switch( nEvent ) 
    { 
        case 'o':
        case 'O': //奇数 
        newtio.c_cflag |= PARENB; 
        newtio.c_cflag |= PARODD; 
        newtio.c_iflag |= (INPCK | ISTRIP); 
        break; 
        case 'e':
        case 'E': //偶数 
        newtio.c_iflag |= (INPCK | ISTRIP); 
        newtio.c_cflag |= PARENB; 
        newtio.c_cflag &= ~PARODD; 
        break;
        case 'n':
        case 'N':  //无奇偶校验位 
        newtio.c_cflag &= ~PARENB; 
        break;
        default:
        break;
    } 
    /*设置波特率*/ 
switch( nSpeed ) 
    { 
    case 2400: 
    cfsetispeed(&newtio, B2400); 
    cfsetospeed(&newtio, B2400); 
    break; 
    case 4800: 
    cfsetispeed(&newtio, B4800); 
    cfsetospeed(&newtio, B4800); 
    break; 
    case 9600: 
    cfsetispeed(&newtio, B9600); 
    cfsetospeed(&newtio, B9600); 
    break; 
    case 115200: 
    cfsetispeed(&newtio, B115200); 
    cfsetospeed(&newtio, B115200); 
    break; 
    case 460800: 
    cfsetispeed(&newtio, B460800); 
    cfsetospeed(&newtio, B460800); 
    break; 
    default: 
    cfsetispeed(&newtio, B9600); 
    cfsetospeed(&newtio, B9600); 
    break; 
    } 
/*设置停止位*/ 
    if( nStop == 1 ) 
    newtio.c_cflag &=  ~CSTOPB; 
    else if ( nStop == 2 ) 
    newtio.c_cflag |=  CSTOPB; 
/*设置等待时间和最小接收字符*/ 
    newtio.c_cc[VTIME]  = 0; 
    newtio.c_cc[VMIN] = 0; 
/*处理未接收字符*/ 
    tcflush(fd,TCIFLUSH); 
/*激活新配置*/ 
    if((tcsetattr(this->fd,TCSANOW,&newtio))!=0) 
    { 
        throw uart::error("com set error"); 
        return -1; 
    } 
    printf("uart open!\n"); 
    return 0; 
} 