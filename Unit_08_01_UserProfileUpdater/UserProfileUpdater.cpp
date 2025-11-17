#include "UserProfileUpdater.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

UserProfileUpdater::UserProfileUpdater(const std::string &inputDir)
	: m_inputDir(inputDir)
{
}

std::string UserProfileUpdater::makeTimestamp()
{
	using namespace std::chrono;
	auto now = system_clock::now();
	std::time_t t = system_clock::to_time_t(now);
	std::tm tm{};
#ifdef _WIN32
	localtime_s(&tm, &t);
#else
	localtime_r(&t, &tm);
#endif
	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
	return oss.str();
}

bool UserProfileUpdater::endsWith(const std::string &str, const std::string &suffix)
{
	if (suffix.size() > str.size())
		return false;
	return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

void UserProfileUpdater::createOutputDirectory()
{
	std::string name = "user_profiles_updated_" + makeTimestamp();
	fs::path parent = m_inputDir.parent_path();
	if (parent.empty())
		parent = ".";
	m_outputDir = parent / name;
	fs::create_directories(m_outputDir);
	std::cout << "Output directory: " << m_outputDir << "\n";
}

void UserProfileUpdater::transformValue(json &value)
{
	if (value.is_object() || value.is_array())
	{
		transformJson(value);
		return;
	}

	if (!value.is_string())
		return;

	std::string s = value.get<std::string>();

	if (endsWith(s, "@company.com"))
	{
		auto at = s.find('@');
		if (at != std::string::npos)
		{
			s = s.substr(0, at) + "@newcompany.com";
			value = s;
		}
		return;
	}

	if (s == "enabled")
	{
		value = json{{"status", "enabled"}, {"since", "2024-10-01"}};
	}
	else if (s == "disabled")
	{
		value = json{{"status", "disabled"}, {"since", "2024-10-01"}};
	}
	else if (s == "manage_users")
	{
		value = json{{"permission", "manage_users"},
					 {"granted_at", "2024-10-05"},
					 {"level", "full"}};
	}
	else if (s == "view_content")
	{
		value = json{{"permission", "view_content"},
					 {"granted_at", "2024-09-25"},
					 {"level", "read-only"}};
	}
}

void UserProfileUpdater::transformJson(json &j)
{
	if (j.is_object())
	{
		for (auto &item : j.items())
		{
			transformValue(item.value());
		}
	}
	else if (j.is_array())
	{
		for (auto &elem : j)
		{
			transformValue(elem);
		}
	}
	else
	{
		transformValue(j);
	}
}

void UserProfileUpdater::processFile(const fs::path &inFile, const fs::path &outFile)
{
	try
	{
		std::ifstream in(inFile);
		if (!in)
		{
			fs::copy_file(inFile, outFile, fs::copy_options::overwrite_existing);
			return;
		}

		json j;
		in >> j;

		transformJson(j);

		fs::create_directories(outFile.parent_path());
		std::ofstream out(outFile);
		if (!out)
		{
			fs::copy_file(inFile, outFile, fs::copy_options::overwrite_existing);
			return;
		}

		out << j.dump(4);
	}
	catch (...)
	{
		fs::create_directories(outFile.parent_path());
		fs::copy_file(inFile, outFile, fs::copy_options::overwrite_existing);
	}
}

void UserProfileUpdater::processDirectory(const fs::path &inDir, const fs::path &outDir)
{
	fs::create_directories(outDir);

	for (const auto &entry : fs::directory_iterator(inDir))
	{
		fs::path inPath = entry.path();
		fs::path outPath = outDir / inPath.filename();

		if (entry.is_directory())
		{
			processDirectory(inPath, outPath);
		}
		else if (entry.is_regular_file() && inPath.extension() == ".json")
		{
			processFile(inPath, outPath);
		}
		else if (entry.is_regular_file())
		{
			fs::create_directories(outDir);
			fs::copy_file(inPath, outPath, fs::copy_options::overwrite_existing);
		}
	}
}

void UserProfileUpdater::run()
{
	if (!fs::exists(m_inputDir) || !fs::is_directory(m_inputDir))
	{
		std::cerr << "Invalid input directory: " << m_inputDir << "\n";
		return;
	}

	createOutputDirectory();
	processDirectory(m_inputDir, m_outputDir);
	std::cout << "Done.\n";
}
