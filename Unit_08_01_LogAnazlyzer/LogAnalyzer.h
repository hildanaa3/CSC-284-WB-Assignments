
#ifndef LOGANALYZER_H
#define LOGANALYZER_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <filesystem>

class LogAnalyzer
{
public:
	LogAnalyzer(const std::string &directory);

	void run();
	void printSummary() const;

private:
	void processFile(const std::filesystem::path &filePath);

private:
	std::string m_directory;
	std::vector<std::filesystem::path> m_files;

	std::vector<std::string> m_keywords;
	std::map<std::string, int> m_totals;

	mutable std::mutex m_mutex;
};

#endif
