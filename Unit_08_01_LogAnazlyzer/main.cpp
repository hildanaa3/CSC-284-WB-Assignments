#include "LogAnalyzer.h"
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <log_directory>\n";
		return 1;
	}

	LogAnalyzer analyzer(argv[1]);
	analyzer.run();

	return 0;
}
