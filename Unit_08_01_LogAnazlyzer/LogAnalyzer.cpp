#include "LogAnalyzer.h"
#include <iostream>
#include <fstream>
#include <thread>

namespace fs = std::filesystem;

LogAnalyzer::LogAnalyzer(const std::string &directory)
	: m_directory(directory)
{

	m_keywords = {"WARN", "ERROR", "FATAL", "INFO", "DEBUG", "TRACE"};

	for (const auto &k : m_keywords)
	{
		m_totals[k] = 0;
	}

	try
	{
		if (!fs::exists(m_directory) || !fs::is_directory(m_directory))
		{
			std::cerr << "Error: Invalid directory: " << m_directory << "\n";
			return;
		}

		for (const auto &entry : fs::directory_iterator(m_directory))
		{
			if (entry.is_regular_file() && entry.path().extension() == ".log")
			{
				m_files.push_back(entry.path());
			}
		}
	}
	catch (...)
	{
		std::cerr << "Error scanning directory.\n";
	}
}

void LogAnalyzer::run()
{
	if (m_files.empty())
	{
		std::cout << "No .log files found.\n";
		return;
	}

	std::cout << "Analyzing folder: " << m_directory << "\n\n";

	std::vector<std::thread> workers;

	for (const auto &file : m_files)
	{
		workers.emplace_back(&LogAnalyzer::processFile, this, file);
	}

	for (auto &t : workers)
	{
		if (t.joinable())
			t.join();
	}

	printSummary();
}

void LogAnalyzer::processFile(const fs::path &filePath)
{
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		std::cout << "Processing: " << filePath.filename().string() << "\n";
	}

	std::ifstream in(filePath);
	if (!in)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		std::cerr << "Failed to open file: " << filePath << "\n";
		return;
	}

	std::map<std::string, int> local;
	for (const auto &k : m_keywords)
	{
		local[k] = 0;
	}

	std::string line;
	while (std::getline(in, line))
	{
		for (const auto &k : m_keywords)
		{
			std::string token = "[" + k + "]";
			size_t pos = line.find(token);
			while (pos != std::string::npos)
			{
				local[k]++;
				pos = line.find(token, pos + token.size());
			}
		}
	}

	{
		std::lock_guard<std::mutex> lock(m_mutex);
		for (const auto &pair : local)
		{
			m_totals[pair.first] += pair.second;
		}
	}
}

void LogAnalyzer::printSummary() const
{
	std::cout << "\n--- Keyword Summary ---\n";
	for (const auto &k : m_keywords)
	{
		std::cout << k << ": " << m_totals.at(k) << "\n";
	}

	std::cout << "\nProcessed " << m_files.size() << " files.\n";
	std::cout << "Analysis complete.\n";
}
