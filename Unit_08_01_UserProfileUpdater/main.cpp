#include "UserProfileUpdater.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <user_profiles_directory>\n";
        return 1;
    }

    UserProfileUpdater updater(argv[1]);
    updater.run();

    return 0;
}
