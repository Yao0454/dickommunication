#include "../../include/server/yyfshead.h"

int main() {

    //先创建一个服务器对象
    Server server(12345);

    if (!server.start()) {
        cerr << "服务器启动失败了qwq" << endl;
        return 1;
    }

    cout << "服务器启动成功了qwq 可以看到服务器的状态：" << (server.getRunningStatus() ? "Running!!!" : "Stopped!!") << endl;

    SOCKET clientSocket = server.acceptClient();
    if (clientSocket != INVALID_SOCKET) {
        cout << "成功与客户端连接" << endl;

        close(clientSocket);
        cout << "Closed!!!!!!!" << endl;

    }

    return 0;
    
}