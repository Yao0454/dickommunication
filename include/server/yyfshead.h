#ifndef YYFSHEAD_H
#define YYFSHEAD_H
/*windows
#include <winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
*/


#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
//我受不了写std::了 FUUUUUUUUCKKKK

//Linux下的socket定义
typedef int SOCKET;
const int INVALID_SOCKET = -1;
const int SOCKET_ERROR = -1;

class Server {
private:
    SOCKET serverSocket;
    sockaddr_in serverAddr;
    int port;
    bool isRunning;

public:
    Server(int serverPort = 12345);
    //构造函数

    ~Server();
    //析构函数

    bool initialize();
    //初始化我们的服务器

    bool createSocket();
    //创建socket

    bool bindAddress();
    //绑定地址和端口

    bool startListen();
    //开始监听

    SOCKET acceptClient();
    //接受来自客户端的连接

    bool start();
    //服务器，启动！！

    void stop();
    //关闭服务器

    bool getRunningStatus() const;
    //获取服务器状态

    int getPort() const;
    //获取端口号



};


#endif