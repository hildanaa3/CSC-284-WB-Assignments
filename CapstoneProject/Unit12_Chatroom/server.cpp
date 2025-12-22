#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

class User
{
public:
    int socket;
    string username;
    string room;
};

class Room
{
public:
    string name;
    vector<User *> users;
};

class ChatServer
{
private:
    map<int, User> users;
    map<string, Room> rooms;
    mutex mtx;
    int anonCount = 1;

public:
    ChatServer()
    {
        rooms["Lobby"] = Room{"Lobby", {}};
    }

    void start()
    {
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in server{};
        server.sin_family = AF_INET;
        server.sin_port = htons(54000);
        server.sin_addr.s_addr = INADDR_ANY;

        int opt = 1;
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        ::bind(serverSocket, (sockaddr *)&server, sizeof(server));
        listen(serverSocket, SOMAXCONN);

        cout << "Server running on port 54000\n";

        while (true)
        {
            sockaddr_in client{};
            socklen_t size = sizeof(client);
            int clientSocket = accept(serverSocket, (sockaddr *)&client, &size);

            lock_guard<mutex> lock(mtx);
            string name = "anon" + to_string(anonCount++);
            users[clientSocket] = User{clientSocket, name, "Lobby"};
            rooms["Lobby"].users.push_back(&users[clientSocket]);

            thread(&ChatServer::handleClient, this, clientSocket).detach();
        }
    }

    void handleClient(int clientSocket)
    {
        char buffer[4096];

        while (true)
        {
            memset(buffer, 0, sizeof(buffer));
            int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytes <= 0)
                break;

            string msg(buffer);
            handleMessage(clientSocket, msg);
        }

        disconnect(clientSocket);
    }

    void handleMessage(int sock, const string &msg)
    {
        if (msg.rfind(".CREATE_ROOM", 0) == 0)
        {
            string room = msg.substr(13);
            createRoom(room, sock);
        }
        else if (msg.rfind(".JOIN_ROOM", 0) == 0)
        {
            string room = msg.substr(11);
            joinRoom(room, sock);
        }
        else if (msg == ".LIST_ROOMS")
        {
            listRooms(sock);
        }
        else if (msg == ".EXIT")
        {
            disconnect(sock);
        }
        else
        {
            broadcast(sock, msg);
        }
    }

    void createRoom(const string &room, int sock)
    {
        lock_guard<mutex> lock(mtx);
        if (!rooms.count(room))
            rooms[room] = Room{room, {}};
    }

    void joinRoom(const string &room, int sock)
    {
        lock_guard<mutex> lock(mtx);
        if (!rooms.count(room))
            return;

        User &u = users[sock];
        auto &oldUsers = rooms[u.room].users;
        oldUsers.erase(remove(oldUsers.begin(), oldUsers.end(), &u), oldUsers.end());

        u.room = room;
        rooms[room].users.push_back(&u);
    }

    void listRooms(int sock)
    {
        lock_guard<mutex> lock(mtx);
        for (auto &r : rooms)
        {
            send(sock, r.first.c_str(), r.first.size(), 0);
            send(sock, "\n", 1, 0);
        }
    }

    void broadcast(int sock, const string &msg)
    {
        lock_guard<mutex> lock(mtx);
        User &u = users[sock];
        for (auto user : rooms[u.room].users)
        {
            if (user->socket != sock)
                send(user->socket, msg.c_str(), msg.size(), 0);
        }
    }

    void disconnect(int sock)
    {
        close(sock);
        users.erase(sock);
    }
};

int main()
{
    ChatServer server;
    server.start();
}
