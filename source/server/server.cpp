#include "../../include/server/yyfshead.h"


Server::Server(int serverPort)
  : port(serverPort),
    isRunning(false),
    serverSocket(INVALID_SOCKET),
    serverAddr{} 
{
    cout << "服务器创建成功，端口：" << port << endl;
    serverAddr.sin_family = AF_INET;
    //yyf: sin_family是这个结构体中的地址簇更上面的AF是对应的 这里AF_INET代表ipv4
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    //yyf：sin.addr也是个结构体 代表输入的地址s_addr就是一个unsigned short INADDR_ANY是一个常量(u_long)0x00000000 代表0.0.0.0也就是任何地址
        //yyf：如果想指定特别的ip可以使用inet_addr("192.168.xx.xxx")之类的 inet_addr 是一个字符串到整数转换函数，用于将点分十进制的 IP 地址字符串转换为网络字节序的 32 位整数
    serverAddr.sin_port = htons(port);
    //yyf：sin_port就是端口 也是unsigned short 范围是0-65535 熟悉的东西来了 htons() 就是 Host To Network Short 是字节序转换 让计算机能看懂你输入的端口
}//构造函数

Server::~Server() {
    stop();
    cout << "服务器被你关掉了！！！" << endl;
}//析构函数

bool Server::createSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //yyf: socket函数的三个输入值都是整型 对应初始化的socket的AF Type 和 Protocol
    //yyf：AF就是Address Family 地址簇 AF_INET就是Address Family_Internet 表示使用ipv4格式  AF_INET6就是ipv6格式了
    //yyf：Type就是套接字类型 套接字就像是网络通信的插座，两个程序要通过网络"说话"，就需要各自插上这个"插座" 
    //yyf：SOCK_STREAM就表示流式套接字TCP 还有数据报套接字UDP（SOCK_DGRAM）
    //yyf：Protocol就是协议 IPPROTO_TCP就是用TCP协议 IPPROTO_UDP就是用UDP协议 这个和上面的Type基本上是绑定的 0就是让系统自己选
    
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Socket初始化错误" << endl;
        //yyf：检测一下初始化有没有问题
        return false;
    }

    cout << "你成功创建了一个Socket服务器qwq" << endl;
    return true;
}//创建Socket服务器的函数

bool Server::bindAddress() {
    //yyf：然后要准备地址结构 需要创建一个sockaddr_in的结构体来存储服务器的地址信息

    
    //yyf: 下一步就是绑定你初始化的socket到对应的地址和端口
    int bindresult = bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    /*听yyf说：
    bind() 函数的三个参数：
    serverSocket - 你创建的 Socket
    (sockaddr*)&serverAddr - 地址结构指针（需要强制转换类型）
    为什么要强制转换类型？
    bind() 函数的输入参数类型是 sockaddr*
    传入的是 sockaddr_in* in就代表着是你输入的
    需要强制转换：(sockaddr*)&serverAddr 这里就相当于是电脑读取的
    sizeof(serverAddr) - 地址结构的大小
    */
    if (bindresult == SOCKET_ERROR) {
        cerr << "地址绑定失败!!!Fucccccckkkkk!!!" << endl;
        return false;
    }

    cout << "恭喜你成功绑定了！！！" << endl;
    return true;

}//绑定ip和端口的函数

bool Server::startListen() {
    //yyf：开始监听连接
    int listenResult = listen(serverSocket, SOMAXCONN);
    //yyf:listen() 函数的两个参数：serverSocket 你的socket服务器, SOMAXCONN 允许的最大连接队列长度（系统默认值）我觉得是Socket Maximum Connection
    
    if (listenResult == SOCKET_ERROR) {
        cerr << "很不好，又出错了，监听错误！" << endl;
        return false;
    }
    
    cout << "OK孩子你成功了,服务器正在监听端口 " << port << endl;
    isRunning = true;
    return true;
}//开始监听函数

bool Server::initialize() {
    cout << "开始来初始化一个服务器" << endl;

    if (!createSocket()) return false;
    if (!bindAddress()) return false;
    if (!startListen()) return false;

    cout << "服务器初始化完成！！" << endl;
    return true;

}//一个统一的初始化函数

bool Server::start() {
    return initialize();
}//启动！！！！！

SOCKET Server::acceptClient() {
    if (!isRunning) {
        cerr << "服务器未正常运行！！！" << endl;
        return INVALID_SOCKET;
    }

    cout << "等待来自客户端的连接......" << endl;

    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);

    if (clientSocket == INVALID_SOCKET) {
        cerr << "与客户端连接失败！！！"  << endl;
        return INVALID_SOCKET;

    }

    cout << "客户端连接成功!你可以看到来自客户端的IP是: " << inet_ntoa(clientAddr.sin_addr) 
         << ", Port: " << ntohs(clientAddr.sin_port) << endl;

    return clientSocket;
}

void Server::stop() {
    if(serverSocket != INVALID_SOCKET) {
        close(serverSocket);
        serverSocket = INVALID_SOCKET;
        cout << "服务器已停止" << endl;

    }
    isRunning = false;

}

bool Server::getRunningStatus() const {
    return isRunning;
}

int Server::getPort() const {
    return port;
}


