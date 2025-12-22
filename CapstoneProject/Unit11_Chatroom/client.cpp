#include <iostream>
#include <thread>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

void receiveMessages(int sock) {
    char buffer[4096];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(sock, buffer, sizeof(buffer), 0);
        if (bytes <= 0) break;

        cout << "\n" << string(buffer, bytes) << endl;
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        cerr << "Cannot connect\n";
        return 1;
    }

    thread recvThread(receiveMessages, sock);

    string msg;
    while (getline(cin, msg)) {
        send(sock, msg.c_str(), msg.size(), 0);
    }

    close(sock);
    recvThread.join();
    return 0;
}
