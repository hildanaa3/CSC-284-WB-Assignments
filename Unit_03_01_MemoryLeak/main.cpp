#include <atomic>
#include <chrono>
#include <csignal>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

constexpr size_t MiB = 1024 * 1024;
atomic<bool> stopFlag{false};
void onSignal(int) { stopFlag = true; }

int main(int argc, char **argv)
{
    vector<char *> keep;

    signal(SIGINT, onSignal);
#ifdef SIGTERM
    signal(SIGTERM, onSignal);
#endif

    size_t t = 0;
    while (!stopFlag)
    {
        char *block = new char[MiB];
        memset(block, 0xA5, MiB);

        // To see the leak: uncomment the next line and comment out the delete[] line
        // keep.push_back(block);

        delete[] block;

        ++t;
        cout << "t=" << t << "s" << endl;

        this_thread::sleep_for(chrono::seconds(1));
    }

    for (char *p : keep)
        delete[] p;
    return 0;
}
