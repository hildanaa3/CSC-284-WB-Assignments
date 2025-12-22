#include <iostream>
#include <thread>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

void receiveMessages(int sock)
{
    char buffer[4096];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(sock, buffer, sizeof(buffer), 0);
        if (bytes <= 0)
            break;
        cout << buffer << endl;
    }
}

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (sockaddr *)&server, sizeof(server));

    thread t(receiveMessages, sock);

    string input;
    while (getline(cin, input))
    {
        send(sock, input.c_str(), input.size(), 0);
        if (input == ".EXIT")
            break;
    }

    close(sock);
    t.join();
}
