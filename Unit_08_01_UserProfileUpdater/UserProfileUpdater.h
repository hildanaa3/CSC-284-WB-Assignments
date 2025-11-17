#ifndef USERPROFILEUPDATER_H
#define USERPROFILEUPDATER_H

#include <string>
#include <filesystem>
#include "json.hpp"
using json = nlohmann::json;


namespace fs = std::filesystem;
using nlohmann::json;

class UserProfileUpdater
{
public:
    explicit UserProfileUpdater(const std::string &inputDir);

    void run();

private:
    fs::path m_inputDir;
    fs::path m_outputDir;

    void createOutputDirectory();
    void processDirectory(const fs::path &inDir, const fs::path &outDir);
    void processFile(const fs::path &inFile, const fs::path &outFile);

    static std::string makeTimestamp();
    static bool endsWith(const std::string &str, const std::string &suffix);

    void transformJson(json &j);
    void transformValue(json &value);
};

#endif
