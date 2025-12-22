#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

mutex clientsMutex;
vector<int> clients;

void broadcastMessage(const string& msg, int sender) {
    lock_guard<mutex> lock(clientsMutex);
    for (int c : clients) {
        if (c != sender) {
            send(c, msg.c_str(), msg.size(), 0);
        }
    }
}

void handleClient(int client) {
    char buffer[4096];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(client, buffer, sizeof(buffer), 0);
        if (bytes <= 0) break;

        broadcastMessage(string(buffer, bytes), client);
    }

    close(client);

    lock_guard<mutex> lock(clientsMutex);
    clients.erase(remove(clients.begin(), clients.end(), client), clients.end());
}

int main() {
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in hint{};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.s_addr = INADDR_ANY;

    if (::bind(listening, (sockaddr*)&hint, sizeof(hint)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(listening, SOMAXCONN) < 0) {
        perror("listen");
        return 1;
    }

    cout << "Server listening on 127.0.0.1:54000" << endl;

    while (true) {
        sockaddr_in client{};
        socklen_t size = sizeof(client);

        int clientSocket = accept(listening, (sockaddr*)&client, &size);
        if (clientSocket < 0) {
            perror("accept");
            continue;
        }

        {
            lock_guard<mutex> lock(clientsMutex);
            clients.push_back(clientSocket);
        }

        thread(handleClient, clientSocket).detach();
    }

    return 0;
}
