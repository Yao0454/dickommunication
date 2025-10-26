#include "../../include/server/yyfshead.h"

int main() {
    //yyf: 这是后端服务器的第一步 初始化Winsocket
    
    WSADATA wsaData;    
    //yyf: 这里的WSADATA是一个结构体名 用来存储Winsock的信息

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);  
    //yyf: 这里初始化一个result 是因为这个初始化函数的返回值是整型 0为成功 非0为失败 MAKEWORD是请求版本（2， 2）就是2.2版本
    if (result != 0) {
        cerr << "初始化错误， 错误代码为" << result << endl; 
        //yyf: cerr是用来打印错误信息的函数
        return 1;
    } else cout << "初始化成功" << endl;

    //yyf: 第二部就是创建一个socket 并绑定到对应端口

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //yyf: socket函数的三个输入值都是整型 对应初始化的socket的AF Type 和 Protocol
    //yyf：AF就是Address Family 地址簇 AF_INET就是Address Family_Internet 表示使用ipv4格式  AF_INET6就是ipv6格式了
    //yyf：Type就是套接字类型 套接字就像是网络通信的插座，两个程序要通过网络"说话"，就需要各自插上这个"插座" 
    //yyf：SOCK_STREAM就表示流式套接字TCP 还有数据报套接字UDP（SOCK_DGRAM）
    //yyf：Protocol就是协议 IPPROTO_TCP就是用TCP协议 IPPROTO_UDP就是用UDP协议 这个和上面的Type基本上是绑定的 0就是让系统自己选
    
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Socket初始化错误" << endl;
        //yyf：检测一下初始化有没有问题
        return 1;
    } else {
        cout << "Sockek初始化成功" << endl;
        //yyf：然后要准备地址结构 需要创建一个sockaddr_in的结构体来存储服务器的地址信息
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        //yyf: sin_family是这个结构体中的地址簇更上面的AF是对应的 这里AF_INET代表ipv4
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        //yyf：sin.addr也是个结构体 代表输入的地址s_addr就是一个unsigned short INADDR_ANY是一个常量(u_long)0x00000000 代表0.0.0.0也就是任何地址
        //yyf：如果想指定特别的ip可以使用inet_addr("192.168.xx.xxx")之类的 inet_addr 是一个字符串到整数转换函数，用于将点分十进制的 IP 地址字符串转换为网络字节序的 32 位整数
        serverAddr.sin_port = htons(12345);
        //yyf：sin_port就是端口 也是unsigned short 范围是0-65535 熟悉的东西来了 htons() 就是 Host To Network Short 是字节序转换 让计算机能看懂你输入的端口
        
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
            return 1;
       } else {
            cout << "恭喜你你成功绑定了!" << endl;
            //yyf：然后就是监听这个连接
            int listenResult = listen(serverSocket, SOMAXCONN);
            //yyf:listen() 函数的两个参数：serverSocket 你的socket服务器, SOMAXCONN 允许的最大连接队列长度（系统默认值）我觉得是Socket Maximum Connection
            if (listenResult == SOCKET_ERROR) {
                cout << "很不好，又出错了，监听错误！" << endl;
                return 1;
            } else {
                cout << "OK孩子你成功了" << endl;
                //yyf：下一步就是等客户端连接了
            }
       }
    }
}